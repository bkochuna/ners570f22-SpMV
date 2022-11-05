#include "SparseMatrix.hpp"
#include "SparseMatrix_JDS.hpp"
#include <iostream>

template class SpMV::SparseMatrix<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix<double>; // Forces binary code to be generated for double data type

int main(int argc, char *argv[]) {
  std::cout << "Hello World!" << std::endl;

  SpMV::SparseMatrix<double> *ptr_A = nullptr;
  SpMV::SparseMatrix_JDS<double> *ptr_B = nullptr;

  ptr_A = new SpMV::SparseMatrix_JDS<double>(5, 8);

  ptr_B = (SpMV::SparseMatrix_JDS<double> *)ptr_A;

  ptr_B->setCoefficient(1, 1, 1.0);
  ptr_B->setCoefficient(2, 2, 2.0);
  ptr_B->setCoefficient(1, 1, -1.0);

  ptr_A->assembleStorage();
  cout << "What does our matrix look like?" << endl;
  // New scoping unit. This means variables defined in here, stay here.
  {
    SpMV::SparseMatrix_JDS<float> A = SpMV::SparseMatrix_JDS<float>(2, 2);
    cout << "Do stuff with A" << endl;
    // A.assembleStorage();
    // A.setCoefficient(5,6, 1.0);

    // SpMV::SparseMatrix B = A.getFormat();
  }

  delete (ptr_A);
  ptr_A = NULL;

  return 0;
}
