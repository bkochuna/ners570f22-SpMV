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
            size_t** J = nullptr;
            size_t max_nnz = 0;
            fp_type** val = nullptr;
        
        public:
            /**
             * @brief Construct a new ELL Sparse Matrix of given dimensions
             *
             * @param nrows Number of rows
             * @param ncols Number of columns
             */
            SparseMatrix_ELL(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols) {};
            /* Overloaded constructor I have no idea if this is right */
            // SparseMatrix_ELL(const size_t nrows, const size_t ncols, size_t data[],size_t nnz[]):SparseMatrix(nrows,ncols);
            
            /**
             * @brief Destructor for ELL Sparse Matrix format. Destory objects created
             *
             */
            virtual ~SparseMatrix_ELL();

            /**
             * @brief Assemble the ELL data structures from the general map based data structure used in the building phase
             *
             */
            void assembleStorage();

            /**
             * @brief I don't know what this does
             *  // Could be getting the nonzero ncols and nrows and creating a new SparseMatrix...
             */
            SparseMatrix<fp_type> void getFormat();
            
            /**
             * @brief Compute the product of this matrix and a vector (y = Ax)
             *
             * @note The contents of y are overwritten by this operation
             *
             * @param x Array to multiply with
             * @param y Array to store result in
             */
            void computeMatVecProduct(const fp_type x[], fp_type y[]);

            /**
             * @brief Convert the assembled matrix data back to the format used for building
             *
             * @note Calling this function will also clear the assembled matrix data
             *
             */
            void _unAssemble();



    };

    template <class fp_type>
    void SparseMatrix_ELL<fp_type>::assembleStorage()
    {
        assert(this->_state == building);
        cout << "Hello from SparseMatrix_ELL::assembleStorage!" << endl;

        //Find the max number of nonzero elements in a given row
        this->max_nnz = 0;
        size_t tmp_max = 0;
        size_t current_row = 0;
        for(auto coeff : this->_buildCoeff) {
            if (coeff.first.first != current_row) {
                if (tmp_max > this->max_nnz) {
                    this->max_nnz = tmp_max;
                }
                tmp_max = 0;
                current_row = coeff.first.first;
            }
            tmp_max += 1;
        }
        if (tmp_max > this->max_nnz) {
            this->max_nnz = tmp_max;
        }

        //Allocate the data and column index arrays
        this->J = new size_t*[this->_nrows];
        this->val = new fp_type*[this->_nrows];
        for (int i = 0; i < this->_nrows; i++) {
            this->J[i] = new size_t[this->max_nnz];
            this->val[i] = new fp_type[this->max_nnz];
        }

        //Fill in values of data and column index arrays
        int j = 0;
        current_row = 0;
        for(auto coeff : this->_buildCoeff)
        {
            if (coeff.first.first != current_row) {
                j = 0;
                current_row = coeff.first.first;
            }
            J[coeff.first.first][j] = coeff.first.second; 
            val[coeff.first.first][j] = coeff.second;
            j += 1;
        }

        // Destroy _buildCoeff
         this->_buildCoeff.clear();

        this->_state = assembled;
        assert(this->_state == assembled);
    }

    template <class fp_type> SparseMatrix_ELL<fp_type>::~SparseMatrix_ELL() {

        if (this->I != NULL) {
            delete[] this->I;
            this->I = NULL;
        }

        if (this->J != NULL) {
            delete[] this->J;
            this->J = NULL;
        }

        if this(->val != NULL) {
            delete[] this->val;
            this->val = NULL;
        }
    }

    template <class fp_type>
    SparseMatrix<fp_type> *SparseMatrix_JDS<fp_type>::getFormat(string fmt) {
    if (this->_state == assembled) {_unAssemble();}
    // Create pointer to new matrix that will be returned
    SparseMatrix<fp_type> *ptr_A = nullptr;

    // Create the new matrix in the requested format for ptr_a to point to ---
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

    template <class fp_type>
    void SparseMatrix_ELL<fp_type>::computeMatVecProduct(const fp_type x[], fp_type y[]) {
        size_t c;
        /* 
        I'm assuning input x and output vector y. 
        Also I'm assuming _maxRow as a class variable that contains the number of maximum nonzero elements for rows 
        This function also assumes a private class variable _col for recording the column indices of elements in each row. Assumes size (N x _maxRow) for array
        This function also assumes a private class variable _val for recording the values of elements in each row. Assumes size (N x _maxRow) for array
        */
        if (this->_state != assembled) {
        assembleStorage();
        }
        // --- Check that the matrix is assembled ---
        assert(this->_state == assembled);

    // Zero the output vector
    #pragma omp parallel for simd schedule(static)
        for (int ii = 0; ii < this->_ncols; ii++) {
        y[ii] = 0.0;
        }

    #pragma omp parallel for simd schedule(static) collapse(2)
        for (int i=0; i< this->_nrows; i++) {
            for (int j=0; j< this->_maxRow; j++) {
                jj = j + this->_maxRow*i; //this row assumes that all elements in the columns are stored in contiguous memory pointers and allows indexing through one single index
                c = this->J[jj];
                if ((c >= 0) && (c < this->_nrows))
                    y[i] += this->val[jj] * x[c];
            }
        }
    }

    template <class fp_type>
    void SparseMatrix_ELL<fp_type>::_unAssemble() {

        assert(this->_state == assembled);

        int i, j;

        // recreate buildCoeff list 
        // assumes data array and column index array are 2d arrays (two levels of pointers)
        // and also assumes empty values at end of row in column index arrays are -1
        for (i = 0; i < this->_nrows; i++) {
            j = 0
            while ((j < this->max_nnz) && (J[i][j] != -1)) {
                this->_buildCoeff[ make_pair(i, J[i][j]) ] = val[i][j];
                j += 1; 
            } 
        } 
        
        free(this->J);
        free(this->val);
        J = nullptr;
        val = nullptr;

        this->_state = building;
        assert(this->_state == building);

    }


}

#endif
