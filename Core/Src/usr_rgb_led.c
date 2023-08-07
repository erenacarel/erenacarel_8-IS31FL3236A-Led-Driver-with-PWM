#include "usr_general.h"

#define _io static
#define _iov static volatile

#define DEVICE_ADDRESS      0x3C


extern uint8_t PWM_Gamma64[64];
extern uint8_t PWM_Bright64[64];
extern uint8_t PWM1[32];
extern uint8_t PWM2[40];
extern uint8_t PWM3[64];
extern uint16_t PWM_RGB[512];
extern uint16_t PWM5[288];


_io void UsrWriteI2CRegister(uint8_t DeviceAddress, uint8_t RegisterAddress, uint8_t data);


_io void UsrWriteI2CRegister(uint8_t DeviceAddress, uint8_t RegisterAddress, uint8_t data)
{ 
    HAL_I2C_Mem_Write(&hi2c1, (DeviceAddress << 1), RegisterAddress, 1, &data, 1, 10);
}


void UsrPowerDown(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_SD, 0x00);
}


void UsrReset(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_RESET, 0x00);
}


void UsrPowerUp(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_SD, 0x01);
}


void UsrInit(uint8_t freq, uint8_t outCurrent)
{
    for(uint8_t ii = 0x26; ii <= 0x49; ii++)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, ii, (outCurrent << 1) | 0x01);            // enable all leds
    } 

    for(uint8_t ii = 0x01; ii <= 0x24; ii++)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, ii, 0x00);                               // set PWM for all leds to 0
    }

    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_UPDATE, 0x00);
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_SD,     0x01);
}


void UsrSetPWM(uint8_t channel, uint8_t PWMLevel)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, channel, PWMLevel);
}


void UsrSetFreq(uint8_t freq)
{
    if(freq == 3)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_FREQ, 0x00);    // set PWM frequency to 3 kHz(default)
    }
    else if(freq == 22)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_FREQ, 0x01);   // set PWM frequency to 22 kHz
    }
    else{
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_FREQ, 0x00);   // set PWM frequency to 3 kHz (default)
    }
}


void UsrI2CScan(void)
{
    uint16_t i = 0, ret;
    uint8_t data[64] = {0};
    uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";

    HAL_UART_Transmit(&huart1, StartMSG, sizeof(StartMSG), 10000);
    for(i=1; i<128; i++)
    {
        ret = HAL_I2C_IsDeviceReady(&hi2c1, (i << 1), 2, 2);
        if(ret == HAL_OK)
        {
            // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
            sprintf((char*)data, "iste adres: 0x%X\n", i);
            HAL_UART_Transmit(&huart1, data, sizeof(data), 10000);
        }
    }
    HAL_UART_Transmit(&huart1, data, sprintf((char*)data, "islem bitmistir...\n"), 10000);    
}


void UsrSetRunMode(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_CTRL, 0x00);     // set device in normal run mode (default)
}


void UsrPWMUpdate(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_UPDATE, 0x00);   // update led array
}


void UsrSetStopMode(void)
{
    UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_CTRL, 0x01);
}


void UsrSetLEDOnOff(uint8_t channel, uint8_t OnOff)
{
    uint8_t data[64] = {0};

    if(OnOff == 0x00 || OnOff == 0x01)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, channel, OnOff);                                     // enable leds
    }
    else
    {
        HAL_UART_Transmit(&huart1, data, sprintf((char*)data, "Illegal LED OnOff value selected!\n"), 10000);
    }    
}



void UsrAllLEDFadeOnRed(uint8_t speed)
{
    for(uint8_t j=0; j<=63; j++)
    {
        for(uint8_t i=0x03; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);                    //set all PWM     PWM_Gamma64[j]
        }
        UsrPWMUpdate();
        HAL_Delay(speed);
    }
    HAL_Delay(500);
}


void UsrAllLEDFadeOffRed(uint8_t speed)         // fade speed in milliseconds
{
    for (uint8_t j=63; j>0; j--)                // all LED breath falling
    {
        for(uint8_t i=0x03; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);         //set all PWM       PWM_Gamma64[j]
        }
        UsrPWMUpdate();                          //update PWM & control registers
        HAL_Delay(speed); 
    } 
    HAL_Delay(500);                           //keep 0.5s
}


void UsrAllLEDFadeOnBlue(uint8_t speed)
{
    for(uint8_t j=0; j<=63; j++)
    {
        for(uint8_t i=0x01; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);          //set all PWM     PWM_Gamma64[j]
        }
        UsrPWMUpdate();
        HAL_Delay(speed);
    }
    HAL_Delay(500);
}


void UsrAllLEDFadeOffBlue(uint8_t speed)             // fade speed in milliseconds
{
    for (uint8_t j=63; j>0; j--)                     // all LED breath falling
    {
        for(uint8_t i=0x01; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);               //set all PWM       PWM_Gamma64[j]
        }
        UsrPWMUpdate();                                 //update PWM & control registers
        HAL_Delay(speed); 
    } 
    HAL_Delay(500); //keep 0.5s
}


void UsrAllLEDFadeOnGreen(uint8_t speed)
{
    for(uint8_t j=0; j<=63; j++)
    {
        for(uint8_t i=0x02; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);               //set all PWM     PWM_Gamma64[j]
        }
        UsrPWMUpdate();
        HAL_Delay(speed);
    }
    HAL_Delay(500);
}


void UsrAllLEDFadeOffGreen(uint8_t speed)            // fade speed in milliseconds
{
    for (uint8_t j=63; j>0; j--)                     // all LED breath falling
    {
        for(uint8_t i=0x02; i<=0x24; i+=3)
        {
            UsrSetPWM(i, PWM_Bright64[j]);               //set all PWM       PWM_Gamma64[j]
        }
        UsrPWMUpdate();                                 //update PWM & control registers
        HAL_Delay(speed); 
    } 
    HAL_Delay(500); //keep 0.5s
}



