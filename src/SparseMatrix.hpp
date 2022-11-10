#ifndef _SPMV570_
#define _SPMV570_

#include <cassert>
#include <cstddef>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

namespace SpMV {
  enum MatrixState { undefined, initialized, building, assembled };

  /**
   * @brief Abstract base class for sparse matrices.
   *
   * @tparam fp_type Numeric type of matrix entries
   */
  template <class fp_type>
  class SparseMatrix {
    protected:
      size_t _nrows = 0; ///< The number of rows
      size_t _ncols = 0; ///< The number of columns
      size_t _nnz = 0;   ///< The number of non-zeros

      MatrixState _state = undefined; ///< The matrix state

      map<pair<size_t, size_t>, fp_type> _buildCoeff; ///< The data structure used for storing non-zero entries
                                                      ///< during matrix assembly

      /**
       * @brief Convert the assembled matrix data back to the format used for building
       *
       */
      virtual void _unAssemble() = 0;

      /**
       * @brief Clear the the unassembled matrix data, should only be called at the end of the matrix assembly
       *
       */
      virtual inline void _clearBuildCoeff() { this->_buildCoeff.clear(); }

    public:
      /**
       * @brief Construct a new Sparse Matrix object of given dimensions
       *
       * @param rows Number of rows
       * @param cols Number of columns
       */
      SparseMatrix(const int nrows, const int ncols);

      /**
       * @brief Destroy the Sparse Matrix object
       *
       */
      virtual ~SparseMatrix();

      /**
       * @brief Get the number of rows in the matrix
       *
       * @return size_t Number of rows
       */
      inline size_t getNumRows() const { return _nrows; };

      /**
       * @brief Get the number of columns in the matrix
       *
       * @return size_t Number of columns
       */
      inline size_t getNumCols() const { return _ncols; };

      /**
       * @brief Get the number of non-zeros in the matrix
       *
       * @return size_t Number of non-zeros
       */
      inline size_t getNumNonZeros() const { return _nnz; };

      /**
       * @brief Get the current state of the matrix
       *
       * @return MatrixState The matrix state
       */
      inline MatrixState getState() const { return _state; };

      /**
       * @brief Set the value of the matrix at the given row and column
       *
       * @param row Row index
       * @param col Column index
       * @param value Value
       */
      void setCoefficient(const size_t row, const size_t col, const fp_type aij);

      /**
       * @brief Assemble the matrix
       *
       */
      virtual void assembleStorage() = 0;

      /**
       * @brief I don't know what this does
       *
       */
      virtual void getFormat();

      /**
       * @brief Compute the matrix vector product y = A*x
       *
       * @param x Vector x
       * @param y Vector y
       */
      virtual void computeMatVecProduct(const fp_type x[], fp_type y[]) = 0;

      /**
       * @brief Write the matrix to disk in MatrixMarket file format
       *
       * @param fileName Name of the file to write
       */
      void exportMatrix(char *fileName);
  };

  template <class fp_type>
  SparseMatrix<fp_type>::SparseMatrix(const int nrows, const int ncols)
      : _nrows(nrows), _ncols(ncols), _nnz(0), _state(initialized) {
    assert(this->_state == initialized);
  }

  template <class fp_type>
  SparseMatrix<fp_type>::~SparseMatrix() {
    this->_state = undefined;
    assert(this->_state == undefined);
  }

  template <class fp_type>
  void SparseMatrix<fp_type>::setCoefficient(const size_t row, const size_t col, const fp_type aij) {
    assert(this->_state != undefined);

    if (this->_state == assembled)
      this->_unAssemble();

    this->_state = building;

    this->_buildCoeff[make_pair(row, col)] = aij;
    this->_nnz = this->_buildCoeff.size();
    assert(this->_state == building);
  }

  template <class fp_type>
  void SparseMatrix<fp_type>::getFormat() {
    assert(this->_state == assembled);

    // return new SparseMatrix(this->_ncols,this->_nrows);
  }

  template <class fp_type>
  void SparseMatrix<fp_type>::exportMatrix(char *fileName) {
    // Exit with warning if matrix is not assembled
    assert(this->_state != assembled);
    SparseMatrix<fp_type> outMat = this->getFormat("COO");

    // Open file
    std::ofstream outfile;
    outfile.open(fileName);

    // Write preamble
  private:
    char preamble = " %%MatrixMarket matrix coordinate real general"
                    " %================================================================================="
                    " %"
                    " % This ASCII file represents a sparse MxN matrix with L "
                    " % nonzeros in the following Matrix Market format:"
                    " %"
                    " % +----------------------------------------------+"
                    " % |%%MatrixMarket matrix coordinate real general | <--- header line"
                    " % |%                                             | <--+"
                    " % |% comments                                    |    |-- 0 or more comment lines"
                    " % |%                                             | <--+         "
                    " % |    M  N  L                                   | <--- rows, columns, entries"
                    " % |    I1  J1  A(I1, J1)                         | <--+"
                    " % |    I2  J2  A(I2, J2)                         |    |"
                    " % |    I3  J3  A(I3, J3)                         |    |-- L lines"
                    " % |        . . .                                 |    |"
                    " % |    IL JL  A(IL, JL)                          | <--+"
                    " % +----------------------------------------------+   "
                    " %"
                    " % Indices are 1-based, i.e. A(1,1) is the first element."
                    " %"
                    " %=================================================================================";
    outfile << m.write << endl;

    // Write header line with matrix meta-data
    outfile << outMat._nrows;
    outfile << outMat._ncols;
    outfile << outMat._nnz << endl;

    // Write data of each nonzero matrix element
    for (int n = 0; n < _nnz; i++) {
      outfile << outMat.J[n];
      outfile << outMat.I[n];
      outfile << outMat.val[n] << endl;
    }
    outfile.close();
  }

} // namespace SpMV

#endif
