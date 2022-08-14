#include "plot.h"
#include "servo.h"
#include "kinematics.h"

#include <math.h>

static const float speed = 50; // mm/s
static const float hz = 50;
static const float step_size = speed/hz;


static vec_t origin;
static vec_t cur;

void plot_init(void)
{
    vec_t zero = {0.375f*M_PI, -0.375f*M_PI};
    origin = cur = crap_to_cartesian(zero);
    servo_goto(zero);
}

void plot_abs(vec_t position)
{
    // for (int i=0; i<50; i++)
    //     servo_goto(cartesian_to_crap(vec_sum(cur, (vec_t){0, i})));

    plot_rel(vec_diff(vec_sum(origin, position), cur));
}

void plot_rel(vec_t offset)
{
    float len = vec_norm(offset);
    int steps = ceilf(len / step_size);
    float isteps = 1.f/steps;
    for (int i=1; i<steps; i++)
        servo_goto(cartesian_to_crap(
            vec_sum(cur, vec_scale(offset, i*isteps))
        ));

    cur = vec_sum(cur, offset);
}
