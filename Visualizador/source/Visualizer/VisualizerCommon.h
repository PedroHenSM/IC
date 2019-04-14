#include "Visualizer.h"
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>


double clamp(double n, double min, double max);
/// LAPLACIAN
unsigned int getMatrixType(gsl_matrix *mat);
static inline double quiet_sqrt (double x)
{
    return (x >= 0) ? sqrt(x) : GSL_NAN;
}
int gsl_linalg_cholesky_decomp2(gsl_matrix * A);

/// GRAPH
bool list_by_degree(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b);
bool list_by_degree_descent(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b);
bool list_by_cpid(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b);
bool list_by_cpid_descent(const std::vector<glm::vec2> &a,const std::vector<glm::vec2> &b);
bool node_by_cpid(const glm::vec2 &a,const glm::vec2 &b);
bool node_by_cpid_descent(const glm::vec2 &a,const glm::vec2 &b);
bool node_by_degree_descent(const glm::vec2 &a,const glm::vec2 &b);
bool cnt_by_connection(const glm::vec4 &a,const glm::vec4 &b);
//bool sort_block_content2(const block_content &bc1, const block_content &bc2);

/// BLOCKS
bool sort_points(const unsigned int& a,const unsigned int& b);
//bool greater_vectors(const cpList& a,const cpList& b);
bool contains(const std::vector<unsigned int>&a, const unsigned int b);
//bool sort_block_content(const block_content &bc1, const block_content &bc2);

