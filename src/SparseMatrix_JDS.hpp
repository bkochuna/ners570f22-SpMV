/*
=============================================================================
Jagged Diagonal Sparse Matrix (JDS) implementation
=============================================================================
@File    :   SparseMatrix_JDS.hpp
@Date    :   2022/10/16
@Description :
*/
#pragma once

// =============================================================================
// Standard Library Includes
// =============================================================================
#include <algorithm>
#include <vector>

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix.hpp"

// ==============================================================================
// Class declaration
// ==============================================================================
namespace SpMV {
  template <class fp_type>
  class SparseMatrix_JDS : public SparseMatrix<fp_type> {
    public:
      /**
       * @brief Construct a new JDS Sparse Matrix of given dimensions
       *
       * @param rows Number of rows
       * @param cols Number of columns
       */
      SparseMatrix_JDS(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {}

      /**
       * @brief Destructor for JDS Sparse Matrix format. Destory objects created
       *
       */
      virtual ~SparseMatrix_JDS();

      /**
       * @brief Assemble the JDS data structures from the general map based data structure used in the building phase
       *
       */
      void assembleStorage();

      /**
       * @brief I don't know what this does
       *  // Could be getting the nonzero ncols and nrows and creating a new SparseMatrix...
       */
      SparseMatrix<fp_type> getFormat();

      /**
       * @brief Compute the product of this matrix and a vector (y = Ax)
       *
       * @note The contents of y are overwritten by this operation
       *
       * @param x Array to multiply with
       * @param y Array to store result in
       */
      void computeMatVecProduct(const fp_type x[], fp_type y[]);

      /**
       * @brief Convert the assembled matrix data back to the format used for building
       *
       * @note Calling this function will also clear the assembled matrix data
       *
       */
      void _unAssemble();

    private:
      size_t *_colIndices;          ///< Column indices
      size_t _maxRowSize;           ///< Maximum row size
      fp_type *_values;             ///< Values
      std::vector<size_t> _rowPerm; ///< Row permutation
      size_t *_jdPtrs;              ///< JDS pointers
  };                                // class SparseMatrix_JDS

  // ==============================================================================
  // Method implementations
  // ==============================================================================

  template <class fp_type>
  void SparseMatrix_JDS<fp_type>::assembleStorage() {

    assert(this->_state == building);

    // I don't know anything about the order in which the entries will come from the map, so I will first create some 2d
    // arrays (vectors of vectors) to store the column index and values in so that we can later sort the entries in each
    // row
    std::vector<std::vector<int> > colIndMatrix(this->_nrows);
    std::vector<std::vector<fp_type> > valMatrix(this->_nrows);
    std::vector<size_t> rowSizes(this->_nrows);

    // For now, we can populate the entries of the matrices in whatever order they come out of the map, and keep track
    // of the row sizes
    for (auto coeff : this->_buildCoeff) {
      int rowInd = coeff.first.first;
      int colInd = coeff.first.second;
      fp_type val = coeff.second;

      colIndMatrix[rowInd].push_back(colInd);
      valMatrix[rowInd].push_back(val);
      rowSizes[rowInd]++;
    }

    // Then we want to get the rowPerm vector, a.k.a a the row indexes in descending order of size ---
    this->_rowPerm.resize(this->_nrows);
    for (int ii = 0; ii < this->_nrows; ii++) {
      this->_rowPerm[ii] = ii;
    }
    auto sortingFunc = [&](const int &a, const int &b) { return (rowSizes[a] > rowSizes[b]); };
    std::sort(this->_rowPerm.begin(), this->_rowPerm.end(), sortingFunc);

    // Now that rows are sorted we can easily find the max row size
    this->_maxRowSize = rowSizes[this->_rowPerm[0]];

    // For each row, we can sort in order of column index then put entries in the flat col index and value arrays
    for (int rowInd = 0; rowInd < this->_nrows; rowInd++) {
      size_t rowSize = rowSizes[rowInd];
      if (rowSize <= 0) {
        break;
      }

      // Make copies of the current row
      std::vector<int> colIndCopy = colIndMatrix[rowInd];
      std::vector<fp_type> valCopy = valMatrix[rowInd];

      // Create a permutation vector for the column indices and sort it
      std::vector<int> colPerm(rowSize);
      for (int ii = 0; ii < rowSize; ii++) {
        colPerm[ii] = ii;
      }
      auto sortingFunc = [&](const int &a, const int &b) { return (colIndCopy[a] < colIndCopy[b]); };
      std::sort(colPerm.begin(), colPerm.end(), sortingFunc);

      // And now put the sorted values back into the colInd and val matrices
      for (int ii = 0; ii < rowSize; ii++) {
        colIndMatrix[rowInd][ii] = colIndCopy[colPerm[ii]];
        valMatrix[rowInd][ii] = valCopy[colPerm[ii]];
      }
    }

    // Now we can put the column indices and values into the flattened arrays in the right order
    int entryCount = 0;

    this->_colIndices = new size_t[this->_nnz];
    this->_values = new fp_type[this->_nnz];
    this->_jdPtrs = new size_t[this->_maxRowSize + 1];
    this->_jdPtrs[0] = 0;

    // Descend down each column from largest to smallest row until we hit a row that doesn't have an entry for that
    // column
    for (int colInd = 0; colInd < this->_maxRowSize; colInd++) {
      int ii = 0;
      for (ii = 0; ii < this->_nrows; ii++) {
        int rowInd = this->_rowPerm[ii];
        if (rowSizes[rowInd] <= colInd) {
          this->_jdPtrs[colInd + 1] = entryCount;
          break;
        }
        this->_colIndices[entryCount] = colIndMatrix[rowInd][colInd];
        this->_values[entryCount] = valMatrix[rowInd][colInd];
        entryCount++;
      }
      // If we reached the end of a column without hitting a row that didn't have an entry for that column, we need to
      // add the next jdPtr
      if (ii == this->_nrows) {
        this->_jdPtrs[colInd + 1] = entryCount;
      }
    }

    // --- Finally, now that the matrix is assembled we want to release all of the memory used for the original index
    // map ---
    this->_clearBuildCoeff();

    // And we can update the state of the matrix
    this->_state = assembled;
  }

