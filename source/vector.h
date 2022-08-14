#pragma once

typedef struct vec
{
    float x;
    float y;
} vec_t;


vec_t vec_angle(float theta);
vec_t vec_scale(vec_t v, float scale);
vec_t vec_sum(vec_t v1, vec_t v2);
vec_t vec_diff(vec_t v1, vec_t v2);
vec_t vec_complex_prod(vec_t v1, vec_t v2);
float vec_dot_prod(vec_t v1, vec_t v2);
float vec_cross_prod(vec_t v1, vec_t v2);
float vec_norm2(vec_t v);
float vec_norm(vec_t v);
float vec_atan2(vec_t v);
vec_t vec_complex_conj(vec_t v);
vec_t vec_flip(vec_t v);
vec_t vec_rot90(vec_t v);
