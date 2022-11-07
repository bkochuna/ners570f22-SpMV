#ifndef __SPMV570_COO__
#define __SPMV570_COO__

#include "SparseMatrix.hpp"

namespace SpMV
{
    template <class fp_type>
    class SparseMatrix_COO : public SparseMatrix<fp_type>
    {

        //using SparseMatrix<fp_type>::SparseMatrix;

        private:
            size_t* I = nullptr;
            size_t* J = nullptr;
            fp_type* val = nullptr;
        
        public:
            SparseMatrix_COO(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols)
            {
                cout << "Hello From SparseMartix_COO" << endl;
            };
	    virtual ~SparseMatrix_COO();
            void assembleStorage();
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
    void SparseMatrix_COO<fp_type>::~SparseMatrix_COO()
    {
	    if (this->I != nullptr)
	    {
		    free(this->I);
		    this->I = nullptr;
	    }
	    if (this->J != nullptr)
            {
                    free(this->J);
                    this->J = nullptr;
            }
	    if (this->val != nullptr)
            {
                    free(this->val);
                    this->val = nullptr;
            }
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
