#include "LinearSolver.h"

#include <iostream>
#include <algorithm>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_errno.h>
#include "gcg.h"

namespace Library
{
void my_handler(const char * reason,
              const char * file,
              int line,
              int gsl_errno)
{
    std::cout<<"Error ";
    switch(gsl_errno)
    {
        case GSL_FAILURE : std::cout<<"GSL_FAILURE"<<std::endl; break;
        case GSL_EDOM : std::cout<<"GSL_EDOM"<<std::endl; break;
        case GSL_EUNIMPL : std::cout<<"GSL_EUNIMPL"<<std::endl; break;
        case GSL_EBADLEN : std::cout<<"GSL_EBADLEN"<<std::endl; break;
        case GSL_ENOTSQR : std::cout<<"GSL_ENOTSQR"<<std::endl; break;

    }
    std::cout<<"at file "<<file<<std::endl;
    std::cout<<"At line "<<line<<std::endl;
    std::cout<<reason<<std::endl;
}

LinearSolver::LinearSolver()
{
    //ctor
    old_handler = gsl_set_error_handler (&my_handler);
    ///gsl_set_error_handler (old_handler);
}

LinearSolver::~LinearSolver()
{
    //dtor
}

gsl_vector* LinearSolver::Solve(SOLVER solver_type, gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_vector *solution = NULL;
    switch(solver_type)
    {
    case LU_SOLVER :
        solution = LUSolver(matrix, b_vector);
        break;
    case CHOLESKY :
        solution = CholeskySolver(matrix, b_vector);
        break;
    case CHOLESKY_PIVOTED :
        solution = CholeskyPivotedSolver(matrix, b_vector);
        break;
    case CHOLESKY_MODIFIED :
        solution = CholeskyModifiedSolver(matrix, b_vector);
        break;
    case SVD :
        solution = SingularValueSolver(matrix, b_vector);
        break;
    default :
        {
        std::cout<<"No solver selected: LU_SOLVER, CHOLESKY, CHOLESKY_PIVOTED, CHOLESKY_MODIFIED, SVD"<<std::endl;
        int nada;std::cin>>nada;
        } break;
    }

    return solution;

}

gsl_matrix* LinearSolver::LeastSquareMatrix(gsl_matrix *matrix)
{
    /// A^T * A = aTa
    gsl_matrix* aTa = gsl_matrix_alloc(matrix->size2, matrix->size2);
    gsl_matrix* matrixTrans = gsl_matrix_alloc(matrix->size2, matrix->size1);
    gsl_matrix_transpose_memcpy(matrixTrans, matrix);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, matrixTrans, matrix, 0.0, aTa);
    gsl_matrix_free(matrixTrans);
    return aTa;
}

gsl_vector* LinearSolver::MatrixTransposeVector(gsl_matrix *matrix, gsl_vector* b_vector)
{
    /// A^T * B = aTb
    gsl_vector* aTb = gsl_vector_alloc(matrix->size2);
    for(unsigned int j = 0; j < matrix->size2; j++)
    {
        double val = 0.0;
        for(unsigned int i = 0; i < matrix->size1; i++)
        {
           val += gsl_matrix_get(matrix, i, j)*gsl_vector_get(b_vector, i);
        }
        gsl_vector_set(aTb, j, val);
    }
    return aTb;
}

gsl_vector* LinearSolver::SingularValueSolver(gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_vector *solution  = gsl_vector_alloc(matrix->size2);
    gsl_vector_set_zero(solution);
    gsl_matrix* decomp_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
    gsl_matrix_memcpy(decomp_matrix, matrix);
    /// The diagonal elements of the singular value matrix S are stored in the vector S.
    /// The singular values are non-negative and form a non-increasing sequence from S_1 to S_N.
    gsl_vector *s_vector = gsl_vector_alloc(matrix->size2);
    /// The matrix V contains the elements of V in untransposed form.
    gsl_matrix* v_matrix = gsl_matrix_alloc(matrix->size2, matrix->size2);
    /// To form the product U S V^T it is necessary to take the transpose of V. A workspace of length N is required in work.
    gsl_vector *work = gsl_vector_alloc(matrix->size2);

    if(gsl_linalg_SV_decomp(decomp_matrix, v_matrix, s_vector, work) == GSL_SUCCESS)
    {
        gsl_linalg_SV_solve(decomp_matrix, v_matrix, s_vector, b_vector, solution);
    }
    gsl_matrix_free(decomp_matrix);
    gsl_matrix_free(v_matrix);
    gsl_vector_free(s_vector);
    gsl_vector_free(work);

    return solution;
}

