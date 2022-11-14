#include "SparseMatrix.hpp"

#include <cassert>

using namespace SpMV;

template class SpMV::SparseMatrix<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix<double>; // Forces binary code to be generated for double data type

template <class fp_type>
SparseMatrix<fp_type>::SparseMatrix(const int nrows, const int ncols)
    : _nrows(nrows), _ncols(ncols), _nnz(0), _state(initialized) {
  assert(this->_state == initialized);
}

template <class fp_type>
SparseMatrix<fp_type>::~SparseMatrix() {
  this->_state = undefined;
  assert(this->_state == undefined);
}

template <class fp_type>
void SparseMatrix<fp_type>::setCoefficient(const size_t row, const size_t col, const fp_type aij) {
  assert(this->_state != undefined);

  if (this->_state == assembled)
    this->_unAssemble();

  this->_state = building;

  this->_buildCoeff[make_pair(row, col)] = aij;
  this->_nnz = this->_buildCoeff.size();
  assert(this->_state == building);
}
