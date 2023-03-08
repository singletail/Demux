#ifdef _GAS
#include "main.h"

#define PIN_GAS 36

namespace gas
{

    void init()
    {
        pinMode(PIN_GAS, INPUT);
    }

    uint32_t read()
    {
        uint16_t gas_value_raw = analogRead(PIN_GAS);
        uint32_t gas_value_ppm = ppm(gas_value_raw);
        // Serial.print("Gas: ");
        // Serial.println(gas_value_ppm);
        return gas_value_ppm;
    }

    uint32_t ppm(uint16_t raw)
    {
        // analog reading range is 0-4095
        // sensor range is 200 - 10000 ppm
        uint32_t convertedValue = ((raw * 9800) / 4095) + 200;
        return convertedValue;
    }
}
#endif