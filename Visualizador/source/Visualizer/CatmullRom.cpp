#include "CatmullRom.h"
#include <cmath>
#include <iostream>
#include <gsl/gsl_multiroots.h>


double CatmullRom::sCatmullRomMatrix[4][4] = {{ 0.0, 1.0, 0.0, 0.0},
                                             {-0.5, 0.0, 0.5, 0.0},
                                             { 1.0,-2.5, 2.0,-0.5},
                                             {-0.5, 1.5,-1.5, 0.5}};

CatmullRom::CatmullRom(int precomputedPoints)
    : mControlPoints(), mPrecomputedPoints(), mPrecomputedBitangents(), mSampleNumber(precomputedPoints), mBitangentSampleNumber(5)
{
}

CatmullRom::CatmullRom()
    : mControlPoints(), mPrecomputedPoints(), mPrecomputedBitangents(), mSampleNumber(700), mBitangentSampleNumber(7)
{
}

int CatmullRom::PushControlPoint(double x, double y, double z)
{
    SPoint point(x, y, z, -1);
    if(mControlPoints.size() == 1) point.arcPosition = 0.0;

    mControlPoints.push_back(point);

    // If the spline have 4 or more points, pre-compute the points and estimate the arc length
    if(mControlPoints.size() >= 4)
    {
        double mat[4][3];
        CalculateCMatrix(mat, mControlPoints.size()-3);

        Vertex lastPoint = mControlPoints[mControlPoints.size()-3].position;

        double length = mControlPoints[mControlPoints.size()-3].arcPosition;
        double spacing = 1.0 / (mSampleNumber + 1);

        Vertex lastBiTangent;
        if(mPrecomputedBitangents.size() == 0)
        {
            lastBiTangent[0] = 0;
            lastBiTangent[1] = 0;
            lastBiTangent[2] = 1;
        }
        else
            lastBiTangent = mPrecomputedBitangents[mPrecomputedBitangents.size()-1].position;

        for(int i = 0; i <= mSampleNumber+1; i++)
        {
            double t = (t == mSampleNumber+1) ? 1.0 : i*spacing;
            double u[4] = {1, t, t*t, t*t*t};

            Vertex pt = Point(mat, u);
            Vertex d = pt - lastPoint;

            length += d.Length();

            if(i == mSampleNumber+1 || i == 0) mControlPoints[mControlPoints.size()-2].arcPosition = length;
            else mPrecomputedPoints.push_back(length);

            // Calculate the bitangent
            if(i % (mSampleNumber/mBitangentSampleNumber) == 0 && i != mSampleNumber)
            {
                double du[4] = {0, 1, 2*t, 3*t*t};
                Vertex tg = Point(mat, du);
                tg.Normalize();
                Vertex nm = lastBiTangent.Cross(tg);
                nm.Normalize();
                Vertex bt = tg.Cross(nm);
                bt.Normalize();

                lastBiTangent.x = bt.x;
                lastBiTangent.y = bt.y;
                lastBiTangent.z = bt.z;

                SPoint bitanget(bt.x, bt.y, bt.z, t);
                mPrecomputedBitangents.push_back(bitanget);

            }

            lastPoint = pt;
        }

    }

    return mControlPoints.size() - 1;
}

void CatmullRom::InterpolateLastPoint()
{
    int first = mControlPoints.size()-3;
    double y = 2.0 * mControlPoints[mControlPoints.size()-1].position.y - mControlPoints[mControlPoints.size()-2].position.y;

    double sum = 0.0;

    for(unsigned int i = first; i < mControlPoints.size(); i++)
    {
        double num = mControlPoints[i].position.x;
        double div = 1.0;

        for(int j = 0; j < 3; j++)
        {
            unsigned int index = first + j;
            if(index == i) continue;

            num *= (y - mControlPoints[index].position.y);
            div *= (mControlPoints[i].position.y - mControlPoints[index].position.y);
        }
        sum += (num / div);
    }
    PushControlPoint(sum, y, 0.0);
}

void CatmullRom::PopControlPoint()
{
    mControlPoints.pop_back();
    if(mControlPoints.size() < 4)
    {
        mControlPoints[mControlPoints.size()-1].arcPosition = -1;
    }
    for(int i = 0; i < mSampleNumber; i++)
    {
        mPrecomputedPoints.pop_back();
    }

}

std::vector<Vertex> CatmullRom::ControlPoints() const
{
    std::vector<Vertex> vertexList;
    for(unsigned int i = 0; i < mControlPoints.size(); i++)
    {
        Vertex vert(mControlPoints[i].position.x, mControlPoints[i].position.y, mControlPoints[i].position.z);
        vertexList.push_back(vert);
    }
    return vertexList;
}

