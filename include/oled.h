#ifdef _OLED

#ifndef _OLED_H
#define _OLED_H

#ifdef _HELTEC
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#endif

#ifdef _DEVKITC
#define OLED_SDA 21
#define OLED_SCL 22
#endif

namespace oled
{
    void init();
    void update();
}

#endif
#endif
