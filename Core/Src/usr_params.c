/*
 * usr_params.c
 *
 *  Created on: August 9, 2023
 *      Author: ERENACAREL
 */
#include "usr_general.h"

S_INITIAL_VALUE m_sInitialParameter = {
    .htim                   = &htim2,
    .pUart                  = &huart1,
    .hi2c                   = &hi2c1,

    .pIs31InitialPort       = GPIOC,
    .pButton1Port           = GPIOC,
    .pButton2Port           = GPIOC,

    .is31Pin                = GPIO_PIN_7,
    .button1Pin             = GPIO_PIN_0,
    .button2Pin             = GPIO_PIN_1,

    .m_freq                 = 22,          // set PWM frequency, either 3 kHz (default) or 22 kHz allowed
    .m_outCurrent           = 0x00,        // choices are 0x00 (IMax = 16 mA), 0x01 (IMax/2), 0x02 (IMax/3), and 0x03 (IMax/4)
  

};

