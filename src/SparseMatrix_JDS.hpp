/*
=============================================================================
Jagged Diagonal Sparse Matrix (JDS) implementation
=============================================================================
@File    :   SparseMatrix_JDS.hpp
@Date    :   2022/10/16
@Description :
*/
#ifndef __SPMV570_JDS__
#define __SPMV570_JDS__

// =============================================================================
// Standard Library Includes
// =============================================================================
#include <algorithm>
#include <cassert>
#include <vector>

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix.hpp"

// ==============================================================================
// Class declaration
// ==============================================================================
namespace SpMV {
  /**
   * @brief Class representing a sparse matrix in JDS format.
   *
   * @tparam fp_type Numeric type to use for matrix entries.
   */
  template <class fp_type>
  class SparseMatrix_JDS : public SparseMatrix<fp_type> {
    public:
      /**
       * @brief Construct a new JDS Sparse Matrix of given dimensions
       *
       * @param rows Number of rows
       * @param cols Number of columns
       */
      SparseMatrix_JDS(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {}

      /**
       * @brief Overloaded constructor:
       * Construct a new JDS Sparse Matrix of given dimensions AND JDS data structures
       *
       * @note Skips the building phase
       *
       * @param rows Number of rows
       * @param cols Number of columns
       * @param perm Vector of row permutations, should be nrows long
       * @param jd_ptr Vector of jagged diagonal pointers (where in the flattened arrays each column starts and ends),
       * should be max_row_size + 1 long
       * @param col_ind Vector of column indices, should have one entry for each nonzero in the matrix
       * @param jdiag Vector of actual matrix values, should have one entry for each nonzero in the matrix
       * @param max_row_size Maximum row size in the matrix
       */
      SparseMatrix_JDS(const size_t nrows,
                       const size_t ncols,
                       size_t perm[],
                       fp_type jdiag[],
                       size_t col_ind[],
                       size_t jd_ptr[],
                       size_t max_row_size);

      /**
       * @brief Destructor for JDS Sparse Matrix format. Destory objects created
       *
       */
      virtual ~SparseMatrix_JDS();

      /**
       * @brief Assemble the JDS data structures from the general map based data structure used in the building phase
       *
       */
      void assembleStorage();

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

    private:
      size_t *_colIndices;          ///< Column indices
      size_t _maxRowSize;           ///< Maximum row size
      fp_type *_values;             ///< Values
      std::vector<size_t> _rowPerm; ///< Row permutation
      size_t *_jdPtrs;              ///< JDS pointers
  };                                // class SparseMatrix_JDS

} // namespace SpMV
#endif
