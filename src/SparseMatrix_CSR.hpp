/*
=============================================================================
Compressed Sparse Row Matrix (CSR) implementation
=============================================================================
@File    :   SparseMatrix_CSR.hpp
@Date    :   2022/11/05

*/
#pragma once

#include "SparseMatrix.hpp"
#include <algorithm>
#include <vector>

// ==============================================================================
// Class declaration
// ==============================================================================

namespace SpMV {
template <class fp_type> class SparseMatrix_CSR : public SparseMatrix<fp_type> {

public:
  SparseMatrix_CSR(const size_t nrows, const size_t ncols)
      : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {}
  SparseMatrix_CSR(const size_t nrows, const size_t ncols, size_t *I,
                   fp_type *val, size_t *ptr)
      : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {}
  virtual ~SparseMatrix_CSR();
  void assembleStorage();

  void getFormat(/*some args*/);



  void computeMatVecProduct(const fp_type *x, fp_type *y);

  //   SparseMatrix_CSR(const int nrows, const int ncols);

private:
  size_t *I = nullptr;    // Column pointer
  fp_type *val = nullptr; // non zero value
  size_t *ptr = nullptr;  // row pointer
  void _unAssemble();
}; // class SparseMatrix_CSR

// ==============================================================================
// Method implementations
// ==============================================================================

template <class fp_type> void SparseMatrix_CSR<fp_type>::assembleStorage() {
  assert(this->_state == building);
  cout << "Hello from SparseMatrix_COO::assembleStorage!" << endl;

  // Convert this buildCoeff dictionary to I, J, val
  this->I = new int[this->_nnz];
  this->val = new fp_type[this->_nnz];
  this->ptr = new size_t[this->_nnz];

  // we start to assemble our matrix here
  size_t n = 0;
  size_t i = 0;
  for (auto coeff : this->_buildCoeff) {
    while (n < this->_nnz && I[n] == coeff.first.first) {

      // set the columns, values and row pinters
      I[n] = coeff.first.first;
      val[n] = coeff.second;
      n += 1;
    }
    ptr[i + 1] = n;
    i += 1;
  }

  // Destroy _buildCoeff
  this->_clearBuildCoeff();

  // now the state is assembled and make sure it assembled
  this->_state = assembled;
  assert(this->_state == assembled);
}

template <class fp_type> SparseMatrix_CSR<fp_type>::~SparseMatrix_CSR() {
  cout << "Hello from SparseMatrix Destructor!" << endl;
  cout << "this->_ncols=" << this->_ncols << endl;
  cout << "this->_nrows=" << this->_nrows << endl;
  cout << "this->_nnz  =" << this->_nnz << endl;
  // delete all the memory allocated pointers
  delete[] this->val;
  delete[] this->I;
  delete[] this->ptr;
}

template <class fp_type>
void SparseMatrix_CSR<fp_type>::computeMatVecProduct(const fp_type *x,
                                                     fp_type *y) {

  assert(this->_state == assembled);

  // ensure that output vector is all zeros at beginning of calculation
  for (int i = 0; i < this->_nrows, i++) {
    y[i] = 0.0;
  }

  // compute matrix vector multiplication
  // i is row index, j is index in the val and I array
  int j = 0;
  for (int i = 0; i < this->_nrows, i++) {
    // while we're not on the last row and j is less than the starting index of
    // the next row, or (we are on the last row) and j is less than the number
    // of nonzero entries
    while (((i < this->_nrows - 1) && (j < this->ptr[i + 1] - 1)) ||
           (j < this->_nnz)) {
      y[i] += this->val[j] * x[this->ptr[j]];
      j += 1;
    }
  }
}

template <class fp_type> void SparseMatrix_CSR<fp_type>::getFormat() {
  cout << "Hello from SparseMatrix_CSR::getFormat!" << endl;

  if (this->_state == assembled)
    _unAssemble();
  SparseMatrix<fp_type> B;
  B._ncols = this->_ncols;
  B._nrows = this->_nrows;
  B._nnz = this->_nnz;
  B._buildCoeff = this->_buildCoeff;
  B.assembleStorage();
  return B;

}

template <class fp_type> void SparseMatrix_CSR<fp_type>::_unAssemble() {
  // check if the matrix is assembled
  assert(this->_state == assembled);

  // change the state to building (state before assembled)
  // setCoefficient checks whether the state is building
  this->_state = building;
  assert(this->_state == building);

  // recreate buildCoeff
  int n = this->_nrows;
  int nnz = this->_nnz;
  this->_nnz = 0;

  // loop over row pointer
  for (int ii = 0; ii < n; ii++) {
    // number of components in a row
    if (ii < n - 1) {
      int len = ptr[ii + 1] - ptr[ii]
    }; else {
      int len = nnz - ptr[ii];
    }
    // loop over the components in the row
    for (int idx = 0; idx < len; idx++) {
      int ri = ptr[ii];
      this->setCoefficient(ptr[ii], I[idx + ri - 1], val[idx + ri - 1]);
    }
  }

  // deallocate pointers
  free(this->I);
  free(this->ptr);
  free(this->val);

  // assign to null pointer
  this->I = nullptr;
  this->val = nullptr;
  this->ptr = nullptr;
}
} // namespace SpMV
