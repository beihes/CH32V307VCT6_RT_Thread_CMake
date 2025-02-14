/*
 * led.c
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#include "led.h"
#include "rtdbg.h"

uint8_t ledRedState = 0;
uint8_t ledGreenState = 0;

/*********************************************************************
 * @fn      led
 *
 * @brief   Test using the driver interface to operate the I/O port
 *
 * @return  none
 */
int led(int argc, char *argv[])
{
    if (argc == 1)
    {
        rt_kprintf("(A,15)\tLED\tcmd:RED\n");
        rt_kprintf("(B,04)\tLED\tcmd:GREEN\n");
        rt_kprintf("example:\tled RED\n");
        return RT_EOK;
    }
    LOG_D("led_SP:%08lx\r\n", __get_SP());
    rt_base_t midPin = RT_NULL;
    if (rt_strcmp(argv[1], "RED") == RT_EOK)
    {
        rt_kprintf("RED\n");
        midPin = LED_PIN_RED;
    }
    else if (rt_strcmp(argv[1], "GREEN") == RT_EOK)
    {
        rt_kprintf("GREEN\n");
        midPin = LED_PIN_GREEN;
    }
    rt_pin_write(midPin, PIN_HIGH);
    if (rt_thread_mdelay(100) != RT_EOK)
    {
        return RT_ERROR;
    }
    rt_pin_write(midPin, PIN_LOW);
    if (rt_thread_mdelay(100) != RT_EOK)
    {
        return RT_ERROR;
    }
    rt_pin_write(midPin, ledGreenState);
    return RT_EOK;
}
MSH_CMD_EXPORT(led, led sample by using I / O drivers);

int Led_Init(void)
{
    rt_pin_mode(LED_PIN_RED, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_PIN_GREEN, PIN_MODE_OUTPUT);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(Led_Init);
