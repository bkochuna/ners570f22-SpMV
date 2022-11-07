#ifndef __SPMV570_FACTORY__
#define __SPMV570_FACTORY__

#include "SparseMatrix.hpp"
#include "SparseMatrix_COO.hpp"

namespace SpMV
{
    template <class fp_type>
    class SpMVFactory
    {
        public:
            virtual SpMV::SparseMatrix<fp_type>* createSparseMatrix()=0;
    };
    template <class fp_type>
    class SparseMatrixFactory_COO : public SpMVFactory
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_COO();
            }
    };
    template <class fp_type>
    class SparseMatrixFactory_ELL : public SpMVFactory
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_ELL();
            }
    };
    template <class fp_type>
    class SparseMatrixFactory_DEN : public SpMVFactory
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_DEN();
            }
    };
    template <class fp_type>
    class SparseMatrixFactory_JDS : public SpMVFactory
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_JDS();
            }
    };
    template <class fp_type>
    class SparseMatrixFactory_CSR : public SpMVFactory
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_CSR();
            }
    };

}

#endif