

#include "epd4in2.h"

int32_t EPD_Init(void) {
	reset_pin = RST_PIN;
	dc_pin = DC_PIN;
	cs_pin = CS_PIN;
	busy_pin = BUSY_PIN;
	width = EPD_WIDTH;
	height = EPD_HEIGHT;

    EPD_Reset();
    EPD_SendCommand(BOOSTER_SOFT_START);  //boost soft start
    EPD_SendData(0x17); //A
    EPD_SendData(0x17); //B
    EPD_SendData(0x17); //C
    EPD_SendCommand(POWER_ON);  //POWER ON
    EPD_WaitUntilIdle();
    EPD_SendCommand(PANEL_SETTING); //panel setting
    EPD_SendData(0xdf);    //LUT from OTP £¬160x296
    EPD_SendData(0x0b);

    EPD_SendCommand(RESOLUTION_SETTING);
    EPD_SendData(0x68);     // width: 104
    EPD_SendData(0x00);
    EPD_SendData(0xD4);     // height: 212

    EPD_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    EPD_SendData(0x97);
    return 0;
}

void EPD_SendCommand(uint8_t command) {
    DigitalWrite(EINC_Base_DC, dc_pin, LOW);
    SpiTransfer(Init_DefaultSPI, command);
}

void EPD_SendData(uint8_t data) {
    DigitalWrite(EINC_Base_DC, dc_pin, HIGH);
    SpiTransfer(Init_DefaultSPI, data);
}

void EPD_WaitUntilIdle(void) {
    EPD_SendCommand(GET_STATUS);
    while(DigitalRead(EINC_Base_BUSY, busy_pin) == 0) {      //0: busy, 1: idle
        DelayMs(100);
    }      
}

void EPD_Reset(void) {
    DigitalWrite(EINC_Base_RES, reset_pin, LOW);                //module reset
    DelayMs(200);
    DigitalWrite(EINC_Base_RES, reset_pin, HIGH);
    DelayMs(200);    
}

void EPD_SetLut(void) {
    uint32_t count;
    EPD_SendCommand(LUT_FOR_VCOM);                            //vcom
    for(count = 0; count < 44; count++) {
        EPD_SendData(lut_vcom0[count]);
    }
    
    EPD_SendCommand(LUT_WHITE_TO_WHITE);                      //ww --
    for(count = 0; count < 42; count++) {
        EPD_SendData(lut_ww[count]);
    }   
    
    EPD_SendCommand(LUT_BLACK_TO_WHITE);                      //bw r
    for(count = 0; count < 42; count++) {
        EPD_SendData(lut_bw[count]);
    } 

    EPD_SendCommand(LUT_WHITE_TO_BLACK);                      //wb w
    for(count = 0; count < 42; count++) {
        EPD_SendData(lut_bb[count]);
    } 

    EPD_SendCommand(LUT_BLACK_TO_BLACK);                      //bb b
    for(count = 0; count < 42; count++) {
        EPD_SendData(lut_wb[count]);
    } 
}

void EPD_DisplayFrame(const uint8_t* frame_buffer) {
    EPD_SendCommand(RESOLUTION_SETTING);
    //EPD_SendData(width >> 8);
    EPD_SendData(width & 0xff);
    EPD_SendData(height >> 8);
    EPD_SendData(height & 0xff);

    //EPD_SendCommand(VCM_DC_SETTING);
    //EPD_SendData(0x12);

    EPD_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    EPD_SendCommand(0x97);    //VBDF 17|D7 VBDW 97  VBDB 57  VBDF F7  VBDW 77  VBDB 37  VBDR B7

    if (frame_buffer != NULL) {
        EPD_SendCommand(DATA_START_TRANSMISSION_1);
        for(int i = 0; i < width * height / 8; i++) {
            EPD_SendData(0xFF);      // bit set: white, bit reset: black
        }
        DelayMs(2);
        EPD_SendCommand(DATA_START_TRANSMISSION_2);
        for(int i = 0; i < width * height / 8; i++) {
            EPD_SendData(frame_buffer[i]);
        }  
        DelayMs(2);                  
    }

    EPD_SetLut();

    EPD_SendCommand(DISPLAY_REFRESH);
    DelayMs(100);
    EPD_WaitUntilIdle();

}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Reset() to awaken or Epd::Init() to initialize
 */
void EPD_Sleep() {
    EPD_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    EPD_SendCommand(0xf7);    //VBDF 17|D7 VBDW 97  VBDB 57  VBDF F7  VBDW 77  VBDB 37  VBDR B7
                   
    EPD_SendCommand(POWER_OFF);          //power off
    EPD_WaitUntilIdle();
    EPD_SendCommand(DEEP_SLEEP);         //deep sleep
    EPD_SendData(0xA5);
}

