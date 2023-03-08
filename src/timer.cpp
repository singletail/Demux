#include "main.h"

namespace timer
{
    uint32_t _start = 0;
    uint32_t _counter = 0;

    uint32_t _last = 0;
    uint32_t _interval = 1000;

    void init()
    {
        _start = millis();
        _last = millis();
    }

    void check()
    {
        if (millis() >= (_last + _interval))
        {
            _counter++;
            _last = millis();
            tick();
        }
    }

    uint32_t count()
    {
        return _counter;
    }
}