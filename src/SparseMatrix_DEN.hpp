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
            
            // Return a new SparseMatrix
            SparseMatrix<fp_type> getFormat();
            
            void computeMatVecProduct(/*some args*/);
            
            void unAssemble();
    };

// ==============================================================================
// Method implementations
// ==============================================================================

/*******************/
/* assembleStorage */
/*******************/

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

/*************/
/* getFormat */
/*************/

    template <class fp_type>
    SparseMatrix<fp_type> SparseMatrix_DEN<fp_type>::getFormat()
    {
        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix_DEN::getFormat!" << endl;
        /*
        Code for implementing getFormat for DEN
        */
        //
        if (this->_state == assembled):
          _unAssemble();
        //
        SparseMatrix<fp_type> B;
        // newMat -> _nrows, _ncols, _nnz, _buildCoeff = mat->
        // newMat -> assemble
        // number of rows
        B._nrows = this->_nrows;
        // number of columns
        B._ncols = this->_ncols;
        //
        B._nnz = this->_nnz;
        // _buildCoeff 
        B._buildCoeff = this->_buildCoeff;
        // assemble
        B.assembleStorage();
        //
        return B;
    }

/************************/
/* computeMatVecProduct */
/************************/

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::computeMatVecProduct(/*some args*/)
    {
        /*
        Code for implementing computeMatVecProduct for DEN
        */
    }

/**************/
/* unAssemble */
/**************/

    template <class fp_type>
    void SparseMatrix_DEN<fp_type>::unAssemble()
    {
        assert(this->_state == assembled);

        this->n_rows = NULL;
        this->n_cols = NULL;
        free(this->Aij);

        this->Aij = nullptr;

	    this->_state = building;
	    assert(this->_state == building);
    }

/**************/
/* Destructor */
/**************/

    template <class fp_type> 
    SparseMatrix_DEN<fp_type>::~SparseMatrix_DEN()
    {
        cout << "Hello from SparseMatrix Destructor!" << endl;
        cout << "this->_ncols=" << this->_ncols << endl;
        cout << "this->_nrows=" << this->_nrows << endl;
        cout << "this->_nnz  =" << this->_nnz << endl;

        if (this->Aij != nullptr)
        {
            free(this->Aij);
            this->Aij = nullptr;
            delete[] this->Aij;
        }

        if (this->n_rows != NULL)
        {
            this-> n_rows = NULL;
            delete[] this->n_rows;
        }

        if (this->n_cols != NULL)
        {
            this-> n_cols = NULL;
            delete[] this->n_cols;
        }
        
    }


}

#endif