const uint8_t lut_vcom0[] =
{
0x00, 0x17, 0x00, 0x00, 0x00, 0x02,        
0x00, 0x17, 0x17, 0x00, 0x00, 0x02,        
0x00, 0x0A, 0x01, 0x00, 0x00, 0x01,        
0x00, 0x0E, 0x0E, 0x00, 0x00, 0x02,        
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,        
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,        
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
const uint8_t lut_ww[] ={
0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x40, 0x0A, 0x01, 0x00, 0x00, 0x01,
0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
const uint8_t lut_bw[] ={
0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x40, 0x0A, 0x01, 0x00, 0x00, 0x01,
0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      
};

const uint8_t lut_bb[] ={
0x80, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x80, 0x0A, 0x01, 0x00, 0x00, 0x01,
0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             
};

const uint8_t lut_wb[] ={
0x80, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x80, 0x0A, 0x01, 0x00, 0x00, 0x01,
0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            
};


void EPD_Init_4gray(void) {

	EPD_Reset();

    EPD_SendCommand(POWER_SETTING);
    EPD_SendData(0x03);
    EPD_SendData(0x00);
    EPD_SendData(0x2b);
    EPD_SendData(0x2b);
    EPD_SendData(0x13);
    EPD_SendCommand(BOOSTER_SOFT_START);
    EPD_SendData(0x17);
    EPD_SendData(0x17);
    EPD_SendData(0x17);

    EPD_SendCommand(POWER_ON);
    EPD_WaitUntilIdle();
    EPD_SendCommand(PANEL_SETTING);
    EPD_SendData(0x3F);
    EPD_SendCommand(PLL_CONTROL);
    EPD_SendData(0x3c);

    EPD_SendCommand(RESOLUTION_SETTING);
    EPD_SendData(0x68);     // width: 104
    EPD_SendData(0x00);
    EPD_SendData(0xD4);     // height: 212

    EPD_SendCommand(VCM_DC_SETTING);
    EPD_SendData(0x12);
    EPD_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    EPD_SendData(0x97);


    /* EPD hardware init end */
    //return 0;
}

//4 grayscale demo function
/********Color display description
      white  gray1  gray2  black
0x10|  01     01     00     00
0x13|  01     00     01     00
                                   ****************/
void EPD_pic_display_4bit(const uint8_t* frame_buffer_black)
{
  int32_t i,j;
	int temp1,temp2,temp3;

	  //old  data
		EPD_SendCommand(0x10);

		for(i=0;i<2756;i++)	               //2756*4  212*104
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = frame_buffer_black[i*4+j];
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)
					temp3 |= 0x01;//white
				else if(temp2 == 0x00)
					temp3 |= 0x00;  //black
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x01;  //gray1
				else 
					temp3 |= 0x00; //gray2
				temp3 <<= 1;	
				temp1 <<= 4;
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)  //white
					temp3 |= 0x01;
				else if(temp2 == 0x00) //black
					temp3 |= 0x00;
				else if((temp2>0xA0)&&(temp2<0xF0))
					temp3 |= 0x01; //gray1
				else    
						temp3 |= 0x00;	//gray2	
        if(j!=3)					
			  temp3 <<= 1;	
				
			
		 }	
       	EPD_SendData(temp3);
		}
    //new  data
		EPD_SendCommand(0x13);

		for(i=0;i<2756;i++)	               //2756*4   212*104
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = frame_buffer_black[i*4+j];
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)
					temp3 |= 0x01;//white
				else if(temp2 == 0x00)
					temp3 |= 0x00;  //black
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x00;  //gray1
				else 
					temp3 |= 0x01; //gray2
				temp3 <<= 1;	
				temp1 <<= 4;
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)  //white
					temp3 |= 0x01;
				else if(temp2 == 0x00) //black
					temp3 |= 0x00;
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x00;//gray1
				else    
						temp3 |= 0x01;	//gray2
        if(j!=3)				
			  temp3 <<= 1;				
			
		 }	
       	EPD_SendData(temp3);
		}
}

//4 gray
const uint8_t lut_vcom11[] =
{
0x00	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x60	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
0x00	,0x13	,0x0A	,0x01	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00
				
};
//R21
const uint8_t lut_ww11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x10	,0x14	,0x0A	,0x00	,0x00	,0x01,
0xA0	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R22H	r
const uint8_t lut_bw11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0C	,0x01	,0x03	,0x04	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R23H	w
const uint8_t lut_wb11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0B	,0x04	,0x04	,0x01	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R24H	b
const uint8_t lut_bb11[] ={
0x80	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x20	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x50	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};

//LUT download
void EPD_lut11(void)
{
	uint32_t count;
	{
		EPD_SendCommand(0x20);							//vcom
		for(count=0;count<44;count++)
			{EPD_SendData(lut_vcom11[count]);}
		
		EPD_SendCommand(0x21);							//red not use
		for(count=0;count<42;count++)
			{EPD_SendData(lut_ww11[count]);}

		EPD_SendCommand(0x22);							//bw r
		for(count=0;count<42;count++)
			{EPD_SendData(lut_bw11[count]);}

		EPD_SendCommand(0x23);							//wb w
		for(count=0;count<42;count++)
			{EPD_SendData(lut_wb11[count]);}

		EPD_SendCommand(0x24);							//bb b
		for(count=0;count<42;count++)
			{EPD_SendData(lut_bb11[count]);}

		EPD_SendCommand(0x25);							//vcom
		for(count=0;count<42;count++)
			{EPD_SendData(lut_ww11[count]);}
	}	         
}

void EPD_DisplayFrame_4gray(const uint8_t* frame_buffer_black)
{
    EPD_Init_4gray();
    EPD_pic_display_4bit(frame_buffer_black); //picture
    EPD_lut11(); //Power settings
    EPD_SendCommand(DISPLAY_REFRESH);
    EPD_WaitUntilIdle();

    
}


/* END OF FILE */


