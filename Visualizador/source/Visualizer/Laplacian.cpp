#include "Laplacian.h"

#include <iostream>
#include <algorithm>
#include "gcg.h"

namespace Library
{
Laplacian::Laplacian(std::vector<DrawableNanotube*> *nano, Graph *graph, int mSegmentsPerCNT) :
    mDrawNano(nano),
    mGraph(graph),
    segmentsPerCNT(mSegmentsPerCNT),
    mLaplacianRows(0),
    mLaplacianCols(0),
    v_x(0.0), v_y(0.0), v_z(0.0),
    a_x(0.0), a_y(0.0), a_z(0.0)
{
    //ctor
    Configure(Z_COORD, XY_COORD, NONE, NONE, NONE);
    SetMatrixLimits();
}

Laplacian::~Laplacian()
{
    //dtor
}

void Laplacian::Configure(COORDINATES vert_coord, COORDINATES att_coord,
                          COORDINATES ver_restr, COORDINATES att_restr,
                          COORDINATES extra_restr)
{
    vertices_coord = vert_coord;
    attractors_coord = att_coord;
    vertices_restriction = ver_restr;
    attractors_restriction = att_restr;
    extra_restriction = extra_restr;
    int rows = 0;
    int cols = 0;
    switch(vertices_coord)
    {
        case X_COORD :
        case Y_COORD :
        case Z_COORD :
        {
            rows = cols = mGraph->GetAdjacencyListSize()-mGraph->GetAttractorsSize();
        }
        break;
        case XY_COORD :
        case XZ_COORD :
        case YZ_COORD :
        {
            rows = cols = 2*(mGraph->GetAdjacencyListSize()-mGraph->GetAttractorsSize());
        }
        break;
        case XYZ_COORD :
        {
            rows = cols = 3*(mGraph->GetAdjacencyListSize()-mGraph->GetAttractorsSize());
        }
        break;
        case NONE :
        {
            rows = cols = 0;
        }
        break;
    }
    switch(attractors_coord)
    {
        case X_COORD :
        case Y_COORD :
        case Z_COORD :
        {
            rows += mGraph->GetAttractorsSize();
            cols += mGraph->GetAttractorsSize();
        }
        break;
        case XY_COORD :
        case XZ_COORD :
        case YZ_COORD :
        {
            rows += 2*(mGraph->GetAttractorsSize());
            cols += 2*(mGraph->GetAttractorsSize());
        }
        break;
        case XYZ_COORD :
        {
            rows += 3*(mGraph->GetAttractorsSize());
            cols += 3*(mGraph->GetAttractorsSize());
        }
        break;
        case NONE : break;
    }

    /// Linhas extras na matriz
    switch(vertices_restriction)
    {
        case X_COORD :
        case Y_COORD :
        case Z_COORD :
        {
            rows += mGraph->GetAttractorsSize();
        }
        break;
        case XY_COORD :
        case XZ_COORD :
        case YZ_COORD :
        {
            rows += 2*(mGraph->GetAttractorsSize());
        }
        break;
        case XYZ_COORD :
        {
            rows += 3*(mGraph->GetAttractorsSize());
        }
        break;
        case NONE : break;
    }
    switch(attractors_restriction)
    {
        case X_COORD :
        case Y_COORD :
        case Z_COORD :
        {
            rows += mGraph->GetAttractorsSize();
        }
        break;
        case XY_COORD :
        case XZ_COORD :
        case YZ_COORD :
        {
            rows += 2*(mGraph->GetAttractorsSize());
        }
        break;
        case XYZ_COORD :
        {
            rows += 3*(mGraph->GetAttractorsSize());
        }
        break;
        case NONE : break;
    }

    mLaplacianRows = rows;
    mLaplacianCols = cols;
}

gsl_vector* Laplacian::Solve(LinearSolver::SOLVER solver_type)
{
    bool verbose = false;
    LinearSolver *linear = new LinearSolver();
    gsl_matrix *laplacian = ComputeLaplacian();
    gsl_vector *b_vector = ComputeBVector();

    linear->GetMatrixConditioning(laplacian);

    gsl_vector *solution1 = linear->Solve(solver_type, laplacian, b_vector);

    gsl_vector *solution = gsl_vector_alloc(3*mGraph->GetAdjacencyListSize());
    gsl_vector_set_zero(solution);

    int adjSize = mGraph->GetAdjacencyListSize();

    for(int i = 0; i < adjSize; i++)
    {
        int cpid = mGraph->GetVertexContent(i)[0];
        int row;
        if((unsigned int)GetCNT(cpid) < (*mDrawNano).size())
        {
            if(v_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, X_COORD);
                gsl_vector_set(solution, i*3, gsl_vector_get(solution1, row));
            }
            if(v_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, Y_COORD);
                gsl_vector_set(solution, i*3+1, gsl_vector_get(solution1, row));
            }
            if(v_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, Z_COORD);
                gsl_vector_set(solution, i*3+2, gsl_vector_get(solution1, row));
            }
        }
        else
        {
            if(a_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, X_COORD);
                gsl_vector_set(solution, i*3, gsl_vector_get(solution1, row));
            }
            if(a_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, Y_COORD);
                gsl_vector_set(solution, i*3+1, gsl_vector_get(solution1, row));
            }
            if(a_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid, row, Z_COORD);
                gsl_vector_set(solution, i*3+2, gsl_vector_get(solution1, row));
            }
        }
    }
    if(verbose)
    {
        std::cout<<"b_vector"<<std::endl;
        linear->PrintVector(b_vector);
        //std::cout<<"laplacian"<<std::endl;
        //linear->PrintMatrix(laplacian);
        std::cout<<"solution"<<std::endl;
        for(unsigned int i = 0 ; i < solution->size; i = i+3)
        {
            int cpid = mGraph->GetVertexContent(i/3)[0];
            std::cout<<GetCNT(cpid)<<"."<<GetIndex(cpid)<<":  ";
            std::cout<<gsl_vector_get(solution, i)  <<"   ";
            std::cout<<gsl_vector_get(solution, i+1)<<"   ";
            std::cout<<gsl_vector_get(solution, i+2)<<std::endl;
        }
    }

    gsl_matrix_free(laplacian);
    gsl_vector_free(b_vector);
    gsl_vector_free(solution1);

    return solution;
}

