#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "gcg.h"
#include <gsl/gsl_vector.h>

struct _Vertex
{
    double x, y, z;

    _Vertex(double x, double y, double z);
    _Vertex();

    double& operator[](int i);
    struct _Vertex operator+(const struct _Vertex& vert);
    struct _Vertex operator-(const struct _Vertex& vert);

    void Normalize();
    struct _Vertex Cross( struct _Vertex& vert);
    double Distance(struct _Vertex& vert);
    double Length();
};

struct _SPoint
{
    _SPoint(double x, double y, double z, double pos);
    struct _Vertex position;
    double arcPosition;

    double& operator[] (int i);
};

typedef struct _SPoint SPoint;
typedef struct _Vertex Vertex;


/** Create the spline and precompute some of the values
  *
  */
class CatmullRom
{
public:
    CatmullRom(int precomputedPoints);
    CatmullRom();

    int PushControlPoint(double x, double y, double z);
    void PopControlPoint();

    std::vector<Vertex> ControlPoints() const;
    Vertex ControlPoint(int index);
    int ControlPointsNumber() const;
    double ArcLength() const;
    double ArcPosition(int index);

    Vertex PointAt(double arcPosition);
    glm::vec3 vPointAt(double arcPosition);
    Vertex PointAt(double arcPosition, double cMat[4][3], int &index, double &lerp);
    void TransformMatrix(double arcPosition, MATRIX4d mat);
    glm::mat4 TransformMatrix(double arcPosition);
    void TranslateControlPoint(int index, double x, double y, double z);

    void InterpolateLastPoint();

    Vertex GetTangent(double arcPosition);
    void UpdateControlPoint(int index, double x, double y, double z);


private:
    std::vector<SPoint> mControlPoints;
    std::vector<double> mPrecomputedPoints;
    std::vector<SPoint> mPrecomputedBitangents;

    static double sCatmullRomMatrix[4][4];

    //Helper functions
    void CalculateCMatrix(double mat[4][3], int i);
    Vertex Point(double mat[4][3], double u[4]);

    int mSampleNumber;
    const int mBitangentSampleNumber;


};
