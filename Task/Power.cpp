//
// Created by LK on 2026/11/7.
//

#include "Power.h"


volatile int16_t power_raw  = 0;
volatile int16_t energy_raw = 0;

void power_rx_callback(can_device_receive *dev, uint8_t *data)
{
    power_raw  = (int16_t)(data[0] | (data[1] << 8));
    energy_raw = (int16_t)(data[2] | (data[3] << 8));
}

void StartPower(void *argument)
{
    can_device_receive powerrx(&hcan2, 0x31, power_rx_callback);
    for (;;) {
        osDelay(10);
    }
}
