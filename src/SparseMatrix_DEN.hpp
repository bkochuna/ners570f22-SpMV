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
            
            /**
             * @brief Overloaded constructor:
             * Construct a new DEN Sparse Matrix of given dimensions AND dense input array
             * 
             * @note Skips the building phase
             *
             * @param rows Number of rows
             * @param cols Number of columns
             * @param perm Vector of row permutations
             * @param a Dense array of entries
             */
            SparseMatrix_DEN(const size_t nrows, const size_t ncols, fp_type **a) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols)    
            {
                assert(this->_state==undefined);
                this->_state=initialized;
                this->Aij=a;
                this->_state=assembled;

                assert(this->_state==assembled);

            }

            virtual ~SparseMatrix_DEN();
            
            void assembleStorage();
            
            // Return a new SparseMatrix

            SparseMatrix<fp_type>* getFormat();

            
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

    SparseMatrix<fp_type>* SparseMatrix_DEN<fp_type>::getFormat()

    {
        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix_DEN::getFormat!" << endl;
        /*
        Code for implementing getFormat for DEN
        */
        if (this->_state == assembled)
        {
          _unAssemble();
        }
        // Create pointer to new matrix that will be returned
        SparseMatrix<fp-type>* ptr_A = nullptr;
        // --- Create the new matrix in the requested format for ptr_a to point to ---
        if (fmt == "DEN") {
          ptr_A = new SparseMatrix_DEN<fp_type>(this->_nrows, this->_ncols);
        }
        else if (fmt == "COO") {
          ptr_A = new SparseMatrix_COO<fp_type>(this->_nrows, this->_ncols);
        }
        else if (fmt == "CSR") {
          ptr_A = new SparseMatrix_CSR<fp_type>(this->_nrows, this->_ncols);
        }
        else if (fmt == "JDS") {
          ptr_A = new SparseMatrix_JDS<fp_type>(this->_nrows, this->_ncols);
        }
        else if (fmt == "ELL") {
          ptr_A = new SparseMatrix_ELL<fp_type>(this->_nrows, this->_ncols);
        }

        // Copy the nonzero entry data to the new matrix and assemble it
        ptr_A->_buildCoeff = this->_buildCoeff;
        ptr_A->assembleStorage();

        return ptr_A;
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


        this->n_rows = NULL;  //set the variable to NULL
        this->n_cols = NULL;  //set the variable to NULL
        free(this->Aij);      //free the pointer


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

            free(this->Aij);          //free the pointer
            this->Aij = nullptr;
            delete[] this->Aij;       //delete the pointer
        }

        if (this->n_rows != NULL)      
        {
            this-> n_rows = NULL;     //set the variable to NULL
            delete[] this->n_rows;    //delete the variable

        }

        if (this->n_cols != NULL)
        {

            this-> n_cols = NULL;     //set the variable to NULL
            delete[] this->n_cols;    //delete the variable

        }
        
    }


}

#endif