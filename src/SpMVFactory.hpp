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
    // Abstract Factory object that can create SparseMatrix of any type.
    template <class fp_type>
    class SpMVFactory
    {
        public:
            virtual SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)=0;
    };
    // Concrete factory to instantiate COO SparseMatrix.
    template <class fp_type>
    class SparseMatrixFactory_COO : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)
            {
                return new SpMV::SparseMatrix_COO<fp_type>(nrows,ncols);
            };
    };
    
    // Concrete factory to instantiate ELL SparseMatrix.
    template <class fp_type>
    class SparseMatrixFactory_ELL : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)
            {
                return new SpMV::SparseMatrix_ELL<fp_type>(nrows,ncols);
            };
    };
    // Concrete factory to instantiate DEN SparseMatrix.
    template <class fp_type>
    class SparseMatrixFactory_DEN : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)
            {
                return new SpMV::SparseMatrix_DEN<fp_type>(nrows,ncols);
            };
    };
    // Concrete factory to instantiate JDS SparseMatrix.
    template <class fp_type>
    class SparseMatrixFactory_JDS : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)
            {
                return new SpMV::SparseMatrix_JDS<fp_type>(nrows,ncols);
            };
    };
    // Concrete factory to instantiate CSR SparseMatrix.
    template <class fp_type>
    class SparseMatrixFactory_CSR : public SpMVFactory<fp_type>
    {
        public:
            SpMV::SparseMatrix<fp_type>* createSparseMatrix(const size_t nrows, const size_t ncols)
            {
                return new SpMV::SparseMatrix_CSR<fp_type>(nrows,ncols);
            };
    };

}

#endif