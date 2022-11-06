/*
=============================================================================
Jagged Diagonal Sparse Matrix (CSR) implementation
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
  virtual ~SparseMatrix_CSR();
  void assembleStorage();

  void getFormat(/*some args*/);

  void computeMatVecProduct(/*some args*/);
  
  void unAssemble();
  //   SparseMatrix_CSR(const int nrows, const int ncols);

private:
  size_t *I = nullptr;
  fp_type *val = nullptr;
  size_t *ptr = nullptr;

}; // class SparseMatrix_CSR

// ==============================================================================
// Method implementations
// ==============================================================================

template <class fp_type> void SparseMatrix_CSR<fp_type>::assembleStorage() {
  assert(this->_state == building);
  cout << "Hello from SparseMatrix_COO::assembleStorage!" << endl;

  // Convert this buildCoeff dictionary to I, J, val
  this->I = (size_t *)malloc(this->_nnz * sizeof(size_t));
  this->val = (fp_type *)malloc(this->_nnz * sizeof(fp_type));
  this->ptr = (unsigned int *)malloc(((this->rows) + 1) * sizeof(unsigned int));

  size_t n = 0;
  size_t i = 0;
  for (auto coeff : this->_buildCoeff) {
    while (n < this->_nnz && I[n] == coeff.first.first) {

      I[n] = coeff.first.first;
      val[n] = coeff.second;
      n += 1;
    }
    ptr[i + 1] = n;
    i += 1;
  }

  // Destroy _buildCoeff

  this->_state = assembled;
  assert(this->_state == assembled);
}

template <class fp_type> SparseMatrix_CSR<fp_type>::~SparseMatrix_CSR() {
  cout << "Hello from SparseMatrix Destructor!" << endl;
  cout << "this->_ncols=" << this->_ncols << endl;
  cout << "this->_nrows=" << this->_nrows << endl;
  cout << "this->_nnz  =" << this->_nnz << endl;
  if (this->val != NULL)
    free(this->val);
  if (this->I != NULL)
    free(this->I);
  if (this->ptr != NULL)
    free(this->ptr->ptr);
  this->val = NULL;
  this->I = NULL;
  this->ptr = NULL;

  delete[] this->val;
  delete[] this->I;
  delete[] this->ptr;
}

template <class fp_type>
void SparseMatrix_CSR<fp_type>::computeMatVecProduct() {}

template <class fp_type> void SparseMatrix_CSR<fp_type>::getFormat() {}

template <class fp_type>
void SparseMatrix_CSR<fp_type>::unAssemble()
{
	assert(this->_state == assembled);

	free(this->I);
	free(this->ptr);
	free(this->val);

	this->_state = building;
	assert(this->_state == building);
}
} // namespace SpMV
