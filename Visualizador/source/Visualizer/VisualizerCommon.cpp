#include "VisualizerCommon.h"


// Clamp n to lie within the range [min, max]
double clamp(double n, double min, double max)
{
    if (n < min) return min;
    if (n > max) return max;
    return n;
}


/// LAPLACIAN
// eigen value
unsigned int getMatrixType(gsl_matrix *mat)
{
    gsl_matrix *mat_ = gsl_matrix_alloc(mat->size2,  mat->size2);
    gsl_matrix_memcpy(mat_, mat);
    gsl_eigen_nonsymm_workspace *eigen = gsl_eigen_nonsymm_alloc(mat->size1);
    gsl_vector_complex *eval = gsl_vector_complex_alloc(mat_->size1);
    gsl_eigen_nonsymm(mat_, eval, eigen);

    gsl_complex val;
    unsigned int cont_neg = 0;
    unsigned int cont_non_pos = 0;
    unsigned int cont_non_neg = 0;
    unsigned int cont_pos = 0;
    unsigned int result = 0;
    std::cout<<"eval"<<std::endl;
    for(unsigned int i = 0; i < eval->size; i++)
    {
        val = gsl_vector_complex_get(eval, i);
        std::cout<<val.dat[0]<<" "<<val.dat[1]<<"\t";
    }
    std::cout<<std::endl;

    for(unsigned int i = 0; i < mat_->size1; i++)
    {
        val = gsl_vector_complex_get(eval, i);

        if(val.dat[0] <  0 && !FEQUAL(val.dat[0], 0.0)) cont_neg++;
        if(val.dat[0] <= 0 ||  FEQUAL(val.dat[0], 0.0)) cont_non_pos++;
        if(val.dat[0] >  0 && !FEQUAL(val.dat[0], 0.0)) cont_pos++;
        if(val.dat[0] >= 0 ||  FEQUAL(val.dat[0], 0.0)) cont_non_neg++;
        if(FEQUAL(val.dat[0], 0.0))
        {
            cont_pos = 0;
            cont_neg = 0;
        }
    }
    std::cout<<"size: "<<mat_->size1<<" neg: "<<cont_neg<<" non pos: "<<cont_non_pos<<" pos: "<<cont_pos<<" non neg: "<<cont_non_neg<<std::endl;

    if(cont_non_pos == mat->size1)
    {
        std::cout<<"Non Positive Definite"<<std::endl;
        result = 1;
    }
    if(cont_non_neg == mat->size1)
    {
        std::cout<<"Non Negative Definite"<<std::endl;
        result = 3;
    }
    if(cont_neg     == mat->size1)
    {
        std::cout<<"Negative Definite"<<std::endl;
        result = 0;
    }
    if(cont_pos     == mat->size1)
    {
        std::cout<<"Positive Definite"<<std::endl;
        result = 2;
    }
    gsl_matrix_free(mat_);
    gsl_eigen_nonsymm_free(eigen);
    gsl_vector_complex_free(eval);
    return result;
}

