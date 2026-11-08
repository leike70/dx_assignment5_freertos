
#ifndef RC_H
#define RC_H

#include "stdint.h"

#define RC_FRAME_LEN  18

typedef struct
{
    uint16_t ch[4];
    uint8_t  s1, s2;
    uint16_t frame_cnt;
    volatile uint32_t last_update_ms;
} RC_Ctrl_t;

extern RC_Ctrl_t rc;
extern uint8_t   dbus_buf[RC_FRAME_LEN];

void    RC_Init(void);
void    RC_IDLE_Handler(void);
void StartRC(void *argument);

#endif
