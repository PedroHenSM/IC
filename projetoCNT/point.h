#ifndef __POINT_H__
    #define __POINT_H__

    #ifndef EPSILON
        #define EPSILON 0.0000077
    #endif

    #ifndef FEQUAL
        #define FEQUAL(a, b) (fabs((a)-(b)) < EPSILON)
    #endif

    #ifndef MIN
        #define MIN(a, b) (a < b ? a : b)
    #endif

    #ifndef MAX
        #define MAX(a, b) (a > b ? a : b)
    #endif

    #ifndef CLAMP
        #define CLAMP(x, minVal, maxVal) MIN(MAX(x, minVal), maxVal)
    #endif

    typedef struct point_s {
        int id;
        double x;
        double y;
        double z;
    } point_t;

    double point_compute_distance(point_t, point_t, point_t, point_t);
#endif
