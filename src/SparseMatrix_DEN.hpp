/*
=============================================================================
Dense Matrix Format (DEN) implementation
=============================================================================
@File    :   SparseMatrix_DEN.hpp
@Date    :   2022/11/06
*/


#ifndef __SPMV570_DEN__
#define __SPMV570_DEN__

#include "SparseMatrix.hpp"

// ==============================================================================
// Class declaration
// ==============================================================================

namespace SpMV
{
    template <class fp_type>
    class SparseMatrix_DEN : public SparseMatrix<fp_type>
    {
        private:
            size_t n_rows; // number of rows of the dense matrix
            size_t n_cols; // number of cols of the dense matrix
            fp_type* Aij = nullptr;
        
        public:
            SparseMatrix_DEN(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols){}
            
            virtual ~SparseMatrix_DEN();
            
            void assembleStorage();
            
            void getFormat(/*some args*/);
            
            void computeMatVecProduct(/*some args*/);
            
            void unAssemble();
    };

// ==============================================================================
// Method implementations
// ==============================================================================

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::assembleStorage()
    {
        assert(this->_state == building);
        cout << "Hello from SparseMatrix_DEN::assembleStorage!" << endl;

        //Convert this buildCoeff dictionary to n_rows, n_cols, Aij
        
        /*
        Code for implementing assembleStorage for DEN
        */

        // Destroy _buildCoeff

        this->_state = assembled;
        assert(this->_state == assembled);
    }

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::getFormat(/*some args*/)
    {
        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix_DEN::getFormat!" << endl;

        /*
        Code for implementing getFormat for DEN
        */      
    }

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::computeMatVecProduct(/*some args*/)
    {
        /*
        Code for implementing computeMatVecProduct for DEN
        */
    }

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::unAssemble()
    {
        assert(this->_state == assembled);

	    free(this->Aij);

        this->n_rows = NULL;
        this->n_cols = NULL;
	    this->Aij = nullptr;

	    this->_state = building;
	    assert(this->_state == building);
    }

    template <class fp_type> 
    SparseMatrix_DEN<fp_type>::~SparseMatrix_DEN()
    {
        cout << "Hello from SparseMatrix Destructor!" << endl;
        cout << "this->_ncols=" << this->_ncols << endl;
        cout << "this->_nrows=" << this->_nrows << endl;
        cout << "this->_nnz  =" << this->_nnz << endl;

        if (this->Aij != NULL)
            free(this->Aij);

        this->n_cols = NULL;
        this->n_rows = NULL;
        this->Aij = NULL;

        delete[] this->n_rows;
        delete[] this->n_cols;
        delete[] this->Aij;
        
    }


}

#endif