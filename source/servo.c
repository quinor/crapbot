#include "servo.h"
#include "main.h"

#include <math.h>

#define QUEUE_SIZE (1 << 5)

#define SRV1_MIN (-M_PI*0.25f)
#define SRV1_MAX (M_PI*0.75f)
#define SRV1_OFFET 30

#define SRV2_MIN (-M_PI*0.75f)
#define SRV2_MAX (M_PI*0.25f)
#define SRV2_OFFSET 60

#define SRV_MININT 250
#define SRV_MAXINT 1250

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

void servo_setup()
{
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

static inline uint16_t interpolate(
    float beg, float end, float ilen, float p,
    int16_t out_beg, int16_t out_end
)
{
    int16_t ret = out_beg;
    ret += (out_end-out_beg) * ((p-beg) * ilen );

    if (ret > out_end) ret = out_end;
    if (ret < out_beg) ret = out_beg;
    return ret;
}

void servo_goto(vec_t v)
{
    uint16_t p1 = interpolate(
        SRV1_MIN, SRV1_MAX, 1.f/(SRV1_MAX-SRV1_MIN),
        v.x, SRV_MININT, SRV_MAXINT
    ) + SRV1_OFFET;
    uint16_t p2 = interpolate(
        SRV2_MIN, SRV1_MAX, 1.f/(SRV2_MAX-SRV2_MIN),
        v.y, SRV_MININT, SRV_MAXINT
    ) + SRV2_OFFSET;

    struct pos_t next = {.p1=p1, .p2=p2};
    while (element_count == QUEUE_SIZE);
    queue[write_head++] = next;
    write_head &= QUEUE_SIZE-1;
    __atomic_fetch_add(&element_count, 1, __ATOMIC_RELEASE);
}

void servo_goto_raw(uint16_t p1, uint16_t p2)
{
    struct pos_t next = {.p1=p1, .p2=p2};
    while (element_count == QUEUE_SIZE);
    queue[write_head++] = next;
    write_head &= QUEUE_SIZE-1;
    __atomic_fetch_add(&element_count, 1, __ATOMIC_RELEASE);
}
