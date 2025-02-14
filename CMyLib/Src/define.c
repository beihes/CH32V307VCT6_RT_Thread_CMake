/*
 * define.c
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#include "define.h"

const uint8_t cmdBuffer[][16]=
{
    "reboot","clear",""
};

CmdData cmdVector={cmdBuffer[0],sizeof(cmdBuffer)/sizeof(cmdBuffer[0])};
