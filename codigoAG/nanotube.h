#ifndef __NANOTUBE_H__
    #define __NANOTUBE_H__

    #include "point.h"

    typedef struct nanotube_s {
        int size;
        double diamInn;
        double diamOut;
        double radiusOut;
        double growthRate;
        double growthAngle;
        double secondInertia;
        double sectionArea;
        int dof;
        int maxSegm;
        double segLength;
        point_t* points;
    } nanotube_t;
#endif
