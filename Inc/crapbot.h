#pragma once

#include "main.h"
#include <stdint.h>


// timer interrupt pushing steps into the stepper driver reading a) from buffer
// b) from speed setting

#define QUEUE_SIZE (1 << 5)

static volatile struct pos_t
{
    uint16_t p1;
    uint16_t p2;
} queue[QUEUE_SIZE];

static volatile uint32_t element_count = 0;
static uint32_t write_head = 0;
static uint32_t read_head = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim != &htim1)
        return;

    if (element_count == 0)
        return;

    // read the element

    struct pos_t elt = queue[read_head++];
    read_head &= QUEUE_SIZE-1;

    __atomic_fetch_sub(&element_count, 1, __ATOMIC_RELEASE);

    htim1.Instance->CCR1 = elt.p1;
    htim1.Instance->CCR2 = elt.p2;
}

void servo_goto(uint16_t p1, uint16_t p2)
{
    struct pos_t next = {.p1=p1, .p2=p2};
    while (element_count != QUEUE_SIZE);
    queue[write_head++] = next;
    write_head &= QUEUE_SIZE-1;
    __atomic_fetch_add(&element_count, 1, __ATOMIC_RELEASE);
}



void setup()
{
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}


void loop()
{
    // htim1.Instance->CCR1 = 50;
    // htim1.Instance->CCR2 = 100;
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    HAL_Delay(1000);

    // htim1.Instance->CCR1 = 100;
    // htim1.Instance->CCR2 = 50;
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    HAL_Delay(1000);
}
