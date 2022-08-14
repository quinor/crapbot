#include "kinematics.h"

#include <math.h>

// TODO measure all of those
static const float srv_dist = 36;
static const float a1_len = 78;
static const float a2_len = 78;
static const float b1_len = 122;
static const float b2_len = 122;
static const float c_len = 47;

static const vec_t P1 = {0, srv_dist/2.f};
static const vec_t P2 = {0, -srv_dist/2.f};


// returns C = circle intersection such that A, C, B are clockwise
static vec_t circle_intersection (vec_t A, float rA, vec_t B, float rB)
{
    float d2 = vec_norm2(vec_diff(A,B));
    float id = 1/sqrtf(d2);
    float a = (rA*rA - rB*rB + d2) * 0.5f * id;
    float h = sqrtf(rA*rA - a*a);

    vec_t m = vec_sum(A, vec_scale(vec_diff(B, A), a*id));
    vec_t C = vec_sum(m, vec_scale(vec_rot90(vec_diff(B, A)), h*id));
    return C;
}


vec_t cartesian_to_crap (vec_t cartesian)
{
    vec_t D = cartesian;
    vec_t A = circle_intersection(P1, a1_len, D, b1_len + c_len);
    vec_t C = vec_sum(D, vec_scale(vec_diff(A, D), c_len/(b1_len + c_len)));
    vec_t B = circle_intersection(C, b2_len, P2, a2_len);

    vec_t arm1 = vec_diff(A, P1);
    vec_t arm2 = vec_diff(B, P2);

    return (vec_t){.x=vec_atan2(arm1), .y=vec_atan2(arm2)};
}

vec_t crap_to_cartesian (vec_t crap)
{
    vec_t arm1 = vec_scale(vec_angle(crap.x), a1_len);
    vec_t arm2 = vec_scale(vec_angle(crap.y), a2_len);

    vec_t A = vec_sum(arm1, P1);
    vec_t B = vec_sum(arm2, P2);

    vec_t C = circle_intersection(A, b1_len, B, b2_len);
    vec_t D = vec_sum(C, vec_scale(vec_diff(C, A), c_len/b2_len));

    return D;
}
