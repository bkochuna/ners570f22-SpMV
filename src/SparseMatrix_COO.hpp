/*
=============================================================================
COOrdinate Sparse Matrix (COO) implementation
=============================================================================
@File    :   SparseMatrix_COO.hpp
@Date    :
@Description :
*/
#ifndef __SPMV570_COO__
#define __SPMV570_COO__

// =============================================================================
// Standard Library Includes
// =============================================================================

// =============================================================================
// Project Includes
// =============================================================================
#include "SparseMatrix.hpp"

// ==============================================================================
// Class declaration
// ==============================================================================
namespace SpMV {
  /**
   * @brief A sparse matrix stored in COO (coordinate format)
   *
   * @tparam fp_type Numeric type of matrix entries
   */
  template <class fp_type>
  class SparseMatrix_COO : public SparseMatrix<fp_type> {

    private:
      size_t *I = nullptr;    ///< Row indices list
      size_t *J = nullptr;    ///< Column indices list
      fp_type *val = nullptr; ///< Non-zero entries list

      /**
       * @brief Convert the assembled matrix data back to the format used for building
       *
       * @note Calling this function will also clear the assembled matrix data
       *
       */
      void _unAssemble();

    public:
      /**
       * @brief Construct a new COO Sparse Matrix of given dimensions
       *
       * @param rows Number of rows
       * @param cols Number of columns
       */
      SparseMatrix_COO(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols){};

      /**
       * @brief Destructor for COO Sparse Matrix format. Destory objects created
       *
       */
      virtual ~SparseMatrix_COO();

      /**
       * @brief Assemble the COO data structures
       *
       * @note object state after call is "assembled"
       *
       * Converts the SparseMatrix generic map format stored in _buildcoeff to the COO specific
       * the COO specific data structure and deallocates the map
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
  };

} // namespace SpMV
#endif