void UsrAllLEDRainbowMode1(uint8_t speed)
{
    for(uint8_t j=0; j<24; j++)  // 57
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM02, PWM1[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM03, PWM1[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM06, PWM1[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM07, PWM1[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM12, PWM1[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM13, PWM1[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM16, PWM1[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM17, PWM1[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM21, PWM1[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM22, PWM1[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM1[j+5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM1[j+5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM1[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM1[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM1[j+7]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM36, PWM1[j+7]);

        UsrPWMUpdate();

        HAL_Delay(speed);
    }
    
}
void UsrAllLEDRainbowMode2(uint8_t speed)
{
    for(uint8_t j=0; j<24; j++)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM02, PWM1[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM03, PWM1[j+7]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM06, PWM1[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM07, PWM1[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM12, PWM1[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM13, PWM1[j+5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM16, PWM1[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM17, PWM1[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM21, PWM1[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM22, PWM1[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM1[j+5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM1[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM1[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM1[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM1[j+7]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM36, PWM1[j]);

        UsrPWMUpdate();

        HAL_Delay(speed);
    }
}



void UsrAllLEDRainbowMode3(uint8_t speed)
{
    for(uint8_t j=0; j<255; j++) // 127
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM01,PWM5[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM02,PWM5[j]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM03,PWM5[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM05,PWM5[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM06,PWM5[j+4]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM04,PWM5[j+8]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM07,PWM5[j+8]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM12,PWM5[j+8]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM11,PWM5[j+8]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM13,PWM5[j+12]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM15,PWM5[j+12]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM16,PWM5[j+12]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM14,PWM5[j+16]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM17,PWM5[j+16]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM21,PWM5[j+16]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM20,PWM5[j+16]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM22,PWM5[j+20]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM24,PWM5[j+20]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM25,PWM5[j+20]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM23,PWM5[j+24]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM26,PWM5[j+24]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM30,PWM5[j+24]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM31,PWM5[j+24]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM32,PWM5[j+28]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM34,PWM5[j+28]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM35,PWM5[j+28]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM33,PWM5[j+32]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM36,PWM5[j+32]);

        UsrPWMUpdate();       

        HAL_Delay(speed);
    }
    
}


void UsrAllLEDRainbowMode4(uint8_t speed)
{

    for(uint8_t j=0; j<36; j++)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM02, PWM2[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM03, PWM2[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM06, PWM2[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM07, PWM2[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM12, PWM2[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM13, PWM2[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM16, PWM2[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM17, PWM2[j]);


        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM2[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM2[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM2[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM2[j+1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM2[j+3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM2[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM2[j+4]);        
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM36, PWM2[j+3]);
        
        UsrPWMUpdate();

        HAL_Delay(speed);
    }    
}



void UsrAllLEDRainbowMode5(uint8_t speed)
{
    for(uint8_t j=0; j<58; j++)
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM02, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM03, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM06, PWM3[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM07, PWM3[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM12, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM13, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM16, PWM3[j+4]);

        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM3[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM3[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+6]);     

        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM3[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM3[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+2]);       

        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM25, PWM3[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM26, PWM3[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM31, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM32, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j+6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS, IS31FL3236A_PWM35, PWM3[j]);             

        UsrPWMUpdate();

        HAL_Delay(speed);
    }    
}



void UsrAllLEDRainbowMode6(uint8_t speed)
{
    uint8_t x = 128;
    uint8_t y= 64;
    uint8_t z = 8;
    
    for(uint8_t i=0; i<196; i++)  // 127
    {
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM01,PWM_RGB[i]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM02,PWM_RGB[i+x]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM03,PWM_RGB[i+y]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM04,PWM_RGB[i+z*1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM05,PWM_RGB[i+x+z*1]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM06,PWM_RGB[i+y+z*1]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM07,PWM_RGB[i+z*2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM08,PWM_RGB[i+x+z*2]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM09,PWM_RGB[i+y+z*2]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM10,PWM_RGB[i+z*3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM11,PWM_RGB[i+x+z*3]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM12,PWM_RGB[i+y+z*3]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM13,PWM_RGB[i+z*4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM14,PWM_RGB[i+x+z*4]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM15,PWM_RGB[i+y+z*4]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM16,PWM_RGB[i+z*5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM17,PWM_RGB[i+x+z*5]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM18,PWM_RGB[i+z*5]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM19,PWM_RGB[i+x+z*5]);       
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM20,PWM_RGB[i+x+z*6]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM21,PWM_RGB[i+y+z*6]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM22,PWM_RGB[i+z*7]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM23,PWM_RGB[i+x+z*7]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM24,PWM_RGB[i+y+z*7]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM25,PWM_RGB[i+z*8]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM26,PWM_RGB[i+x+z*8]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM27,PWM_RGB[i+y+z*8]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM28,PWM_RGB[i+z*9]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM29,PWM_RGB[i+x+z*9]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM30,PWM_RGB[i+y+z*9]);

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM31,PWM_RGB[i+z*10]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM32,PWM_RGB[i+x+z*10]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM33,PWM_RGB[i+y+z*10]);     

        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM31,PWM_RGB[i+z*11]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM32,PWM_RGB[i+x+z*11]);
        UsrWriteI2CRegister(DEVICE_ADDRESS,IS31FL3236A_PWM33,PWM_RGB[i+y+z*11]);          

        UsrPWMUpdate();

        HAL_Delay(speed);
    }    
}