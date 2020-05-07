

#ifndef EPD4IN2_H
#define EPD4IN2_H

#include "epdif.h"
#include "init.h"

// Display resolution
#define EPD_WIDTH       104
#define EPD_HEIGHT      212

// EPD4IN2 commands
#define PANEL_SETTING                               0x00
#define POWER_SETTING                               0x01
#define POWER_OFF                                   0x02
#define POWER_OFF_SEQUENCE_SETTING                  0x03
#define POWER_ON                                    0x04
#define POWER_ON_MEASURE                            0x05
#define BOOSTER_SOFT_START                          0x06
#define DEEP_SLEEP                                  0x07
#define DATA_START_TRANSMISSION_1                   0x10
#define DATA_STOP                                   0x11
#define DISPLAY_REFRESH                             0x12
#define DATA_START_TRANSMISSION_2                   0x13
#define LUT_FOR_VCOM                                0x20 
#define LUT_WHITE_TO_WHITE                          0x21
#define LUT_BLACK_TO_WHITE                          0x22
#define LUT_WHITE_TO_BLACK                          0x23
#define LUT_BLACK_TO_BLACK                          0x24
#define PLL_CONTROL                                 0x30
#define TEMPERATURE_SENSOR_COMMAND                  0x40
#define TEMPERATURE_SENSOR_SELECTION                0x41
#define TEMPERATURE_SENSOR_WRITE                    0x42
#define TEMPERATURE_SENSOR_READ                     0x43
#define VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define LOW_POWER_DETECTION                         0x51
#define TCON_SETTING                                0x60
#define RESOLUTION_SETTING                          0x61
#define GSST_SETTING                                0x65
#define GET_STATUS                                  0x71
#define AUTO_MEASUREMENT_VCOM                       0x80
#define READ_VCOM_VALUE                             0x81
#define VCM_DC_SETTING                              0x82
#define PARTIAL_WINDOW                              0x90
#define PARTIAL_IN                                  0x91
#define PARTIAL_OUT                                 0x92
#define PROGRAM_MODE                                0xA0
#define ACTIVE_PROGRAMMING                          0xA1
#define READ_OTP                                    0xA2
#define POWER_SAVING                                0xE3
#include "stdlib.h"
#include "epdif.h"


extern const unsigned char lut_vcom0[];
extern const unsigned char lut_ww[];
extern const unsigned char lut_bw[];
extern const unsigned char lut_bb[];
extern const unsigned char lut_wb[];

int width;
int height;

int reset_pin;
int dc_pin;
int cs_pin;
int busy_pin;


int32_t EPD_Init(void);
void EPD_WaitUntilIdle(void);
void EPD_Reset(void);
void EPD_SetLut(void);
void EPD_DisplayFrame(const unsigned char* frame_buffer);
void EPD_SendCommand(unsigned char command);
void EPD_SendData(unsigned char data);
void EPD_Sleep(void);

void EPD_DisplayFrame_4gray(const unsigned char* frame_buffer_black);
void EPD_lut11(void);
void EPD_Init_4gray(void);
void EPD_pic_display_4bit(const unsigned char* frame_buffer_black);




#endif /* EPD4IN2_H */

/* END OF FILE */
