#ifndef LAPLACIAN_H
#define LAPLACIAN_H
#include "DrawableNanotube.h"
#include "LinearSolver.h"
#include "Graph.h"

namespace Library
{
class Laplacian
{
    public:
        typedef enum coord{
            NONE = 0,
            X_COORD = 1,
            Y_COORD = 2,
            Z_COORD = 3,
            XY_COORD = 4,
            XZ_COORD = 5,
            YZ_COORD = 6,
            XYZ_COORD = 7
        } COORDINATES; // coordenadas a serem consideradas na montagem da matriz

        Laplacian(std::vector<DrawableNanotube*> *nano, Graph *graph, int mSegmentsPerCNT);
        virtual ~Laplacian();

        void Configure(COORDINATES vert_coord, COORDINATES att_coord,
                       COORDINATES ver_restr, COORDINATES att_restr,
                       COORDINATES extra_restr);
        gsl_vector* Solve(LinearSolver::SOLVER solver_type);

    protected:

    private:
        std::vector<DrawableNanotube*> *mDrawNano;
        Graph *mGraph;
        int segmentsPerCNT;

        int mLaplacianRows;
        int mLaplacianCols;

        COORDINATES vertices_coord;
        COORDINATES attractors_coord;
        COORDINATES vertices_restriction;
        COORDINATES attractors_restriction;
        COORDINATES extra_restriction;

        /// Limits
        glm::vec2 v_x, v_y, v_z;
        glm::vec2 a_x, a_y, a_z;

        gsl_matrix *ComputeLaplacian();
        gsl_vector *ComputeBVector();
        void NormalizeLaplacian(gsl_matrix *laplacian);
        void SetMatrixLimits();
        void GetLaplacianMatrixIndices(int cpid, int &index, COORDINATES coordinate);

        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);
};
}

#endif // LAPLACIAN_H
