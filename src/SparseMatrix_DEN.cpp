#include "SparseMatrix_DEN.hpp"

using namespace SpMV;

template class SpMV::SparseMatrix_DEN<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix_DEN<double>; // Forces binary code to be generated for double data type

// ==============================================================================
// Method implementations
// ==============================================================================
template <class fp_type>
void SparseMatrix_DEN<fp_type>::assembleStorage() {
  assert(this->_state == building);

  cout << "#### DEN assembleStorage() NOT IMPLEMENTED!" << endl;
  assert(false);

  // Convert this buildCoeff dictionary to n_rows, n_cols, Aij

  /*
  Code for implementing assembleStorage for DEN
  */

  // Destroy _buildCoeff

  this->_state = assembled;
  assert(this->_state == assembled);
}

template <class fp_type>
void SparseMatrix_DEN<fp_type>::computeMatVecProduct(const fp_type x[], fp_type y[]) {
  cout << "#### DEN MatVec NOT IMPLEMENTED!" << endl;
  assert(false);
  /*
  Code for implementing computeMatVecProduct for DEN
  */
}

template <class fp_type>
void SparseMatrix_DEN<fp_type>::_unAssemble() {
  assert(this->_state == assembled);

  // Assign values back to _buildcoeff

  free(this->_A); // free the pointer

  this->_A = nullptr;

  this->_state = building;
  assert(this->_state == building);
}

template <class fp_type>
SparseMatrix_DEN<fp_type>::~SparseMatrix_DEN() {

  if (this->_A != nullptr) {

    free(this->_A); // free the pointer
    this->_A = nullptr;
  }
}
