#ifndef _SPMV570_
#define _SPMV570_

#include <cassert>
#include <cstddef>
#include <iostream>
#include <map>
#include <utility>
#include <fstream>

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

      void importMatrix(char const* fileName);
      void setCoefficient(const size_t row, const size_t col, const fp_type aij);
      virtual void assembleStorage() = 0;
      virtual void getFormat();
      size_t getNRows(){ return this->_nrows;}
      size_t getNCols(){ return this->_ncols;}
      size_t getNNZ(){ return this->_nnz;}
      size_t getMapSize(){ return this->_buildCoeff.size();}
      fp_type getMapEntry(const size_t row, const size_t col);
  };

  template <class fp_type>
  SparseMatrix<fp_type>::SparseMatrix(const int nrows, const int ncols)
      : _nrows(nrows), _ncols(ncols), _nnz(0), _state(initialized) {
    cout << "Hello from SparseMatrix Constructor!" << endl;
    assert(this->_state == initialized);
  }

  template <class fp_type>
  SparseMatrix<fp_type>::~SparseMatrix() {
    cout << "Hello from SparseMatrix Destructor!" << endl;
    cout << "this->_ncols=" << this->_ncols << endl;
    cout << "this->_nrows=" << this->_nrows << endl;
    cout << "this->_nnz  =" << this->_nnz << endl;
    this->_state = undefined;
    assert(this->_state == undefined);
  }

    //Function to import matrix
    //Function will overwrite all existing data and build with all coefficients in the file
    template <class fp_type>
    void SparseMatrix<fp_type>::importMatrix(char const* fileName)
    {

    //Opens file and checks if file is available, otherwise kills the program
    ifstream fileStream;
    fileStream.open(fileName);
    if(fileStream.fail()){
        cout<<"File "<<fileName<<" cannot be found"<<endl;
        assert(false);
        return;
}      

        //If matrix has been initialized/is building, notify user that their data will be ovewrit
        if(this->_state != undefined){
            cout<<"This matrix is already intialized/building"<<endl;
            cout<<"This import will overwrite all existing data in the matrix"<<endl;
        }
        this->_buildCoeff.clear();

        //Getting matrix metadata to initialize the matrix
        int numHolder = 0;
        string lineHolder;
        while(getline(fileStream,lineHolder)){
            if(lineHolder.at(0)!='%'){
                //There has to be a better way to do this
                stringstream lineStream(lineHolder);
                string sublineHolder;
                lineStream>>sublineHolder;
                this->_nrows = stoi(sublineHolder);
                lineStream>>sublineHolder;
                this->_ncols = stoi(sublineHolder);
                lineStream>>sublineHolder;
                numHolder = stoi(sublineHolder);
                break;
            }
        }

        //Reads in the data entry by entry and builds the coefficient
        string entryHolder = "";
        for(int i = 0; i<numHolder; ++i){
            fileStream>>entryHolder;
            size_t rowHolder = (size_t) stoi(entryHolder)-1;
            fileStream>>entryHolder;
            size_t colHolder = (size_t) stoi(entryHolder)-1;
            fileStream>>entryHolder;
            fp_type dataHolder = (fp_type) stod(entryHolder);
            setCoefficient(rowHolder, colHolder, dataHolder);
        }

        //Sets matrix state to building
        this->_state = building;

    } 

  template <class fp_type>
  void SparseMatrix<fp_type>::setCoefficient(const size_t row, const size_t col, const fp_type aij) {
    assert(this->_state != undefined);
    cout << "Hello from SparseMatrix::setCoefficient!" << endl;

    // if(this->_state == assembled)
    //      this->_unAssemble();

    this->_state = building;

    this->_buildCoeff[make_pair(row, col)] = aij;
    this->_nnz = this->_buildCoeff.size();
    assert(this->_state == building);
  }

  template <class fp_type>
  void SparseMatrix<fp_type>::getFormat() {
    assert(this->_state == assembled);
    cout << "Hello from SparseMatrix::getFormat!" << endl;

    // return new SparseMatrix(this->_ncols,this->_nrows);
  }

  template <class fp_type>
  fp_type SparseMatrix<fp_type>::getMapEntry(const size_t row, const size_t col){
    auto it = this->_buildCoeff.find(make_pair(row,col));
    if(it== this->_buildCoeff.end()){
      return 0;
    } 
    else{
      return it->second;
    }
  }

} // namespace SpMV

#endif
