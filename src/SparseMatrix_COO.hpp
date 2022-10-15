#ifndef __SPMV570_COO__
#define __SPMV570_COO__

#include "SparseMatrix.hpp"

namespace SpMV
{
    /**
     * @brief A sparse matrix stored in COO (coordinate format)
     *
     * @tparam fp_type Numeric type of matrix entries
     */
    template <class fp_type>
    class SparseMatrix_COO : public SparseMatrix<fp_type>
    {

        private:
            size_t* I = nullptr;    ///< Row indices list
            size_t* J = nullptr;    ///< Column indices list
            fp_type* val = nullptr; ///< Non-zero entries list

        public:
            /**
             * @brief Construct a new COO Sparse Matrix of given dimensions
             *
             * @param rows Number of rows
             * @param cols Number of columns
             */
            SparseMatrix_COO(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols)
            {
                cout << "Hello From SparseMartix_COO" << endl;
            };

            /**
             * @brief Assemble the COO data structures
             *
             */
            void assembleStorage();

            /**
             * @brief I don't know what this does
             *
             */
            /*Some return type*/ void getFormat(/*some args*/);

    };

    template <class fp_type>
    void SparseMatrix_COO<fp_type>::assembleStorage()
    {
        assert(this->_state == building);
        cout << "Hello from SparseMatrix_COO::assembleStorage!" << endl;

        //Convert this buildCoeff dictionary to I, J, val
        this->I = (size_t*)malloc(this->_nnz * sizeof(size_t));
        this->J = (size_t*)malloc(this->_nnz * sizeof(size_t));
        this->val = (fp_type*)malloc(this->_nnz * sizeof(fp_type));

        size_t n=0;
        for(auto coeff : this->_buildCoeff)
        {
            I[n]   = coeff.first.first;
            J[n]   = coeff.first.second;
            val[n] = coeff.second;
            n += 1;
        }

        // Destroy _buildCoeff

        this->_state = assembled;
        assert(this->_state == assembled);
    }

    template <class fp_type>
    void SparseMatrix_COO<fp_type>::getFormat()
    {
        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix_COO::getFormat!" << endl;

        //return new SparseMatrix(this->_ncols,this->_nrows);
    }
}

#endif
