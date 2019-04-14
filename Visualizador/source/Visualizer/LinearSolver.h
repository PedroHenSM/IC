#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

namespace Library
{
class LinearSolver
{
    public:
        typedef enum solver{
            LU_SOLVER = 0,
            CHOLESKY = 1,
            CHOLESKY_PIVOTED = 2,
            CHOLESKY_MODIFIED = 3,
            SVD = 4
        } SOLVER;

        LinearSolver();
        virtual ~LinearSolver();

        gsl_matrix* LeastSquareMatrix(gsl_matrix *matrix);
        gsl_vector* MatrixTransposeVector(gsl_matrix *matrix, gsl_vector* b_vector);
        gsl_vector* Solve(SOLVER solver_type, gsl_matrix* matrix, gsl_vector *b_vector);
        gsl_vector* ComputeBvectorOrderMatrix(gsl_matrix *edgeMatrix);

        double GetMatrixConditioning(gsl_matrix *matrix);

        void PrintMatrix(gsl_matrix *matrix);
        void PrintVector(gsl_vector *vec);

    protected:

    private:
        gsl_error_handler_t *old_handler;

        gsl_vector* SingularValueSolver(gsl_matrix* matrix, gsl_vector *b_vector);
        gsl_vector* LUSolver(gsl_matrix* matrix, gsl_vector *b_vector);
        gsl_vector* CholeskySolver(gsl_matrix* matrix, gsl_vector *b_vector);
        gsl_vector* CholeskyPivotedSolver(gsl_matrix* matrix, gsl_vector *b_vector);
        gsl_vector* CholeskyModifiedSolver(gsl_matrix* matrix, gsl_vector *b_vector);
};
}
#endif // LINEARSOLVER_H
