/*
 * usr_general.h
 *
 *  Created on: August 9, 2023
 *      Author: ERENACAREL
 */

#ifndef __USR_GENERAL_H
#define __USR_GENERAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
#include <math.h>

#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define _io  static
#define _iov static volatile

#include "usr_rgb_led.h"
#include "usr_system.h"

#endif // !_USR_GENERAL_H
