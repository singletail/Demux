#ifdef _LED
#include "main.h"

#ifdef _HELTEC
#define PIN_EXT_LED 13
#endif

namespace led {

    bool led_status;

    void init()
    {
        pinMode(PIN_EXT_LED, OUTPUT);
        digitalWrite(PIN_EXT_LED, LOW);
        led_status = false;
    }

    void on()
    {
        if (led_status == false)
        {
            digitalWrite(PIN_EXT_LED, HIGH);
            led_status = true;
        }
    }

    void off()
    {
        if (led_status == true)
        {
            digitalWrite(PIN_EXT_LED, LOW);
            led_status = false;
        }
    }

}
#endif