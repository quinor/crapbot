#include "main.h"
#include "servo.h"
#include "vector.h"
#include "plot.h"

#include <math.h>


void setup()
{
    servo_setup();
    plot_init();
    while (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin));
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}


void loop()
{
    plot_abs((vec_t){-25, -25});
    plot_abs((vec_t){-25, 25});
    plot_abs((vec_t){25, 25});
    plot_abs((vec_t){25, -25});
}
