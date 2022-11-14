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

namespace SpMV {
  template <class fp_type>
  class SparseMatrix_DEN : public SparseMatrix<fp_type> {
    private:
      fp_type *_A = nullptr;

      void _unAssemble();

    public:
      SparseMatrix_DEN(const size_t nrows, const size_t ncols) : SparseMatrix<fp_type>::SparseMatrix(nrows, ncols) {}

      virtual ~SparseMatrix_DEN();

      void assembleStorage();

      void computeMatVecProduct(const fp_type x[], fp_type y[]);
  };

} // namespace SpMV

#endif
