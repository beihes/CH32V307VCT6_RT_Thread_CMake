/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */

#include "board.h"
#include <stdint.h>
#include "drv_usart.h"
#include <rthw.h>
#include <rtthread.h>

extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    NVIC_SetPriority(SysTicK_IRQn, 0x80);
    NVIC_SetPriority(Software_IRQn, 0xc0);
    NVIC_EnableIRQ(SysTicK_IRQn);
    NVIC_EnableIRQ(Software_IRQn);
    SysTick->CTLR = 0;
    SysTick->SR = 0;
    SysTick->CNT = 0;
    SysTick->CMP = ticks - 1;
    SysTick->CTLR = 0xF;
    return 0;
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)

/* 最大堆大小开关*/
#define USING_MAX_HEAP_SIZE 1

#if (USING_MAX_HEAP_SIZE == 0)
#define RT_HEAP_SIZE (4096)
static uint32_t rt_heap[RT_HEAP_SIZE];
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#else
RT_WEAK void *rt_heap_begin_get(void)
{
    return HEAP_BEGIN;
}
RT_WEAK void *rt_heap_end_get(void)
{
    return HEAP_END;
}
#endif /* END OF  USING_MAX_HEAP_SIZE*/
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Tick Configuration */
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

int reboot(void)
{
    NVIC_SystemReset();
    return 0;
}
FINSH_FUNCTION_EXPORT(reboot, reboot the board);
MSH_CMD_EXPORT(reboot, reboot the board);

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();
    SysTick->SR = 0;
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
