#include "SparseMatrix.hpp"
<<<<<<< HEAD
=======
#include "SparseMatrix_COO.hpp"
>>>>>>> b045fc8d40a89454938b838d95a8426eb9c11d1d
#include "SparseMatrix_CSR.hpp"
#include "SparseMatrix_DEN.hpp"

template class SpMV::SparseMatrix<float>;  // Forces binary code to be generated for float data type
template class SpMV::SparseMatrix<double>; // Forces binary code to be generated for double data type

int main(int argc, char *argv[]) {
  std::cout << "Hello World!" << std::endl;

  SpMV::SparseMatrix<double> *ptr_A = nullptr;
  SpMV::SparseMatrix_CSR<double> *ptr_B = nullptr;
  SpMV::SparseMatrix_DEN<double> *ptr_C = nullptr;

  ptr_A = new SpMV::SparseMatrix_CSR<double>(5, 8);

  ptr_B = (SpMV::SparseMatrix_CSR<double> *)ptr_A;

  ptr_C = (SpMV::SparseMatrix_DEN<double> *)ptr_C;

  ptr_B->setCoefficient(1, 1, 1.0);
  ptr_B->setCoefficient(2, 2, 2.0);
  ptr_B->setCoefficient(1, 1, -1.0);

  ptr_C->setCoefficient(1, 1, 1.0);
  ptr_C->setCoefficient(2, 2, 2.0);

  ptr_A->assembleStorage();
  ptr_C->assembleStorage();

  cout << "What does our matrix look like?" << endl;
  // New scoping unit. This means variables defined in here, stay here.
  {
    SpMV::SparseMatrix_CSR<float> A = SpMV::SparseMatrix_CSR<float>(2, 2);
    cout << "Do stuff with A" << endl;
    // A.assembleStorage();
    // A.setCoefficient(5,6, 1.0);

    // SpMV::SparseMatrix B = A.getFormat();
  }

  delete (ptr_A);
  ptr_A = NULL;

  return 0;
}
