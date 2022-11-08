#include "SparseMatrix.hpp"
#include "SparseMatrix_COO.hpp"
#include "SparseMatrix_DEN.hpp"
#include "SparseMatrix_CSR.hpp"
#include "SparseMatrix_ELL.hpp"
#include "SparseMatrix_JDS.hpp"

namespace SpMV
{
    enum FormatType {DEN, COO, CSR, ELL, JDS};
    template <class fp_type>
    SparseMatrix<fp_type>* Formatter(SparseMatrix<fp_type> matx, FormatType fmt)
    {
        if (_state = assembled)
        {
            //Unassemble build
            std::cout << "Unassembled" << endl; 
            switch (fmt)
            {
                case DEN
                    //SparseMatrix_DEN
                    ptr_A = new SparseMatrix_DEN<fp_type>(matx._nrows, matx._ncols);
                    ptr_A->_buildCoeff = matx._buildCoeff;
                    ptr_A->assembleStorage();
                    break;
                case COO
                    //SparseMatrix_COO
                    break;
                case CSR
                    //SparseMatrix_CSR
                    break;
                case ELL
                    //SparseMatrix_ELL
                    break;
                case JDS
                    //SparseMatrix_JDS
                    ptr_A = new SparseMatrix_JDS<fp_type>(matx._nrows, matx._ncols);
                    ptr_A->_buildCoeff = matx._buildCoeff;
                    ptr_A->assembleStorage();
                default:
                    break;
            }
        }
    }
}
