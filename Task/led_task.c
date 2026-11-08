//
// Created by LK on 2026/11/7.
//

#include "led_task.h"
#include "main.h"
#include "cmsis_os2.h"
void StartLED_Task(void *argument) {
    for (;;) {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        osDelay(500);
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        osDelay(500);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
        osDelay(500);
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
    }
}