Vertex CatmullRom::ControlPoint(int index)
{
    if(index < 0 || index >= mControlPoints.size()) return Vertex(-1.0, -1.0, -1.0);

    Vertex vert(mControlPoints.at(index).position.x, mControlPoints.at(index).position.y, mControlPoints.at(index).position.z);

    return vert;
}

void CatmullRom::UpdateControlPoint(int index, double x, double y, double z)
{
    SPoint point(x, y, z, -1);
    if(index == 1) point.arcPosition = 0.0;

    mControlPoints[index] = point;

    // If the spline have 4 or more points, pre-compute the points and estimate the arc length
    if(mControlPoints.size() >= 4)
    {
        for(int k = index-2; k < (int)mControlPoints.size()-2; k++)
        {
            if(k < 1) continue;

            double mat[4][3];
            CalculateCMatrix(mat, k);

            Vertex lastPoint = mControlPoints[k].position;

            double length = mControlPoints[k].arcPosition;
            double spacing = 1.0 / (mSampleNumber + 1);

            Vertex lastBiTangent;
            if(mPrecomputedBitangents.size() == 0)
            {
                lastBiTangent[0] = 0;
                lastBiTangent[1] = 0;
                lastBiTangent[2] = 1;
            }
            else
                lastBiTangent = mPrecomputedBitangents[mBitangentSampleNumber*(k-1)].position;

            int btgPos = mBitangentSampleNumber*(k-1);

            for(int i = 0; i <= mSampleNumber+1; i++)
            {
                double t = (t == mSampleNumber+1) ? 1.0 : i*spacing;
                double u[4] = {1, t, t*t, t*t*t};

                Vertex pt = Point(mat, u);
                Vertex d = pt - lastPoint;

                length += d.Length();

                if(i == mSampleNumber+1 || i == 0) mControlPoints[k+1].arcPosition = length;
                else mPrecomputedPoints[mSampleNumber*(k-1)+i-1] = length;

                // Calculate the bitangent
                if(i % (mSampleNumber/mBitangentSampleNumber) == 0 && i != mSampleNumber)
                {
                    double du[4] = {0, 1, 2*t, 3*t*t};
                    Vertex tg = Point(mat, du);
                    tg.Normalize();
                    Vertex nm = lastBiTangent.Cross(tg);
                    nm.Normalize();
                    Vertex bt = tg.Cross(nm);
                    bt.Normalize();

                    lastBiTangent.x = bt.x;
                    lastBiTangent.y = bt.y;
                    lastBiTangent.z = bt.z;

                    SPoint bitanget(bt.x, bt.y, bt.z, t);
                    mPrecomputedBitangents[++btgPos] = bitanget;

                }

                lastPoint = pt;
            }
        }

    }
}

int CatmullRom::ControlPointsNumber() const
{
    return mControlPoints.size();
}

double CatmullRom::ArcLength() const
{
    return mControlPoints[mControlPoints.size()-2].arcPosition;
}

glm::vec3 CatmullRom::vPointAt(double arcPosition)
{
    Vertex v = PointAt(arcPosition);
    glm::vec3 vec(v.x, v.y, v.z);
    return vec;
}

Vertex CatmullRom::PointAt(double arcPosition)
{
    Vertex pt(0, 0, 0);

    // If the arc position is inside the arc of the spline search between the control points
    if(arcPosition <= ArcLength())
    {
        int a = 1, b = mControlPoints.size()- 2, i;
        while(true)
        {
            i = (a+b)/2;
            //std::cout << "a: " << a << " b: " << b << " - p(i): " << mControlPoints[i].arcPosition << " arcPosition:" << arcPosition << std::endl;
            if(FEQUAL(mControlPoints[i].arcPosition, arcPosition))
                return mControlPoints[i].position;
            else if(mControlPoints[i].arcPosition > arcPosition)
                b = i;
            else
                a = i;

            if(a+1 == b)
            {
                if(FEQUAL(mControlPoints[a].arcPosition, arcPosition)) return mControlPoints[a].position;
                else if(FEQUAL(mControlPoints[b].arcPosition, arcPosition)) return mControlPoints[b].position;
                else break;
            }
        }

        int c = (a-1)*mSampleNumber, d = a*mSampleNumber;
        double u; // spline interpolation value
        while(true)
        {
            i = floor((c+d)/2.0);
            //std::cout << "c: " << c << " d: " << d << " - p(i): " << mPrecomputedPoints[i] << " arcPosition:" << arcPosition << std::endl;
            if(mPrecomputedPoints[i] == arcPosition)
            {
                u = ((double)i - (a-1)*mSampleNumber) / mSampleNumber;
                break;
            }
            if(mPrecomputedPoints[i] > arcPosition)
                d = i;
            else
                c = i;

            // Found the
            if(c+1 == d)
            {
                double f = (mPrecomputedPoints[c] - arcPosition)/(mPrecomputedPoints[c] - mPrecomputedPoints[d]);
                u = ((double)c + f - (a-1)*mSampleNumber) / mSampleNumber;
                break;
            }
        }
        //std::cout << "i: " << i << std::endl;

        // Now interpolates the spline segment
        double mat[4][3];
        CalculateCMatrix(mat, a);

        double t[4] = {1, u, u*u, u*u*u};
        pt = Point(mat, t);

        return pt;
    }
    return pt;
}

