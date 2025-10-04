#pragma once

#define SCALAR double
#define INDEX unsigned int

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    void mulSparseMatrixScalar(const void *mat, SCALAR scalar, void *matOut);
    void subSparseMatrices(const void *matA, const void *matB, void *matOut);

    void *createSparseMatrix(INDEX rows, INDEX cols);
    void *createSparseMatrixFromTriplets(INDEX rows, INDEX cols,
                                         INDEX nb_triplets,
                                         const INDEX *triplet_rows, const INDEX *triplet_cols, const SCALAR *triplet_vals);
    void *createDiagonalSparseMatrixFromArray(INDEX size, const SCALAR *diag_vals);
    void solveSymmetricSparseLinearSystem(const void *mat, const SCALAR *b, SCALAR *x, INDEX size);
    void destroySparseMatrix(void *mat);

#ifdef __cplusplus
}
#endif /* __cplusplus */
