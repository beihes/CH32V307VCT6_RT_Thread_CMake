/*
 * define.h
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_DEFINE_H_
#define CMYLIB_INC_DEFINE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch32v30x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <rtthread.h>
#include "drivers/pin.h"
#include "msh.h"
#include "drv_gpio.h"

typedef struct CmdData
{
    const uint8_t* buffer;
    uint8_t num;
}CmdData;

typedef enum CmdBufferData
{
    REBOOT,CLEAR,
}CmdBufferData;

extern CmdData cmdVector;

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_DEFINE_H_ */
