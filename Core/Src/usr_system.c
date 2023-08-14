/*
 * usr_system.c
 *
 *  Created on: August 9, 2023
 *      Author: ERENACAREL
 */

#include "usr_general.h"

uint8_t  m_count1 = 1;
uint16_t m_count2 = 254;

uint32_t g_button1PressedTimeCnt = 0;
uint32_t g_button2PressedTimeCnt = 0;

uint8_t g_button1PressedOkFlg1 = 0;
uint8_t g_button2PressedOkFlg2 = 0;

uint8_t g_pressedOccuredFlg1 = 0;
uint8_t g_pressedOccuredFlg2 = 0;

// _io S_INITIAL_VALUE m_sInitialParameter;
extern S_INITIAL_VALUE m_sInitialParameter;

void UsrSystemInitial(const S_INITIAL_VALUE *pInitial)
{
    m_sInitialParameter = *pInitial;

    HAL_GPIO_WritePin(m_sInitialParameter.pIs31InitialPort, m_sInitialParameter.is31Pin, GPIO_PIN_SET);

    UsrInit(m_sInitialParameter.m_freq, m_sInitialParameter.m_outCurrent);
    UsrSetRunMode();

    HAL_TIM_Base_Start_IT(m_sInitialParameter.htim);
}


void UsrSystemGeneral(void)
{
    if(g_button1PressedOkFlg1 == 1)
    {
        m_count1 = m_count1 + 1;
        if(m_count1 > 23)  // 15
        {
            m_count1 = 1;
        }
        g_button1PressedOkFlg1 = 0;
    }

    
    if(g_button2PressedOkFlg2 == 1)
    {
        m_count2 = m_count2 + 15;
        if(m_count2 > 255)
        {
            m_count2 = 0;
        }
        g_button2PressedOkFlg2 = 0;
    }

    
    if(m_count1 == 1)
    {
      for(uint8_t i = 0x01; i <= 0x24; i+=3)
      {
        if(m_count2 == 255)
        {
            UsrAllLEDFadeOnBlue(5);
            UsrAllLEDFadeOffBlue(5); 
            UsrAllLEDFadeOnBlue(5);
            UsrAllLEDFadeOffBlue(5); 
            m_count2 = 270; 
        }
        else if(m_count2 == 270)
        {
            UsrSetPWM(i, 255); 
        } 
        else
        {
            UsrSetPWM(i, m_count2);
        }
      }
      for(uint8_t i = 0x02; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }
      for(uint8_t i = 0x03; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }      
      UsrPWMUpdate();
    }

    
    else if(m_count1 == 2)
    {
      for(uint8_t i = 0x01; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }
      for(uint8_t i = 0x02; i <= 0x24; i+=3)
      {
        if(m_count2 == 255)
        {
            UsrAllLEDFadeOnGreen(5);
            UsrAllLEDFadeOffGreen(5);  
            UsrAllLEDFadeOnGreen(5);
            UsrAllLEDFadeOffGreen(5);            
            m_count2 = 270;        
        }
        else if(m_count2 == 270)
        {
          UsrSetPWM(i, 255); 
        }     
        else
        {
          UsrSetPWM(i, m_count2);
        }
      }
      for(uint8_t i = 0x03; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }
      UsrPWMUpdate();
    }


    else if(m_count1 == 3)
    {
      for(uint8_t i = 0x01; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }
      for(uint8_t i = 0x02; i <= 0x24; i+=3)
      {
        UsrSetPWM(i, 0);
      }
      for(uint8_t i = 0x03; i <= 0x24; i+=3)
      {
        if(m_count2 == 255)
        {
            UsrAllLEDFadeOnRed(5);
            UsrAllLEDFadeOffRed(5);  
            UsrAllLEDFadeOnRed(5);
            UsrAllLEDFadeOffRed(5);            
            m_count2 = 270;        
        }
        else if(m_count2 == 270)
        {
          UsrSetPWM(i, 255); 
        } 
        else
        {
          UsrSetPWM(i, m_count2);
        }  
      }
      UsrPWMUpdate();
    }


    else if(m_count1 == 4)
    {
        for(uint8_t i = 0x01; i <= 0x24; i+=3)
        {
            UsrSetPWM(i, 0);
        }

        for(uint8_t i = 0x02; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnBrown(5);
                UsrAllLEDFadeOffBrown(5);
                UsrAllLEDFadeOnBrown(5);
                UsrAllLEDFadeOffBrown(5);                
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }    
            else
            {
                UsrSetPWM(i, m_count2);
            }        
        }

        for(uint8_t i = 0x03; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnBrown(5);
                UsrAllLEDFadeOffBrown(5);
                UsrAllLEDFadeOnBrown(5);
                UsrAllLEDFadeOffBrown(5);                
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
        }
        UsrPWMUpdate();
    }


    else if(m_count1 == 5)
    {
        for(uint8_t i = 0x01; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnCyan(5);
                UsrAllLEDFadeOffCyan(5);
                UsrAllLEDFadeOnCyan(5);
                UsrAllLEDFadeOffCyan(5);               
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }  
            else
            {
                UsrSetPWM(i, m_count2);
            }          
        }

        for(uint8_t i = 0x02; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnCyan(5);
                UsrAllLEDFadeOffCyan(5);
                UsrAllLEDFadeOnCyan(5);
                UsrAllLEDFadeOffCyan(5);               
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }          
            else
            {
                UsrSetPWM(i, m_count2);
            }  
        }

        for(uint8_t i = 0x03; i <= 0x24; i+=3)
        {
            UsrSetPWM(i, 0);
        }
        UsrPWMUpdate();
    }


    else if(m_count1 == 6)
    {
        for(uint8_t i = 0x01; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnPurple(5);
                UsrAllLEDFadeOffPurple(5);
                UsrAllLEDFadeOnPurple(5);
                UsrAllLEDFadeOffPurple(5);              
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }  
            else
            {
                UsrSetPWM(i, m_count2);
            }          
        }

        for(uint8_t i = 0x02; i <= 0x24; i+=3)
        {
            UsrSetPWM(i, 0); 
        }

        for(uint8_t i = 0x03; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnPurple(5);
                UsrAllLEDFadeOffPurple(5);
                UsrAllLEDFadeOnPurple(5);
                UsrAllLEDFadeOffPurple(5);              
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }  
            else
            {
                UsrSetPWM(i, m_count2);
            }
        }
        UsrPWMUpdate();
    }


    else if(m_count1 == 7)
    {
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnWhite(5);
                UsrAllLEDFadeOffWhite(5);
                UsrAllLEDFadeOnWhite(5);
                UsrAllLEDFadeOffWhite(5);
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
        }
        UsrPWMUpdate();
    }


    else if(m_count1 == 8)
    {
        uint32_t currentMillis = HAL_GetTick();
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            UsrSetPWM(i, 0);
            UsrPWMUpdate();
        }
        
        for(uint8_t i = 0x03; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnRed(5);
                UsrAllLEDFadeOffRed(5);
                UsrAllLEDFadeOnRed(5);
                UsrAllLEDFadeOffRed(5);
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
            UsrPWMUpdate();

            while((HAL_GetTick() - currentMillis) < 50)
            {}
        }
    }


    else if(m_count1 == 9)
    {
        uint32_t currentMillis = HAL_GetTick();
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            UsrSetPWM(i, 0);
            UsrPWMUpdate();
        }
        
        for(uint8_t i = 0x01; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnBlue(5);
                UsrAllLEDFadeOffBlue(5);
                UsrAllLEDFadeOnBlue(5);
                UsrAllLEDFadeOffBlue(5);
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
            UsrPWMUpdate();

            while((HAL_GetTick() - currentMillis) < 50)
            {}
        }
    }


    else if(m_count1 == 10)
    {
        uint32_t currentMillis = HAL_GetTick();
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            UsrSetPWM(i, 0);
            UsrPWMUpdate();
        }
        
        for(uint8_t i = 0x02; i <= 0x24; i+=3)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnGreen(5);
                UsrAllLEDFadeOffGreen(5);
                UsrAllLEDFadeOnGreen(5);
                UsrAllLEDFadeOffGreen(5);
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
            UsrPWMUpdate();

            while((HAL_GetTick() - currentMillis) < 50)
            {}
        }
    }


    else if(m_count1 == 11)
    {
        uint32_t currentMillis = HAL_GetTick();
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            UsrSetPWM(i, 0);
            UsrPWMUpdate();
        }
        
        for(uint8_t i = 0x01; i <= 0x24; i++)
        {
            if(m_count2 == 255)
            {
                UsrAllLEDFadeOnWhite(5);
                UsrAllLEDFadeOffWhite(5);
                UsrAllLEDFadeOnWhite(5);
                UsrAllLEDFadeOffWhite(5);
                m_count2 = 270;
            }
            else if(m_count2 == 270)
            {
                UsrSetPWM(i, 255);
            }
            else
            {
                UsrSetPWM(i, m_count2);
            }
            UsrPWMUpdate();

            while((HAL_GetTick() - currentMillis) < 50)
            {}
        }
    }


    else if(m_count1 == 12)
    {
        UsrAllLEDFadeOnRed(2);
        UsrAllLEDFadeOffRed(2); 
        UsrAllLEDFadeOnBlue(2);
        UsrAllLEDFadeOffBlue(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
    }


    else if(m_count1 == 13)
    {
        UsrAllLEDRainbowMode2(5);
    }


    else if(m_count1 == 14)
    {
        UsrAllLEDFadeOnBlue(2);
        UsrAllLEDFadeOffBlue(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
        UsrAllLEDFadeOnRed(2);
        UsrAllLEDFadeOffRed(2);      
    }


    else if(m_count1 == 15)
    {
        UsrAllLEDRainbowMode5(5);
    }


    else if(m_count1 == 16)
    {
        UsrAllLEDFadeOnCyan(2);
        UsrAllLEDFadeOffCyan(2); 
        UsrAllLEDFadeOnRed(2);
        UsrAllLEDFadeOffRed(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
    }


    else if(m_count1 == 17)
    {
        UsrAllLEDRainbowMode3(5);
    }


    else if(m_count1 == 18)
    {
        UsrAllLEDFadeOnRed(2);
        UsrAllLEDFadeOffRed(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
        UsrAllLEDFadeOnPurple(2);
        UsrAllLEDFadeOffPurple(2);      
    }


    else if(m_count1 == 19)
    {
        UsrAllLEDRainbowMode4(5);
    }
    

    else if(m_count1 == 20)
    {
        UsrAllLEDFadeOnBrown(2);
        UsrAllLEDFadeOffBrown(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
        UsrAllLEDFadeOnPurple(2);
        UsrAllLEDFadeOffPurple(2);      
    }


    else if(m_count1 == 21)
    {
        UsrAllLEDRainbowMode1(5);
    }


    else if(m_count1 == 22)
    {
        UsrAllLEDFadeOnWhite(2);
        UsrAllLEDFadeOffWhite(2);
        UsrAllLEDFadeOnGreen(2);
        UsrAllLEDFadeOffGreen(2); 
        UsrAllLEDFadeOnBrown(2);
        UsrAllLEDFadeOffBrown(2);      
    }


    else if(m_count1 == 23)
    {
        UsrAllLEDRainbowMode6(5);
    }


    else
    {
        m_count1 = 1;
        m_count2 = 254;
    }


}

