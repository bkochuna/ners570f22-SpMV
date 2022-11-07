#ifndef __SPMV570_ELL__
#define __SPMV570_ELL__

#include "SparseMatrix.hpp"

namespace SpMV
{
    template <class fp_type>
    class SparseMatrix_ELL : public SparseMatrix<fp_type>
    {

        //using SparseMatrix<fp_type>::SparseMatrix;

        private:
            size_t* I = nullptr;
            size_t* J = nullptr;
            fp_type* val = nullptr;
        
        public:
            SparseMatrix_ELL(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols)
            {
                cout << "Hello From SparseMartix_ELL" << endl;
            };
            
            virtual ~SparseMatrix_ELL();

            void assembleStorage();
            /*Some return type*/ void getFormat(/*some args*/);

    };

    template <class fp_type>
    void SparseMatrix_ELL<fp_type>::assembleStorage()
    {
        assert(this->_state == building);
        cout << "Hello from SparseMatrix_ELL::assembleStorage!" << endl;

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

    template <class fp_type> SparseMatrix_ELL<fp_type>::~SparseMatrix_ELL() {
    	cout << "Hello from SparseMatrix_ELL Destructor!" << endl;

        if (this->I != NULL) {
            free(this->I);
            this->I = NULL;
        }

        if (this->J != NULL) {
            free(this->J);
            this->J = NULL;
        }

        if this(->val != NULL) {
            free(this->val);
            this->val = NULL;
        }
    }

    template <class fp_type>
    void SparseMatrix_ELL<fp_type>::getFormat()
    {
        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix_ELL::getFormat!" << endl;
        
        //return new SparseMatrix(this->_ncols,this->_nrows);
    }
}

#endif
