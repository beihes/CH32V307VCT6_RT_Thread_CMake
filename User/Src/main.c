/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "ch32v30x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"
#include <board.h>
#include "myDrivers.h"
#include "app.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    rt_kprintf("MCU: CH32V307VCT6\n");
	rt_kprintf("SysClk: %dHz\n",SystemCoreClock);
    rt_kprintf("www.wch.cn\n");
	// rt_pin_write(LED_PIN_RED, PIN_LOW);
    RT_Thread_Init();
	while(1)
	{
	    // rt_pin_write(LED_PIN_RED, PIN_HIGH);
	    rt_thread_mdelay(5000);
	    // rt_pin_write(LED_PIN_RED, PIN_LOW);
	    rt_thread_mdelay(5000);
	}
}



