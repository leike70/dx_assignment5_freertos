#include "rc.h"
#include "main.h"
#include "usart.h"
#include "dma.h"
#include "cmsis_os2.h"

extern DMA_HandleTypeDef hdma_usart3_rx;

RC_Ctrl_t rc = {0};
uint8_t   dbus_buf[18];
uint8_t is_online=0;
void RC_Init(void)
{
    HAL_UART_Abort(&huart3);
    __HAL_DMA_SET_COUNTER(&hdma_usart3_rx, RC_FRAME_LEN);
    HAL_UART_Receive_DMA(&huart3, dbus_buf, RC_FRAME_LEN);
    __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);
    rc.last_update_ms = HAL_GetTick()-40;

}
void RC_Update(void)
{
       if (HAL_GetTick()-rc.last_update_ms >= 42) {
           is_online = 0;
       }
    else {
        is_online = 1;
    }
}

static void RC_Decode(void)
{
    rc.ch[0] = (dbus_buf[0] | (dbus_buf[1] << 8)) & 0x07FF;
    rc.ch[1] = ((dbus_buf[1] >> 3) | (dbus_buf[2] << 5)) & 0x07FF;
    rc.ch[2] = ((dbus_buf[2] >> 6) | (dbus_buf[3] << 2) | (dbus_buf[4] << 10)) & 0x07FF;
    rc.ch[3] = ((dbus_buf[4] >> 1) | (dbus_buf[5] << 7)) & 0x07FF;

    rc.s1  = (dbus_buf[5] >> 6) & 0x03;
    rc.s2  = (dbus_buf[5] >> 4) & 0x03;

}

void RC_IDLE_Handler(void)
{
    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) == RESET)
        return;

    __HAL_UART_CLEAR_IDLEFLAG(&huart3);

    HAL_UART_DMAStop(&huart3);

    uint16_t len = RC_FRAME_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
    if (len == RC_FRAME_LEN)
    {
        RC_Decode();
        rc.last_update_ms = HAL_GetTick();
        rc.frame_cnt++;
    }
    __HAL_DMA_SET_COUNTER(&hdma_usart3_rx, RC_FRAME_LEN);
    HAL_UART_Receive_DMA(&huart3, dbus_buf, RC_FRAME_LEN);
}

void StartRC(void *argument)
{
    /* USER CODE BEGIN StartRC */
    /* Infinite loop */
    for(;;)
    {
        RC_Update();
        osDelay(5);
    }
    /* USER CODE END StartRC */
}