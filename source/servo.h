#pragma once

#include <stdint.h>
#include "vector.h"

void servo_setup(void);

// set servos to angles v.x and v.y (in radians) in the next tick
void servo_goto(vec_t v);

void servo_goto_raw(uint16_t p1, uint16_t p2);
