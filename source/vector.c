#include "vector.h"

#include <math.h>


vec_t vec_angle(float theta)
{
    return (vec_t){.x=cosf(theta), .y=sinf(theta)};
}

vec_t vec_scale(vec_t v, float scale)
{
    return (vec_t){v.x*scale, v.y*scale};
}

vec_t vec_sum(vec_t v1, vec_t v2)
{
    return (vec_t){v1.x+v2.x, v1.y+v2.y};
}

vec_t vec_diff(vec_t v1, vec_t v2)
{
    return (vec_t){v1.x-v2.x, v1.y-v2.y};
}

vec_t vec_complex_prod(vec_t v1, vec_t v2)
{
    return (vec_t){v1.x*v2.x - v1.y*v2.y, v1.x*v2.y + v1.y*v2.x};
}

float vec_dot_prod(vec_t v1, vec_t v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

float vec_cross_prod(vec_t v1, vec_t v2)
{
    return v1.x*v2.y - v2.x*v1.y;
}

float vec_norm2(vec_t v)
{
    return v.x*v.x + v.y*v.y;
}

float vec_norm(vec_t v)
{
    return sqrtf(vec_norm2(v));
}

float vec_atan2(vec_t v)
{
    return atan2f(v.y, v.x);
}

vec_t vec_complex_conj(vec_t v)
{
    return (vec_t){v.x, -v.y};
}

vec_t vec_flip(vec_t v)
{
    return (vec_t){v.y, v.x};
}

vec_t vec_rot90(vec_t v)
{
    return (vec_t){-v.y, v.x};
}
