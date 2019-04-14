#ifndef __FOREST_H__
    #define __FOREST_H__

    #include "nanotube.h"
    #include "point.h"

    #define FOREST_READ_BUFFER_SIZE 1024

    typedef struct forest_s {
        int seed;
        int totalCNTs;
        double spacing;
        int growthSteps;
        double minX;
        double maxX;
        double sigma;
        int density;
        int diamInn;
        int diamOut;
        int growthRate;
        int growthAngle;
        int captureDist;
        double vdWStiffness;
        double distance;
        nanotube_t* nanotubes;
        point_t* buffer;
    } forest_t;

    forest_t* forest_create(double);
    void forest_print(forest_t*);
    void forest_read_attributes(forest_t*, char[]);
    void forest_read_simulation(forest_t*, char[]);
    void forest_read_solution(forest_t*, char[]);
    void forest_write_attributes(forest_t*, char[]);
    void forest_write_simulation(forest_t*, char[]);
    void forest_destroy(forest_t*);
#endif
