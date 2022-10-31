#include "SparseMatrix.hpp"
#include "SparseMatrix_COO.hpp"
//#include "SparseMatrix_DEN.hpp"
//#include "SparseMatrix_CSR.hpp"
//#include "SparseMatrix_ELL.hpp"
//#include "SparseMatrix_JDS.hpp"

namespace SpMV
{
    enum FormatType {DEN, COO, CSR, ELL, JDS}

    template <class fp_type>
    SparseMatrix<fp_type>* Formatter(SparseMatrix<fp_type> matx, FormatType fmt)
    {
    if (_state = assembled)
    {
        //Unassemble build
        cout << "Unassembled" << endl; 
    switch (fmt)
    {
    case DEN
        //SparseMatrix_DEN
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
        //SparseMatrix_DEN
    
    default:
        break;
    }
    }
    }



    
}
