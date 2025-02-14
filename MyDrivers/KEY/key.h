/*
 * key.h
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#ifndef MYDRIVERS_KEY_KEY_H_
#define MYDRIVERS_KEY_KEY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "drv_gpio.h"

typedef struct KeyData
{
    uint8_t state;
    uint8_t num;
    rt_time_t startTime;
    rt_time_t endTime;
    rt_time_t midTime;
}KeyData;

#define KEY_PB03 GET_PIN(B, 3)

void KeyPB03_Irq_entry(void *parameter);

#ifdef __cplusplus
}
#endif

#endif /* MYDRIVERS_KEY_KEY_H_ */
