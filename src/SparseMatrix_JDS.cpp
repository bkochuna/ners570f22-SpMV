#include "SparseMatrix_JDS.hpp"

using namespace SpMV;

template class SpMV::SparseMatrix_JDS<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix_JDS<double>; // Forces binary code to be generated for double data type

// ==============================================================================
// Method implementations
// ==============================================================================

template <class fp_type>
SparseMatrix_JDS<fp_type>::SparseMatrix_JDS(const size_t nrows,
                                            const size_t ncols,
                                            size_t perm[],
                                            fp_type jdiag[],
                                            size_t col_ind[],
                                            size_t jd_ptr[],
                                            size_t max_row_size)
    : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {
  this->_state = building;

  this->_nnz = jd_ptr[max_row_size];
  this->_maxRowSize = max_row_size;

  this->_colIndices = new size_t[this->_nnz];
  this->_values = new fp_type[this->_nnz];
  for (int i = 0; i < this->_nnz; i++) {
    this->_colIndices[i] = col_ind[i];
    this->_values[i] = jdiag[i];
  }
  this->_jdPtrs = new size_t[this->_maxRowSize + 1];
  for (int i = 0; i < this->_maxRowSize + 1; i++) {
    this->_jdPtrs[i] = jd_ptr[i];
  }

  vector<size_t> vecPerm(perm, perm + nrows);
  this->_rowPerm = vecPerm;

  this->_state = assembled;

  assert(this->_state == assembled);
}

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
  if (this->_colIndices != NULL) {
    delete[] this->_colIndices;
    this->_colIndices = NULL;
  }

  if (this->_values != NULL) {
    delete[] this->_values;
    this->_values = NULL;
  }

  if (this->_jdPtrs != NULL) {
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
void SparseMatrix_JDS<fp_type>::_unAssemble() {
  // Only makes sense to unassemble if the matrix is assembled
  assert(this->_state == assembled);

  // Set the state to building, otherwise `setCoefficient` will call this method and that results in a segfault
  this->_state = building;

  // --- Loop through all the assembled data and call `setCoefficient` to add it to the `_buildCeff` map ---
  this->_nnz = 0; // Need to reset the nonzero count because setCoefficient will increment it
  for (int ii = 0; ii < this->_maxRowSize; ii++) {
    int colLength = this->_jdPtrs[ii + 1] - this->_jdPtrs[ii];
    int offset = this->_jdPtrs[ii];
    for (int jj = 0; jj < colLength; jj++) {
      size_t rowInd = this->_rowPerm[jj];
      size_t colInd = this->_colIndices[offset + jj];
      fp_type val = this->_values[offset + jj];
      this->setCoefficient(rowInd, colInd, val);
    }
  }

  // --- Now that the matrix is un-assembled we can release all of the memory used for the assembled storage ---
  if (this->_colIndices != NULL) {
    delete[] this->_colIndices;
    this->_colIndices = NULL;
  }

  if (this->_values != NULL) {
    delete[] this->_values;
    this->_values = NULL;
  }

  if (this->_jdPtrs != NULL) {
    delete[] this->_jdPtrs;
    this->_jdPtrs = NULL;
  }
}

template <class fp_type>
SparseMatrix<fp_type> *SparseMatrix_JDS<fp_type>::getFormat(string fmt) {
  if (this->_state == assembled) {
    _unAssemble();
  }
  // Create pointer to new matrix that will be returned
  SparseMatrix<fp_type> *ptr_A = nullptr;

  // --- Create the new matrix in the requested format for ptr_a to point to ---
  // if (fmt == "DEN") {
  //   ptr_A = new SparseMatrix_DEN<fp_type>(this->_nrows, this->_ncols);
  // }
  // else if (fmt == "COO") {
  //   ptr_A = new SparseMatrix_COO<fp_type>(this->_nrows, this->_ncols);
  // }
  // else if (fmt == "CSR") {
  //   ptr_A = new SparseMatrix_CSR<fp_type>(this->_nrows, this->_ncols);
  // }
  // else if (fmt == "JDS") {
  //   ptr_A = new SparseMatrix_JDS<fp_type>(this->_nrows, this->_ncols);
  // }
  // else if (fmt == "ELL") {
  //   ptr_A = new SparseMatrix_ELL<fp_type>(this->_nrows, this->_ncols);
  // }

  // Copy the nonzero entry data to the new matrix and assemble it
  // ptr_A->_buildCoeff = this->_buildCoeff;
  // ptr_A->assembleStorage();

  return ptr_A;
}
