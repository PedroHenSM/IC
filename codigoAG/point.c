#include <math.h>

#include "point.h"

double point_compute_distance(point_t p1_, point_t p2_, point_t q1_, point_t q2_) {
    point_t r__;
    // Direction vector of segment S1.
    point_t d1_;
    // Direction vector of segment S2
    point_t d2_;

    // Vector d1 = q1 - p1;
    d1_.x = q1_.x - p1_.x;
    d1_.y = q1_.y - p1_.y;
    d1_.z = q1_.z - p1_.z;

    // Vector d2 = q2 - p2;
    d2_.x = q2_.x - p2_.x;
    d2_.y = q2_.y - p2_.y;
    d2_.z = q2_.z - p2_.z;

    // Vector r = p1 - p2;
    r__.x = p1_.x - p2_.x;
    r__.y = p1_.y - p2_.y;
    r__.z = p1_.z - p2_.z;

    double a, e, f, s, t;

    a = d1_.x * d1_.x + d1_.y * d1_.y + d1_.z * d1_.z; // Squared length of segment S1, always nonnegative
    e = d2_.x * d2_.x + d2_.y * d2_.y + d2_.z * d2_.z; // Squared length of segment S1, always nonnegative
    f = d2_.x * r__.x + d2_.y * r__.y + d2_.z * r__.z;

    if ((FEQUAL(a, EPSILON) == 1 || a <= EPSILON) && (FEQUAL(e, EPSILON) == 1 || e <= EPSILON)) {
        // Both segments degenerate into points
        return sqrt(r__.x * r__.x + r__.y * r__.y + r__.z * r__.z);
    }

    if (FEQUAL(a, EPSILON) == 1 && a <= EPSILON) {
        // First segment degenerates into a point
        s = 0.0;
        t = f / e; // s = 0 => t = (b*s + f) / e = f / e
        t = CLAMP(t, 0.0, 1.0);
    } else {
        double c = d1_.x * r__.x + d1_.y * r__.y + d1_.z * r__.z;

        if (FEQUAL(e, EPSILON) == 1 || e <= EPSILON) {
            // Second segment degenerates into a point
            t = 0.0f;
            s = CLAMP(-c / a, 0.0, 1.0); // t = 0 => s = (b*t - c) / a = -c / a
        } else {
            // The general nondegenerate case starts here
            double b = d1_.x * d2_.x + d1_.y * d2_.y + d1_.z * d2_.z;

            double denom = a * e - b * b; // Always nonnegative

            // If segments not parallel, compute closest point on L1 to L2 and
            // clamp to segment S1. Else pick arbitrary s (here 0)
            ///if (denom != 0.0f) {
            if (FEQUAL(denom, 0) == 0) {
                s = CLAMP((b * f - c * e) / denom, 0.0, 1.0);
            } else {
                s = 0.0;
            }

            // Compute point on L2 closest to S1(s) using
            // t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
            t = (b * s + f) / e;
            // If t in [0,1] done. Else clamp t, recompute s for the new value
            // of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
            // and clamp s to [0, 1]
            if (t < 0.0f) {
                t = 0.0f;
                s = CLAMP(-c / a, 0.0, 1.0);
            } else {
                if (t > 1.0) {
                    t = 1.0;
                    s = CLAMP((b - c) / a, 0.0, 1.0);
                }
            }
        }
    }

    point_t d1_s;
    d1_s.x = d1_.x * s;
    d1_s.y = d1_.y * s;
    d1_s.z = d1_.z * s;

    point_t d2_s;
    d2_s.x = d2_.x * t;
    d2_s.y = d2_.y * t;
    d2_s.z = d2_.z * t;

    d1_s.x = d1_s.x + p1_.x;
    d1_s.y = d1_s.y + p1_.y;
    d1_s.z = d1_s.z + p1_.z;

    d2_s.x = d2_s.x + p2_.x;
    d2_s.y = d2_s.y + p2_.y;
    d2_s.z = d2_s.z + p2_.z;

    //pt1 = d1_s;
    //pt2 = d2_s;

    d1_s.x = d1_s.x - d2_s.x;
    d1_s.y = d1_s.y - d2_s.y;
    d1_s.z = d1_s.z - d2_s.z;

    return sqrt(d1_s.x * d1_s.x + d1_s.y * d1_s.y + d1_s.z * d1_s.z);
}
