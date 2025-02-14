/*
 * SPI.h
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_SPI_H_
#define CMYLIB_INC_SPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch32v30x.h"

    typedef struct CH32SPI
    {
        SPI_InitTypeDef spiInitTypedef;
        SPI_TypeDef *spiTypedef;
        IRQn_Type irqnType;
    } CH32SPI;

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_SPI_H_ */