gsl_vector* LinearSolver::LUSolver(gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_matrix *square_matrix;
    if(matrix->size1 != matrix->size2)
    {
        square_matrix = LeastSquareMatrix(matrix);
    }
    else
    {
        square_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
        gsl_matrix_memcpy(square_matrix, matrix);
    }
    int dim = square_matrix->size1;
    int signum;
    gsl_permutation *perm = gsl_permutation_alloc(dim);
    gsl_matrix *L_LU = gsl_matrix_alloc(dim, dim);
    gsl_matrix_memcpy(L_LU, square_matrix);
    gsl_linalg_LU_decomp(L_LU, perm, &signum);
    /// Refining
    gsl_vector *solution  = gsl_vector_alloc(dim);
    gsl_vector *residual = gsl_vector_alloc(dim);
    gsl_vector *rhs      = gsl_vector_alloc(dim); /// armazena 1 na coluna que vamos refinar
    gsl_vector *new_row  = gsl_vector_alloc(dim);
    gsl_matrix *L_Inverse = gsl_matrix_alloc(dim, dim);
    double det = gsl_linalg_LU_det(L_LU, signum);

    /// Não é zero, nem perto de zero, ou NaN
    if(!FEQUAL(det, EPSILON) && !FEQUAL(det, 0.0) && det == det)
    {
        for (int m = 0; m < dim; m++)
        {
            gsl_vector_set_zero(rhs);
            gsl_vector_set(rhs, m, 1.0);

            gsl_linalg_LU_solve(L_LU, perm, rhs, new_row);
            gsl_linalg_LU_refine(square_matrix, L_LU, perm, rhs, new_row, residual);

            for (int n = 0; n < dim; n++)
            {
                gsl_matrix_set(L_Inverse,n, m, gsl_vector_get(new_row, n));
            }
        }
        gsl_blas_dgemv(CblasNoTrans, 1.0, L_Inverse, b_vector, 0.0, solution);
    }
    else
    {
        std::cout<<"Matrix is singular"<<std::endl;
        std::cout<<"Determinant "<<det<<std::endl;
        int nada;std::cin>>nada;
        gsl_vector_set_zero(solution);
    }
    gsl_matrix_free(L_Inverse);
    gsl_matrix_free(L_LU);
    gsl_matrix_free(square_matrix);
    gsl_permutation_free(perm);
    gsl_vector_free(residual);
    gsl_vector_free(rhs);
    gsl_vector_free(new_row);

    return solution;

}

gsl_vector* LinearSolver::CholeskySolver(gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_matrix *square_matrix;
    if(matrix->size1 != matrix->size2)
    {
        square_matrix = LeastSquareMatrix(matrix);
    }
    else
    {
        square_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
        gsl_matrix_memcpy(square_matrix, matrix);
    }
    int dim = square_matrix->size1;
    gsl_vector *solution  = gsl_vector_alloc(dim);
    gsl_vector_set_zero(solution);
    gsl_matrix* decomp_matrix = gsl_matrix_alloc(square_matrix->size1, square_matrix->size2);
    gsl_matrix_memcpy(decomp_matrix, square_matrix);

    if(gsl_linalg_cholesky_decomp(decomp_matrix) == GSL_SUCCESS)
    {
        gsl_linalg_cholesky_solve(decomp_matrix, b_vector, solution);
    }
    gsl_matrix_free(decomp_matrix);

    return solution;
}


gsl_vector* LinearSolver::CholeskyPivotedSolver(gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_matrix *square_matrix;
    if(matrix->size1 != matrix->size2)
    {
        square_matrix = LeastSquareMatrix(matrix);
    }
    else
    {
        square_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
        gsl_matrix_memcpy(square_matrix, matrix);
    }
    int dim = square_matrix->size1;
    gsl_vector *solution  = gsl_vector_alloc(dim);
    gsl_vector_set_zero(solution);


    return solution;
}

gsl_vector* LinearSolver::CholeskyModifiedSolver(gsl_matrix* matrix, gsl_vector *b_vector)
{
    gsl_matrix *square_matrix;
    if(matrix->size1 != matrix->size2)
    {
        square_matrix = LeastSquareMatrix(matrix);
    }
    else
    {
        square_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
        gsl_matrix_memcpy(square_matrix, matrix);
    }
    int dim = square_matrix->size1;
    gsl_vector *solution  = gsl_vector_alloc(dim);
    gsl_vector_set_zero(solution);


    return solution;
}

double LinearSolver::GetMatrixConditioning(gsl_matrix *matrix)
{
    bool verbose = false;
    double max_s = -1, min_s = INT_MAX;

    gsl_matrix* decomp_matrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
    gsl_matrix_memcpy(decomp_matrix, matrix);
    /// The diagonal elements of the singular value matrix S are stored in the vector S.
    /// The singular values are non-negative and form a non-increasing sequence from S_1 to S_N.
    gsl_vector *s_vector = gsl_vector_alloc(matrix->size2);
    /// The matrix V contains the elements of V in untransposed form.
    gsl_matrix* v_matrix = gsl_matrix_alloc(matrix->size2, matrix->size2);
    /// To form the product U S V^T it is necessary to take the transpose of V. A workspace of length N is required in work.
    gsl_vector *work = gsl_vector_alloc(matrix->size2);

    if(gsl_linalg_SV_decomp(decomp_matrix, v_matrix, s_vector, work) == GSL_SUCCESS)
    {
        for(unsigned int i = 0; i < s_vector->size; i++)
        {
            if(gsl_vector_get(s_vector, i) > max_s)
                max_s = gsl_vector_get(s_vector, i);
            if(gsl_vector_get(s_vector, i) < min_s)
                min_s = gsl_vector_get(s_vector, i);
        }
    }
    if(verbose) std::cout<<"Matrix Conditioning:  min_s "<<min_s<<"  max_s  "<<max_s<<std::endl;
    gsl_matrix_free(decomp_matrix);
    gsl_matrix_free(v_matrix);
    gsl_vector_free(s_vector);
    gsl_vector_free(work);

    return max_s/min_s;
}

void LinearSolver::PrintMatrix(gsl_matrix *matrix)
{
    for(unsigned int i = 0; i < matrix->size1; i++)
    {
        for(unsigned int j = 0; j < matrix->size2; j++)
        {
            std::cout<<gsl_matrix_get(matrix, i, j)<<"\t";
        }
        std::cout<<std::endl;
    }

}

void LinearSolver::PrintVector(gsl_vector *vec)
{
    for(unsigned int i = 0; i < vec->size; i++)
    {
        std::cout<<gsl_vector_get(vec, i)<<"\t";
    }
    std::cout<<std::endl;
}

}
