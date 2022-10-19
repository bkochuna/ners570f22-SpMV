/*
=============================================================================
Jagged Diagonal Sparse Matrix (JDS) implementation
=============================================================================
@File    :   SparseMatrix_JDS.hpp
@Date    :   2022/10/16
@Description :
*/
#pragma once

// =============================================================================
// Standard Library Includes
// =============================================================================
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
  class SparseMatrix_JDS : public SparseMatrix<fp_type>
  {
    public:
      /**
       * @brief Construct a new JDS Sparse Matrix of given dimensions
       *
       * @param rows Number of rows
       * @param cols Number of columns
       */
      SparseMatrix_JDS(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows,ncols){}

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

      void computeMatVecProduct(const fp_type &x, fp_type &y);

    private:
      size_t *_colIndices; ///< Column indices
      size_t _maxRowSize;   ///< Maximum row size
      fp_type _values;      ///< Values
      std::vector<size_t> _rowPerm; ///< Row permutation
      size_t *_jdPtrs;      ///< JDS pointers
  }; // class SparseMatrix_JDS
} // namespace SpMV


// ==============================================================================
// Method implementations
// ==============================================================================
