/*
=============================================================================
Coordinate Matrix format (COO) implementation
=============================================================================
@File    :   SparseMatrix_COO.hpp
@Date    :   2022/10/16
@Description :
*/
#ifndef __SPMV570_COO__
#define __SPMV570_COO__

#pragma once

// =============================================================================
// Standard Library Includes
// =============================================================================
#include <algorithm>
#include <vector>

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix.hpp"

// ==============================================================================
// Class declaration
// ==============================================================================
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
            void _unAssemble();

            SparseMatrix<fp_type>* getFormat();
    /**
       * @brief Compute the product of this matrix and a vector in COO format (y = Ax)
       *
       * @note The contents of y are overwritten by this operation
       *
       * @param x Array to multiply with
       * @param y Array to store result in
       */
      void computeMatVecProduct(const fp_type x[], fp_type y[]);
            SparseMartix<fp_type> getFormat();


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
        _buildCoeff.clear()
            //this->_clearBuildCoeff();

        this->_state = assembled;
        assert(this->_state == assembled);
    }
    
    template <class fp_type>
              void SparseMatrix_COO<fp_type>::_unAssemble()
            {
                   assert(this->_state == assembled);
                  
                    //this->_buildCoeff[ make_pair(_nnz,_nnz), _nnz ] = make_pair(I,J),val;
                    size_t n=0;
                    for(n=0; n<this->_nnz; n++)
                    {
                        _buildCoeff.append(make_pair(I[n],J[n]),val[n]); 
                        //this->_buildCoeff[make_pair(I[n],J[n]),val[n]]; 
                        //this->_nnz = this->_buildCoeff.size();
                       // I[n]   = coeff.first.first;
                        //J[n]   = coeff.first.second;
                        //val[n] = coeff.second;
         
                    }
                   free(this->J);
                   free(this->I);
                   free(this->val);
                   this->_state = unassembled;
                   assert(this->_state == unassembled);
               }

    template <class fp_type>
    void SparseMatrix_COO<fp_type>::~SparseMatrix_COO()
    {
	    // Deallocate memory and assign null pointer
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
  void SparseMatrix_COO<fp_type>::computeMatVecProduct(const fp_type x[], fp_type y[]) {
    if (this->_state != assembled) {
      assembleStorage();
    }
    // --- Check that the matrix is assembled ---
    assert(this->_state == assembled);

    // Zero the output vector
    #pragma omp parallel for simd schedule(static)
        for (int ii = 0; ii < this->_nnz; ii++) {
        y[ii] = 0.0;
        }
    // --- Compute the matrix vector product ---
    #pragma omp parallel for simd schedule(static)
        for (int ii = 0; ii < this->_nnz; ii++) {
    #pragma omp atomic
            y[this->J[ii]]+=this->val[ii]*x[this->I[ii]];
        }
    }

    template <class fp_type>
    SparseMatrix<fp_type>* SparseMatrix_COO<fp_type>::getFormat()
    {
    if (this->_state == assembled) {_unAssemble();}

    // Create pointer to new matrix that will be returned
    SparseMatrix<fp-type>* ptr_A = nullptr;

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
    
    
}

#endif



