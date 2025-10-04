#include "sparse.h"
#include <Eigen/Sparse>

extern "C"
{
    void mulSparseMatrixScalar(const void *mat, SCALAR scalar, void *matOut)
    {
        const Eigen::SparseMatrix<SCALAR> *sparseMat = static_cast<const Eigen::SparseMatrix<SCALAR> *>(mat);
        Eigen::SparseMatrix<SCALAR> *sparseMatOut = static_cast<Eigen::SparseMatrix<SCALAR> *>(matOut);
        *sparseMatOut = (*sparseMat) * scalar;
    }

    void subSparseMatrices(const void *matA, const void *matB, void *matOut)
    {
        const Eigen::SparseMatrix<SCALAR> *sparseMatA = static_cast<const Eigen::SparseMatrix<SCALAR> *>(matA);
        const Eigen::SparseMatrix<SCALAR> *sparseMatB = static_cast<const Eigen::SparseMatrix<SCALAR> *>(matB);
        Eigen::SparseMatrix<SCALAR> *sparseMatOut = static_cast<Eigen::SparseMatrix<SCALAR> *>(matOut);
        *sparseMatOut = (*sparseMatA) - (*sparseMatB);
    }

    void *createSparseMatrix(INDEX rows, INDEX cols)
    {
        return new Eigen::SparseMatrix<SCALAR>(rows, cols);
    }

    void *createSparseMatrixFromTriplets(INDEX rows, INDEX cols,
                                         INDEX nb_triplets,
                                         const INDEX *triplet_rows, const INDEX *triplet_cols, const SCALAR *triplet_vals)
    {
        Eigen::SparseMatrix<SCALAR> *mat = new Eigen::SparseMatrix<SCALAR>(rows, cols);
        std::vector<Eigen::Triplet<SCALAR>> triplets;
        triplets.reserve(nb_triplets);
        for (size_t i = 0; i < nb_triplets; ++i)
            triplets.emplace_back(triplet_rows[i], triplet_cols[i], triplet_vals[i]);
        mat->setFromTriplets(triplets.begin(), triplets.end());
        return mat;
    }

    void *createDiagonalSparseMatrixFromArray(INDEX size, const SCALAR *diag_vals)
    {
        Eigen::Map<const Eigen::VectorXd> diag(diag_vals, size);
        return new Eigen::SparseMatrix<SCALAR>(diag.asDiagonal());
    }

    void solveSymmetricSparseLinearSystem(const void *mat, const SCALAR *b, SCALAR *x, INDEX size)
    {
        const Eigen::SparseMatrix<SCALAR> *sparseMat = static_cast<const Eigen::SparseMatrix<SCALAR> *>(mat);
        Eigen::Map<const Eigen::VectorXd> bVec(b, size);
        Eigen::Map<Eigen::VectorXd> xVec(x, size);

        Eigen::SimplicialLDLT<Eigen::SparseMatrix<SCALAR>> solver(*sparseMat);
        xVec = solver.solve(bVec);
    }

    void destroySparseMatrix(void *mat)
    {
        delete mat;
    }
}
