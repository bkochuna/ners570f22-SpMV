This folder for documentation.

To build the documentation, you need to install doxygen and graphviz (e.g `sudo apt install doxygen graphviz` on Ubuntu).

Then run `doxygen doxy.config` in this folder.

You can then view the documentation by opening `html/index.html` in your browser.

(From JDS format doc)


# CSR format

A sparse matrix or sparse array is a matrix in which most of the elements are zero. The compressed sparse row (CSR) represents a matrix M by three (one-dimensional) arrays, that respectively contain nonzero values, column indices and row pointers.

This package helps to store the sparse matrix in CSR format and do the matrix-vector multiplication as a collected package. The code and the architecture are written in an objected oriented manner to ease the use of it. 

These are the functions that are critical to this package:

`SparseMatrix_CSR(const size_t nrows, const size_t ncols)` : Constructor
`SparseMatrix_CSR()` : Destructor
`assembleStorage()` : assemble the CSR format
`computeMatVecProduct(const fp_type *x,fp_type *y)`: Compute matrix-vector product
`getFormat`: getting the format in CSR
`_unAssemble()`: Unassemble the CSR format


