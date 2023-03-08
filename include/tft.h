#ifdef _TFT

#ifndef _TFT_H
#define _TFT_H

#include "TFT_eSPI.h"
#include "tft_pin_config.h"

#define LCD_MODULE_CMD_1

namespace tft
{
    void init();
    void sample();
}

#endif
#endif