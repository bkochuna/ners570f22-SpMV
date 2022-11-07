#ifndef __SPMV570_FACTORY__
#define __SPMV570_FACTORY__

#include "SparseMatrix.hpp"
#include "SparseMatrix_COO.hpp"
#include "SparseMatrix_ELL.hpp"
#include "SparseMatrix_JDS.hpp"
#include "SparseMatrix_CSR.hpp"
#include "SparseMatrix_DEN.hpp"

namespace SpMV
{
    template <class fp_type>
    class SpMVFactory
    {
        public:
            virtual SpMV::SparseMatrix<fp_type>* createSparseMatrix()=0;
    };

    template <class fp_type>
    class SparseMatrixFactory_COO : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_COO<fp_type>();
            };
    };
    template <class fp_type>
    class SparseMatrixFactory_ELL : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_ELL<fp_type>();
            };
    };
    template <class fp_type>
    class SparseMatrixFactory_DEN : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_DEN<fp_type>();
            };
    };
    template <class fp_type>
    class SparseMatrixFactory_JDS : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_JDS<fp_type>();
            };
    };
    template <class fp_type>
    class SparseMatrixFactory_CSR : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix()
            {
                return SpMV::SparseMatrix_CSR<fp_type>();
            };
    };

}

#endif