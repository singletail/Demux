#ifdef _BUZZER
#include "main.h"

#define PIN_BUZZER 32

namespace buzzer
{

    void init()
    {
        pinMode(PIN_BUZZER, OUTPUT);
    }

    void on()
    {
        analogWrite(PIN_BUZZER, 255);
    }

    void off()
    {
        analogWrite(PIN_BUZZER, 0);
    }
}

#endif