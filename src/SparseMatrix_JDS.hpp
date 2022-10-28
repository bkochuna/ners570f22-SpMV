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
       * @brief Assemble the JDS data structures from the general map based data structure used in the building phase
       *
       */
      void assembleStorage();

      /**
       * @brief I don't know what this does
       *
       */
      /*Some return type*/ void getFormat(/*some args*/);

      void computeMatVecProduct(const fp_type &x, fp_type &y);

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

    // I don't know anything about the order in which the entries will come from the map, so I will first create some 2d
    // arrays (vectors of vectors) to store the column index and values in so that we can later sort the entries in each
    // row
    colIndMatrix = std::vector<std::vector<int> >;
    valMatrix = std::vector<std::vector<fp_type> >;

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
    rowPerm.resize(this->_nrows);
    for (int ii = 0; ii < rows; ii++) {
      this->_rowPerm[ii] = ii;
    }
    auto sortingFunc = [&](const int &a, const int &b) { return (rowSizes[a] > rowSizes[b]); };
    std::sort(this->_rowPerm.begin(), this->_rowPerm.end(), sortingFunc);

    // Now that rows are sorted we can easily find the max row size
    this->_maxRowSize = rowSizes[this->_rowPerm[0]];

    // For each row, we can sort in order of column index then put entries in the flat col index and value arrays
    for (int rowInd = 0; rowInd < this->_nrows; rowInd++) {
      rowSize = rowSizes[rowInd];
      if (rowSize <= 0) {
        break;
      }

      std::vector<int> colIndCopy(rowSize);
      std::vector<fp_type> valCopy(rowSize);

      // Make copies of the current row
      for (int ii = 0; ii < rowSize; ii++) {
        colIndCopy[ii] = colIndMatrix[rowInd][colPerm[ii]];
        valCopy[ii] = valMatrix[rowInd][colPerm[ii]];
      }

      // Create a permutation vector for the column indices and sort it
      std::vector<int> colPerm(rowSize);
      for (int ii = 0; ii < rowSize; ii++) {
        colPerm[ii] = ii;
      }
      auto sortingFunc = [&](const int &a, const int &b) { return (colIndCopy[rowInd][a] < colIndCopy[rowInd][b]); };
      std::sort(colPerm.begin(), colPerm.end(), sortingFunc);

      // And now put the sorted values back into the colInd and val matrices
      for (int ii = 0; ii < rowSize; ii++) {
        colIndMatrix[rowInd][ii] = colIndCopy[colPerm[ii]];
        valMatrix[rowInd][ii] = valCopy[colPerm[ii]];
      }
    }

    // Now we can put the column indices and values into the flattened arrays in the right order
    int entryCount = 0;

    this->_colIndices = new int[this->_nnz];
    this->_values = new double[this->_nnz];
    this->_jdPtrs = new int[this->_maxRowSize + 1];
    this->_jdPtrs[0] = 0;

    // Descend down each column until we hit a row that doesn't have an entry for that column
    for (int colInd = 0; colInd < this->_maxRowSize; colInd++) {
      for (int rowInd = 0; rowInd < this->_nrows; rowInd++) {
        if (rowSizes[rowInd] < colInd) {
          this->_jdPtrs[colInd + 1] = entryCount + 1;
          break;
        }
        this->_colIndices[entryCount] = colIndMatrix[rowInd][colInd];
        this->_values[entryCount] = valMatrix[rowInd][colInd];
      }
    }

    // --- Finally, now that the matrix is assembled we want to release all of the memory used for the original index
    // map ---
    this->_buildCoeff.clear();

    // --- For debugging, print out the stored matrix data structures ---
    printf("values = [");
    for (int ii = 0; ii < this->_nnz; ii++) {
      printf("%f, ", this->_values[ii]);
    }
    printf("]\n\n");

    printf("colIndices = [");
    for (int ii = 0; ii < this->_nnz; ii++) {
      printf("%f, ", this->_colIndices[ii]);
    }
    printf("]\n\n");

    printf("jdPtrs = [");
    for (int ii = 0; ii < (this->_maxRowSize + 1); ii++) {
      printf("%f, ", this->_jdPtrs[ii]);
    }
    printf("]\n\n");

    printf("rowPerm = [");
    for (int ii = 0; ii < this->_nrows; ii++) {
      printf("%f, ", this->_rowPerm[ii]);
    }
    printf("]\n\n");
  }

  template <class fp_type>
  void SparseMatrix_JDS<fp_type>::computeMatVecProduct(const fp_type &x, fp_type &y) {}

} // namespace SpMV
