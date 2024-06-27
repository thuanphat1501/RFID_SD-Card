#ifndef __SD_CARD_H
#define __SD_CARD_H

#include "fatfs.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "uart.h"
#include <string.h>

void readFile(char* flename);
#endif