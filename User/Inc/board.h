/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ch32v30x.h"

#define CH32V30X_PIN_NUMBERS 100

/* board configuration */
#define SRAM_SIZE 64
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

extern int _ebss, _heap_end;
#define HEAP_BEGIN ((void *)&_ebss)
#define HEAP_END ((void *)&_heap_end)

// extern volatile unsigned long  interrupter_sp_saver;
void rt_hw_board_init(void);



#endif /* __BOARD_H__ */
