/*
 * led.h
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#ifndef MYDRIVERS_LED_LED_H_
#define MYDRIVERS_LED_LED_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"

#define LED_PIN_RED GET_PIN(A,15)   // PA15
#define LED_PIN_GREEN GET_PIN(B,4) // PB4

extern uint8_t ledRedState;
extern uint8_t ledGreenState;

#ifdef __cplusplus
}
#endif

#endif /* MYDRIVERS_LED_LED_H_ */