Vertex CatmullRom::PointAt(double arcPosition, double cMat[4][3], int &index, double &lerp)
{
    Vertex pt(0, 0, 0);

    //std::cout << arcPosition << std::endl;

    // If the arc position is inside the arc of the spline search between the control points
    if(arcPosition < ArcLength() || FEQUAL(arcPosition, ArcLength()))
    {
        int a = 1, b = mControlPoints.size()- 2, i;
        while(true)
        {
            i = (a+b)/2;
            //std::cout << "a: " << a << " b: " << b << " - p(i): " << mControlPoints[i].arcPosition << " arcPosition:" << arcPosition << std::endl;
            if(FEQUAL(mControlPoints[i].arcPosition, arcPosition))
            {
                CalculateCMatrix(cMat, i);
                index = i;
                lerp = 0.0;
                return mControlPoints[i].position;
            }
            else if(mControlPoints[i].arcPosition > arcPosition)
                b = i;
            else
                a = i;

            if(a+1 == b)
            {
                if(FEQUAL(mControlPoints[a].arcPosition, arcPosition))
                {
                    CalculateCMatrix(cMat, a);
                    index = a;
                    lerp = 0.0;
                    return mControlPoints[a].position;
                }
                else if(FEQUAL(mControlPoints[b].arcPosition, arcPosition))
                {
                    CalculateCMatrix(cMat, a);
                    index = a;
                    lerp = 1.0;
                    return mControlPoints[b].position;
                }
                else break;
            }
        }
        //std::cout << "i: " << i << std::endl;

        //After finding the control points the arc position is between search for the precomputed values
        int c = (a-1)*mSampleNumber, d = a*mSampleNumber - 1;
        double u; // spline interpolation value
        while(true)
        {
            i = floor((c+d)/2.0);
            //std::cout << "c: " << c << " d: " << d << " - p(i): " << mPrecomputedPoints[i] << " arcPosition:" << arcPosition << std::endl;
            if(FEQUAL(mPrecomputedPoints[i], arcPosition))
            {
                u = ((double)i - (a-1)*mSampleNumber +1) / (mSampleNumber+1);
                break;
            }
            if(mPrecomputedPoints[i] > arcPosition)
                d = i;
            else
                c = i;

            // Found the
            if(c+1 == d)
            {
                double f = (arcPosition - mPrecomputedPoints[c])/(mPrecomputedPoints[d] - mPrecomputedPoints[c]);
                u = ((double)c + f - (a-1)*mSampleNumber+1) / (mSampleNumber+1);
                break;
            }
        }

        // Now interpolates the spline segment
        CalculateCMatrix(cMat, a);

        double t[4] = {1, u, u*u, u*u*u};
        pt = Point(cMat, t);

        index = a;
        lerp = std::min(std::max(u, 0.0), 1.0);

        return pt;
    }
    return pt;
}

glm::mat4 CatmullRom::TransformMatrix(double arcPosition)
{
    MATRIX4d mat;
    TransformMatrix(arcPosition, mat);
    glm::mat4 tMatrix( mat[0],  mat[1],  mat[2],  mat[3],
                       mat[4],  mat[5],  mat[6],  mat[7],
                       mat[8],  mat[9],  mat[10], mat[11],
                       mat[12], mat[13], mat[14], mat[15]);

    return tMatrix;
}