  template <class fp_type>
  SparseMatrix_JDS<fp_type>::~SparseMatrix_JDS() {
    if (_colIndices != NULL) {
      delete[] this->_colIndices;
      this->_colIndices = NULL;
    }

    if (_values != NULL) {
      delete[] this->_values;
      this->_values = NULL;
    }

    if (_jdPtrs != NULL) {
      delete[] this->_jdPtrs;
      this->_jdPtrs = NULL;
    }
  }

  template <class fp_type>
  void SparseMatrix_JDS<fp_type>::computeMatVecProduct(const fp_type x[], fp_type y[]) {
    if (this->_state != assembled) {
      assembleStorage();
    }
    // --- Check that the matrix is assembled ---
    assert(this->_state == assembled);

// Zero the output vector
#pragma omp parallel for simd schedule(static)
    for (int ii = 0; ii < this->_ncols; ii++) {
      y[ii] = 0.0;
    }

// --- Compute the matrix vector product ---
#pragma omp parallel for simd schedule(static) collapse(2)
    for (int ii = 0; ii < this->_maxRowSize; ii++) {
      int colLength = this->_jdPtrs[ii + 1] - this->_jdPtrs[ii];
      int offset = this->_jdPtrs[ii];
      for (int jj = 0; jj < colLength; jj++) {
#pragma omp atomic
        y[this->_rowPerm[jj]] += this->_values[offset + jj] * x[this->_colIndices[offset + jj]];
      }
    }
  }

  template <class fp_type>
  void SparseMatrix_JDS<fp_type>::_unAssemble() {}

  template <class fp_type>
  SparseMatrix<fp_type> SparseMatrix_JDS<fp_type>::getFormat() {
    //
    if (this->_state == assembled):
      _unAssemble();
    //
    SparseMatrix<fp_type> B;
    // newMat -> _nrows, _ncols, _nnz, _buildCoeff = mat->
    // newMat -> assemble
    // number of rows
    B._nrows = this->_nrows;
    // number of columns
    B._ncols = this->_ncols;
    //
    B._nnz = this->_nnz;
    // _buildCoeff 
    B._buildCoeff = this->_buildCoeff;
    // assemble() 
    B.assembleStorage();
    //
    return B;
  }

} // namespace SpMV
