/*
 * key.c
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#include "key.h"

// static struct rt_device keyPB03Device=
// {
//     .device_id=1
// };
KeyData keyPB03 = {0};

static void KeyPB03_Irq_callback(void *args)
{
    char *str = args;
    keyPB03.num++;
    if (keyPB03.num == 0xFF)
    {
        keyPB03.num = 0;
    }
    (keyPB03.state) ? (keyPB03.state = 0) : (keyPB03.state = 1);
    keyPB03.startTime = rt_tick_get();
    while (rt_pin_read(KEY_PB03) == DISABLE)
    {
    }
    keyPB03.endTime = rt_tick_get();
    keyPB03.midTime = keyPB03.endTime - keyPB03.startTime;
    rt_kprintf("\nstartTime:%d\t%s\n", keyPB03.startTime, str);
}

/* irq线程入口函数 -------------------------------------------------------------------------*/
void KeyPB03_Irq_entry(void *parameter)
{
    /* 配置KEY0引脚为上拉输入 */
    rt_pin_mode(KEY_PB03, PIN_MODE_INPUT_PULLUP);

    /* 绑定中断回调函数，下降沿模式，回调函数参数为字符串"--By ZhengNian" */
    rt_pin_attach_irq(KEY_PB03, PIN_IRQ_MODE_FALLING, KeyPB03_Irq_callback, (void *)"--By BHS");

    /* 使能引脚中断 */
    rt_pin_irq_enable(KEY_PB03, PIN_IRQ_ENABLE);
}

//void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));