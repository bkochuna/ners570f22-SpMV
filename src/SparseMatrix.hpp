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

    template <class fp_type>
    class SparseMatrix {

    protected:
        size_t _nrows = 0;
        size_t _ncols = 0;
        size_t _nnz = 0;

        MatrixState _state = undefined;

        map<pair<size_t, size_t>, fp_type> _buildCoeff;

        // void _unAssemble();

    public:
        SparseMatrix(const int nrows, const int ncols);
        virtual ~SparseMatrix();
        void setCoefficient(size_t row, size_t col, fp_type val);
        void setCoefficient(size_t *row, size_t *col, fp_type *val, size_t num_vals); 
        virtual void assembleStorage() = 0;
        virtual void getFormat();
  };

    template <class fp_type>
    SparseMatrix<fp_type>::SparseMatrix(const int nrows, const int ncols):
        _nrows(nrows), _ncols(ncols), _nnz(0), _state(initialized) 
    {

        cout << "Hello from SparseMatrix Constructor!" << endl;
        assert(this->_state == initialized);

    }

    template <class fp_type>
    SparseMatrix<fp_type>::~SparseMatrix() 
    {

        cout << "Hello from SparseMatrix Destructor!" << endl;
        cout << "this->_ncols=" << this->_ncols << endl;
        cout << "this->_nrows=" << this->_nrows << endl;
        cout << "this->_nnz  =" << this->_nnz << endl;
        this->_state = undefined;
        assert(this->_state == undefined);

    }

    template <class fp_type>
    void SparseMatrix<fp_type>::setCoefficient(size_t row, size_t col, fp_type val)
    {
        /* Check for undefined state */
        assert(this->_state != undefined);

        /* Go to Build state */
        this->_state = building;

        this->_buildCoeff[ make_pair(row, col) ] = val;

        this->_nnz = this->_buildCoeff.size();

        /* Check for building state */
        assert(this->_state == building);

    }

    template <class fp_type>
    void SparseMatrix<fp_type>::setCoefficient(size_t *row, size_t *col, fp_type *val, size_t num_vals)
    {
        /* Check for undefined state */
        assert(this->_state != undefined);

        /* Go to Build state */
        this->_state = building;

        for (int ival=0; ival<num_vals; ival++)

        {

            this->_buildCoeff[ make_pair(*(row + ival),*(col + ival)) ] = *(val + ival); 

        }

        this->_nnz = this->_buildCoeff.size();

        /* Check for building state */
        assert(this->_state == building);

    }

    template <class fp_type>
    void SparseMatrix<fp_type>::getFormat() 
    {

        assert(this->_state == assembled);
        cout << "Hello from SparseMatrix::getFormat!" << endl;

    }

} // namespace SpMV

#endif