gsl_matrix* Laplacian::ComputeLaplacian()
{
    /// Cada linha e coluna é um ponto da componente
    /// A diagonal é a soma dos pesos da linha da matriz
    gsl_matrix *laplacian = gsl_matrix_alloc(mLaplacianRows, mLaplacianCols);
    gsl_matrix_set_zero(laplacian);

    //int attSize = mGraph->GetAttractorsSize();
    int adjSize = mGraph->GetAdjacencyListSize();
    //int vertSize = adjSize-attSize;

    int row, col;

    //LinearSolver *linear = new LinearSolver();
    for(int i = 0; i < adjSize; i++)
    {
        double sum = 0.0;
        int neighbourSize = mGraph->GetVertexNeighbourSize(i);
        int cpid_row = mGraph->GetVertexContent(i, 0)[0];
        std::vector<int> rows;

        if((unsigned int)GetCNT(cpid_row) < (*mDrawNano).size())
        {
            if(v_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, X_COORD);
                rows.push_back(row);
            }
            if(v_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Y_COORD);
                rows.push_back(row);
            }
            if(v_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Z_COORD);
                rows.push_back(row);
            }
        }
        else
        {
            if(a_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, X_COORD);
                rows.push_back(row);
            }
            if(a_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Y_COORD);
                rows.push_back(row);
            }
            if(a_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Z_COORD);
                rows.push_back(row);
            }

        }

        for(int j = 1; j < neighbourSize; j++)
        {
            glm::vec2 vert = mGraph->GetVertexContent(i, j);
            int cpid_col = vert[0];
            double weight = vert[1];
            sum += weight;

            for(int r : rows)
            {
                gsl_matrix_set(laplacian, r, r, sum);
            }
            //std::cout<<i<<" "<<j<<"  "<<GetCNT(cpid_row)<<"."<<GetIndex(cpid_row)<<"-"<<GetCNT(cpid_col)<<"."<<GetIndex(cpid_col)<<"\t";
            //std::cout<<"weight "<<weight<<" sum "<<sum<<std::endl;
            if((unsigned int)GetCNT(cpid_col) < (*mDrawNano).size())
            {
                if(v_x[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, X_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"v_x row  "<<r<<" col "<<col<<std::endl;
                        if(r >= v_x[0] && r < v_x[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
                if(v_y[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, Y_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"v_y row  "<<r<<" col "<<col<<std::endl;
                        if(r >= v_y[0] && r < v_y[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
                if(v_z[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, Z_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"v_z row  "<<r<<" col "<<col<<std::endl;
                        if(r >= v_z[0] && r < v_z[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
            }
            else
            {
                if(a_x[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, X_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"a_x row  "<<r<<" col "<<col<<std::endl;
                        if(r >= a_x[0] && r < a_x[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
                if(a_y[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, Y_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"a_y row  "<<r<<" col "<<col<<std::endl;
                        if(r >= a_y[0] && r < a_y[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
                if(a_z[1] != 0)
                {
                    GetLaplacianMatrixIndices(cpid_col, col, Z_COORD);
                    for(int r : rows)
                    {
                        //std::cout<<"a_z row  "<<r<<" col "<<col<<std::endl;
                        if(r >= a_z[0] && r < a_z[1])
                            gsl_matrix_set(laplacian, r, col, -weight);
                    }
                }
            }

        }
        rows.clear();
    }

    NormalizeLaplacian(laplacian);
    //std::cout<<"laplacian"<<std::endl;
    //linear->PrintMatrix(laplacian);

    return laplacian;
}

gsl_vector *Laplacian::ComputeBVector()
{
    gsl_vector *b_vector = gsl_vector_alloc(mLaplacianRows);
    gsl_vector_set_zero(b_vector);

    int attSize = mGraph->GetAttractorsSize();
    int adjSize = mGraph->GetAdjacencyListSize();
    int vertSize = adjSize-attSize;

    int row;

    for(int i = 0; i < adjSize; i++)
    {
        Vertex val(0.0,0.0,0.0);
        int neighbourSize = mGraph->GetVertexNeighbourSize(i);
        int cpid_row = mGraph->GetVertexContent(i, 0)[0];

        Vertex pos_row(0.0, 0.0, 0.0);

        if((unsigned int)GetCNT(cpid_row) < (*mDrawNano).size())
        {
            int cpid = mGraph->GetVertexContent(i, 0)[0];
            pos_row = (*mDrawNano)[GetCNT(cpid)]->mInterpolator->ControlPoints()[GetIndex(cpid)];
        }
        else
        {
            glm::vec3 pos = mGraph->GetAttractorPosition(i-vertSize);
            pos_row.x = pos.x;
            pos_row.y = pos.y;
            pos_row.z = pos.z;
        }

        double weight_i =  mGraph->GetVertexContent(i, 0)[1];

        for(int j = 1; j < neighbourSize; j++)
        {
            Vertex pos_col(0.0, 0.0, 0.0);
            glm::vec2 vert = mGraph->GetVertexContent(i, j);
            int cpid_col = vert[0];
            double weight_ij = vert[1];
            /// normalizando. Se weight_i = 1, não precisa dividir
            if(!FEQUAL(weight_i, 0.0))
            {
                weight_ij = weight_ij/weight_i;
            }

            if((unsigned int)GetCNT(cpid_col) < (*mDrawNano).size())
            {
                pos_col = (*mDrawNano)[GetCNT(cpid_col)]->mInterpolator->ControlPoints()[GetIndex(cpid_col)];
            }
            else
            {
                for(int k = vertSize; k < adjSize; k++)
                {
                    if(mGraph->GetVertexContent(k)[0] == cpid_col)
                    {
                        glm::vec3 pos = mGraph->GetAttractorPosition(k-vertSize);
                        pos_col.x = pos.x;
                        pos_col.y = pos.y;
                        pos_col.z = pos.z;
                        break;
                    }
                }
            }

            val.x = val.x + (pos_row.x - pos_col.x)*weight_ij;
            val.y = val.y + (pos_row.y - pos_col.y)*weight_ij;
            val.z = val.z + (pos_row.z - pos_col.z)*weight_ij;
        }

        if((unsigned int)GetCNT(cpid_row) < (*mDrawNano).size())
        {
            if(v_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, X_COORD);
                gsl_vector_set(b_vector, row, -val.x);
            }
            if(v_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Y_COORD);
                gsl_vector_set(b_vector, row, -val.y);
            }
            if(v_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Z_COORD);
                gsl_vector_set(b_vector, row, -val.z);
            }
        }
        else
        {
            if(a_x[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, X_COORD);
                gsl_vector_set(b_vector, row, -val.x);
            }
            if(a_y[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Y_COORD);
                gsl_vector_set(b_vector, row, -val.y);
            }
            if(a_z[1] != 0)
            {
                GetLaplacianMatrixIndices(cpid_row, row, Z_COORD);
                gsl_vector_set(b_vector, row, -val.z);
            }

        }

    }
    return b_vector;
}

void Laplacian::GetLaplacianMatrixIndices(int cpid, int &index, COORDINATES coordinate)
{
    index = -1; /// ERROR
    int graphIndex = -1;
    int adjSize = mGraph->GetAdjacencyListSize();
    int attSize = mGraph->GetAttractorsSize();
    int vertSize = adjSize-attSize;

    for(int i = 0; i < adjSize; i++)
    {
        if(mGraph->GetVertexContent(i, 0)[0] == cpid)
        {
            graphIndex = i;
            break;
        }
    }
    if(graphIndex == -1) return; // ponto não encontradp

    switch(coordinate)
    {
        case X_COORD :
        {
            // ponto do CNT
            if((unsigned int)GetCNT(cpid) < (*mDrawNano).size())
            {
                index = v_x[0]+graphIndex;
            }
            else
            {
                index = a_x[0]+graphIndex-vertSize;
            }
        }
        break;
        case Y_COORD :
        {
            // ponto do CNT
            if((unsigned int)GetCNT(cpid) < (*mDrawNano).size())
            {
                index = v_y[0]+graphIndex;
            }
            else
            {
                index = a_y[0]+graphIndex-vertSize;
            }
        }
        break;
        case Z_COORD :
        {
            // ponto do CNT
            if((unsigned int)GetCNT(cpid) < (*mDrawNano).size())
            {
                index = v_z[0]+graphIndex;
            }
            else
            {
                index = a_z[0]+graphIndex-vertSize;
            }
        }
        break;
        default : break;
    }
}

void Laplacian::SetMatrixLimits()
{
    int adjSize = mGraph->GetAdjacencyListSize();
    int attSize = mGraph->GetAttractorsSize();
    int vertSize = adjSize-attSize;
    int max_index = 0;

    /// Submatriz da coordenada X
    if(vertices_coord == X_COORD || vertices_coord == XY_COORD || vertices_coord == XZ_COORD || vertices_coord == XYZ_COORD)
    {
        v_x[0] = 0.0;
        v_x[1] = vertSize-1;
        max_index = v_x[1]+1;
    }
    if(attractors_coord == X_COORD || attractors_coord == XY_COORD || attractors_coord == XZ_COORD || attractors_coord == XYZ_COORD)
    {
        a_x[0] = max_index;
        a_x[1] = max_index+attSize-1;
        max_index = a_x[1]+1;
    }
    /// Submatriz da coordenada Y
    if(vertices_coord == Y_COORD || vertices_coord == XY_COORD || vertices_coord == YZ_COORD || vertices_coord == XYZ_COORD)
    {
        v_y[0] = max_index;
        v_y[1] = max_index+vertSize-1;
        max_index = v_y[1]+1;
    }
    if(attractors_coord == Y_COORD || attractors_coord == XY_COORD || attractors_coord == YZ_COORD  || attractors_coord == XYZ_COORD)
    {
        a_y[0] = max_index;
        a_y[1] = max_index+attSize-1;
        max_index = a_y[1]+1;
    }
    /// Submatriz da coordenada Z
    if(vertices_coord == Z_COORD || vertices_coord == YZ_COORD || vertices_coord == XZ_COORD || vertices_coord == XYZ_COORD)
    {
        v_z[0] = max_index;
        v_z[1] = max_index+vertSize-1;
        max_index = v_z[1]+1;
    }
    if(attractors_coord == Z_COORD || attractors_coord == YZ_COORD || attractors_coord == XZ_COORD || attractors_coord == XYZ_COORD)
    {
        a_z[0] = v_z[1]+1;
        a_z[1] = v_z[1]+attSize;
        max_index = a_z[1]+1;
    }
    bool verbose = false;
    if(verbose)
    {
        std::cout<<"Limits"<<std::endl;
        std::cout<<"v_x  ["<<v_x[0]<<", "<<v_x[1]<<"]"<<std::endl;
        std::cout<<"v_y  ["<<v_y[0]<<", "<<v_y[1]<<"]"<<std::endl;
        std::cout<<"v_z  ["<<v_z[0]<<", "<<v_z[1]<<"]\n"<<std::endl;
        std::cout<<"a_x  ["<<a_x[0]<<", "<<a_x[1]<<"]"<<std::endl;
        std::cout<<"a_y  ["<<a_y[0]<<", "<<a_y[1]<<"]"<<std::endl;
        std::cout<<"a_z  ["<<a_z[0]<<", "<<a_z[1]<<"]"<<std::endl;
    }
}

void Laplacian::NormalizeLaplacian(gsl_matrix *laplacian)
{
    for(unsigned int i = 0; i < laplacian->size1; i++)
    {
        for(unsigned int j = 0; j < laplacian->size2; j++)
        {
            gsl_matrix_set(laplacian, i, j, gsl_matrix_get(laplacian, i, j)/gsl_matrix_get(laplacian, i, i));
        }
    }
}

unsigned int Laplacian::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int Laplacian::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int Laplacian::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}
}