int gsl_linalg_cholesky_decomp2(gsl_matrix * A)
{
    const size_t M = A->size1;
    const size_t N = A->size2;

    if (M != N)
    {
        //GSL_ERROR("cholesky decomposition requires square matrix", GSL_ENOTSQR);
        std::cout<<"cholesky decomposition requires square matrix"<<std::endl;
    }
    else
    {
        size_t i,j,k;
        int status = 0;

        /* Do the first 2 rows explicitly.  It is simple, and faster.  And
        * one can return if the matrix has only 1 or 2 rows.
        */

        double A_00 = gsl_matrix_get (A, 0, 0);

        double L_00 = quiet_sqrt(A_00);

        if (A_00 <= 0)
        {
            status = GSL_EDOM ;
        }

        gsl_matrix_set (A, 0, 0, L_00);

        if (M > 1)
        {
            double A_10 = gsl_matrix_get (A, 1, 0);
            double A_11 = gsl_matrix_get (A, 1, 1);

            double L_10 = A_10 / L_00;
            double diag = A_11 - L_10 * L_10;
            double L_11 = quiet_sqrt(diag);

            if (diag <= 0)
            {
                status = GSL_EDOM;
            }

            gsl_matrix_set (A, 1, 0, L_10);
            gsl_matrix_set (A, 1, 1, L_11);
        }

        for (k = 2; k < M; k++)
        {
            double A_kk = gsl_matrix_get (A, k, k);

            for (i = 0; i < k; i++)
            {
                double sum = 0;

                double A_ki = gsl_matrix_get (A, k, i);
                double A_ii = gsl_matrix_get (A, i, i);

                gsl_vector_view ci = gsl_matrix_row (A, i);
                gsl_vector_view ck = gsl_matrix_row (A, k);

                if (i > 0)
                {
                    gsl_vector_view di = gsl_vector_subvector(&ci.vector, 0, i);
                    gsl_vector_view dk = gsl_vector_subvector(&ck.vector, 0, i);

                    gsl_blas_ddot (&di.vector, &dk.vector, &sum);
                }

                A_ki = (A_ki - sum) / A_ii;
                gsl_matrix_set (A, k, i, A_ki);
            }

            {
                gsl_vector_view ck = gsl_matrix_row (A, k);
                gsl_vector_view dk = gsl_vector_subvector (&ck.vector, 0, k);

                double sum = gsl_blas_dnrm2 (&dk.vector);
                double diag = A_kk - sum * sum;

                double L_kk = quiet_sqrt(diag);

                if (diag <= 0)
                {
                    status = GSL_EDOM;
                }
                gsl_matrix_set (A, k, k, L_kk);
            }
        }

    /* Now copy the transposed lower triangle to the upper triangle,
    * the diagonal is common.
    */

        for (i = 1; i < M; i++)
        {
            for (j = 0; j < i; j++)
            {
                double A_ij = gsl_matrix_get (A, i, j);
                gsl_matrix_set (A, j, i, A_ij);
            }
        }

        if (status == GSL_EDOM)
        {
            //GSL_ERROR ("matrix must be positive definite", GSL_EDOM);
            std::cout<<"matrix must be positive definite"<<std::endl;
            return GSL_EDOM;
        }

        return GSL_SUCCESS;
    }
    return GSL_EFAILED;
}


/// GRAPH
bool list_by_degree(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b)
{
    return a.size() < b.size(); /// crescente
}
bool list_by_degree_descent(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b)
{
    return a.size() > b.size(); /// decrescente
    //return a.size() >= b.size(); /// não funciona na floresta 25
}
bool list_by_cpid(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b)
{
    return a[0][0] < b[0][0]; /// crescente
}
bool list_by_cpid_descent(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b)
{
    return a[0][0] > b[0][0]; /// decrescente
}
bool node_by_cpid(const glm::vec2 &a,const glm::vec2 &b)
{
    return a[0] < b[0]; /// crescente
}
bool node_by_cpid_descent(const glm::vec2 &a,const glm::vec2 &b)
{
    return a[0] > b[0]; /// decrescente
}
bool node_by_degree_descent(const glm::vec2 &a,const glm::vec2 &b)
{
    return a[1] > b[1]; /// decrescente
}
bool cnt_by_connection(const glm::vec4 &a,const glm::vec4 &b)
{
    return a[1] > b[1]; /// decrescente
}

//bool sort_block_content2(const block_content &bc1, const block_content &bc2)
//{
//    return (bc1.cp_ids < bc2.cp_ids);
//}

/// BLOCKS
bool sort_points(const unsigned int& a,const unsigned int& b)
{
    return a < b;
}
//bool greater_vectors(const cpList& a,const cpList& b)
//{
//    return a.contacts.size() > b.contacts.size();
//}
bool contains(const std::vector<unsigned int>&a, const unsigned int b)
{
    for(unsigned int i : a)
    {
        if(i == b) return true;
    }
    return false;
}
/*bool sort_block_content(const block_content &bc1, const block_content &bc2)
{
    if(bc1.type == MULTIPLE)
    {
        if(bc2.type != MULTIPLE)
        {
            return true;
        }
        else
        {
            if(bc1.cnts > bc2.cnts)
            {
                return true;
            }
            else
            {
                if(bc1.cnts == bc2.cnts)
                {
                    if(bc1.contacts_size > bc2.contacts_size)
                        return true;
                }
                else return false;
            }
        }
    }
    else
    {
        if(bc1.type == COMPOSED)
        {
            if(bc2.type == MULTIPLE)
            {
                return false;
            }
            else
            {
                if(bc2.type == SIMPLE)
                {
                    return true;
                }
                else
                {
                    if(bc1.cnts > bc2.cnts)
                    {
                        return true;
                    }
                    else
                    {
                        if(bc1.cnts == bc2.cnts)
                        {
                            if(bc1.contacts_size > bc2.contacts_size)
                                return true;
                        }
                        else return false;
                    }
                }
            }
        }
        else
        {
            if(bc1.cnts > bc2.cnts)
                return true;
            else
                if(bc1.cnts == bc2.cnts)
                    if(bc1.contacts_size > bc2.contacts_size)
                        return true;
        }
    }
    return false;
}*/
