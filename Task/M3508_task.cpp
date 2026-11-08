//
// Created by LK on 2026/11/7.
//

#include "M3508_task.h"
#include "DJI_motor_driver.h"
#include "main.h"


float target_pos;
uint32_t start;
uint32_t tick;
uint32_t next;
void StartM3508_Task(void *argument) {
    DJI_motor m3508(&hcan1,nullptr,1,DJI_M3508,0);
    m3508.motor_control(DJI_MOTOR_CLEAR_PID);
    start=osKernelGetTickCount();
    next=start;
    for (;;) {
        tick=osKernelGetTickCount()-start;
        target_pos=2*cosf(tick/1000.0f)-2;
        m3508.motor_set_rounds(target_pos);
        next+=5;
        osDelayUntil(next);
    }
}