//void CatmullRom::TransformMatrix(double arcPosition, double mat[4][4])
void CatmullRom::TransformMatrix(double arcPosition, MATRIX4d mat)
{
    //if(arcPosition <= 0.1) arcPosition = 0.1;

    double cMat[4][3];
    int a = 1;
    double t = 0.0;


    Vertex v = PointAt(arcPosition, cMat, a, t);

    // Calculate the tangent vector
    double d[4] = {0, 1, 2*t, 3*t*t};
    Vertex tg = Point(cMat, d);
    tg.Normalize();

    // Get an estimate bitangent from pre-calculated values
    int s = floor(t / (1.0f / (mBitangentSampleNumber)));
    Vertex btg = mPrecomputedBitangents[(a-1)*mBitangentSampleNumber + s].position;

    Vertex nm = btg.Cross(tg);
    nm.Normalize();
    Vertex bt = tg.Cross(nm);
    bt.Normalize();

    /*mat[0][1] = 0;
    mat[1][1] = 0;
    mat[2][1] = 0;
    mat[0][3] =  v[0];

    mat[0][0] = bt[0];
    mat[1][0] = bt[1];
    mat[2][0] = bt[2];
    mat[1][3] =  v[1];

    mat[0][2] = nm[0];
    mat[1][2] = nm[1];
    mat[2][2] = nm[2];
    mat[2][3] =  v[2];

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][3] = 0;
    mat[3][3] = 1;*/

    gcgSETMATRIX4( mat, bt[0],    0, nm[0],  v[0],
                        bt[1],    0, nm[1],  v[1],
                        bt[2],    0, nm[2],  v[2],
                            0,    0,     0,     1);
}

void CatmullRom::CalculateCMatrix(double mat[4][3], int i)
{
    for(int c = 0; c < 3; c++)
    {
        for(int l = 0; l < 4; l++)
        {
            mat[l][c] = 0;
            for(int j = 0; j < 4; j++)
            {
                mat[l][c] += sCatmullRomMatrix[l][j] * mControlPoints[j+i-1][c];
            }
        }
    }
}

Vertex CatmullRom::Point(double mat[4][3], double u[4])
{
    Vertex point;
    for(int c = 0; c < 3; c++)
    {
        point[c] = 0.0;
        for(int j = 0; j < 4; j++)
        {
            point[c] += u[j] * mat[j][c];
        }
    }
    return point;
}

double CatmullRom::ArcPosition(int index)
{
    return mControlPoints[index].arcPosition;
}

void CatmullRom::TranslateControlPoint(int index, double x, double y, double z)
{
    SPoint p = mControlPoints[index];
    UpdateControlPoint(index, p.position.x + x, p.position.y + y, p.position.z + z);
}

Vertex CatmullRom::GetTangent(double arcPosition)
{
    double cMat[4][3];
    double t = 0.0;
    //int a = 1; /// indice do ponto de controle
    //Vertex v = PointAt(arcPosition, cMat, a, t);
    double d[4] = {0, 1, 2*t, 3*t*t};
    Vertex tg = Point(cMat, d);
    tg.Normalize(); /// Nao normalizar pois essa funcao eh usada como se fosse a derivada da curva
    return tg;
}

Vertex::_Vertex(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vertex::_Vertex()
{
    x = 0;
    y = 0;
    z = 0;
}

struct _Vertex _Vertex::operator+(const struct _Vertex& vert)
{
    struct _Vertex v(x+vert.x, y+vert.y, z+vert.z);
    return v;
};

struct _Vertex _Vertex::operator-(const struct _Vertex& vert)
{
    struct _Vertex v(x-vert.x, y-vert.y, z-vert.z);
    return v;
};

double _Vertex::Length()
{
    return sqrt(x*x + y*y + z*z);
}

void _Vertex::Normalize()
{
    double norm = Length();
    x /= norm;
    y /= norm;
    z /= norm;
}

struct _Vertex _Vertex::Cross( struct _Vertex& vert)
{
    struct _Vertex cross;
    cross.x =  y*vert.z - vert.y*z;
    cross.y = -x*vert.z + vert.x*z;
    cross.z =  x*vert.y - vert.x*y;
    return cross;
};

double& _Vertex::operator[](int i)
{
    switch(i)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        return x;
    }
}

double _Vertex::Distance(struct _Vertex& vert)
{
    return sqrt( (x-vert[0])*(x-vert[0]) + (y-vert[1])*(y-vert[1]) + (z-vert[2])*(z-vert[2]) );
}

//SPoint mathods
_SPoint::_SPoint(double x, double y, double z, double pos) : position(x, y, z), arcPosition(pos)
{
}

double& _SPoint::operator[] (int i)
{
    switch(i)
    {
    case 0:
    case 1:
    case 2:
        return position[i];
    case 3:
        return arcPosition;
    default:
        return position[0];
    }
}
