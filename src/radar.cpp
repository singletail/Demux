#ifdef _RADAR
#include "main.h"

#define PIN_RADAR 25

namespace radar
{
    bool current = false;
    bool status = false;
    char radar_status[16] = {'\0'};

    // float doppler_status = 0.0;

    void init()
    {
        pinMode(PIN_RADAR, INPUT);
    }

    void report()
    {
#ifdef _MQTT
        sensor::set("motion", status);
        sensor::set("uptime", (esp_timer_get_time() / 1000000));
        sensor::set("rssi", WiFi.RSSI());
#endif
    }

    void read()
    {
        current = digitalRead(PIN_RADAR);
        // Serial.print("radar read ");
        Serial.println(current);
        if (current != status)
        {
            status = current;
            report();
            if (status)
            {
                // led::on();
                // buzzer::on();
                // audio::play();
                Serial.println("Motion Detected.");
            }
            else
            {
                // led::off();
                // buzzer::off();
                Serial.println("Clear.");
            }
        }
    }

    const char *getStatus()
    {

        if (status)
        {
            sprintf(radar_status, "%s", "MOTION");
        }
        else
        {
            sprintf(radar_status, "%s", " ");
        }
        return radar_status;
    }

}

#endif