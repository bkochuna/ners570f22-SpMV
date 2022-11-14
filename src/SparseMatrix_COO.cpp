#include "SparseMatrix_COO.hpp"

using namespace SpMV;

template class SpMV::SparseMatrix_COO<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix_COO<double>; // Forces binary code to be generated for double data type

template <class fp_type>
void SparseMatrix_COO<fp_type>::assembleStorage() {
  assert(this->_state == building);

  // Convert this buildCoeff dictionary to I, J, val
  this->I = (size_t *)malloc(this->_nnz * sizeof(size_t));
  this->J = (size_t *)malloc(this->_nnz * sizeof(size_t));
  this->val = (fp_type *)malloc(this->_nnz * sizeof(fp_type));

  // Destroy _buildCoeff

  this->_state = assembled;
  assert(this->_state == assembled);
}

template <class fp_type>
SparseMatrix_COO<fp_type>::~SparseMatrix_COO() {
  cout << "#### COO Destructor NOT IMPLEMENTED!" << endl;
  assert(false);
}

template <class fp_type>
void SparseMatrix_COO<fp_type>::computeMatVecProduct(const fp_type x[], fp_type y[]) {
  cout << "#### COO MatVec NOT IMPLEMENTED!" << endl;
  assert(false);
}

template <class fp_type>
void SparseMatrix_COO<fp_type>::_unAssemble() {
  cout << "#### COO _unAssemble NOT IMPLEMENTED!" << endl;
  assert(false);
}
