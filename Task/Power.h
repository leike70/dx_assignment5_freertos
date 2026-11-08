//
// Created by LK on 2026/11/7.
//
#ifndef DX_ASSIGNMENT5_FREERTOS_POWER_H
#define DX_ASSIGNMENT5_FREERTOS_POWER_H

#include "cmsis_os2.h"
#include "CAN_bsp.h"

extern volatile int16_t power_raw;
extern volatile int16_t energy_raw;

#ifdef __cplusplus
extern "C" {
#endif
void StartPower(void *argument);
#ifdef __cplusplus
}
#endif

#endif //DX_ASSIGNMENT5_FREERTOS_POWER_H
