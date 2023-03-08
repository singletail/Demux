#ifdef _SENSOR

#ifndef _SENSOR_H
#define _SENSOR_H

namespace sensor
{
    // -------------------------------------------------------//
    // -------------------------------------------------------//

    // Set each of these manually:
#ifdef _DEVKITC
    const char *device_name = "devkitc_v4_2";
#endif

#ifdef _HELTEC
    const char *device_name = "heltec_1";
#endif

#ifdef _BME
    const uint8_t numVars = 6;
    std::array<std::array<std::string, 3>, numVars> vars =
        {{{"temperature", "°F", "temperature"},
          {"pressure", "hPa", "pressure"},
          {"humidity", "%", "humidity"},
          {"altitude", "m", ""},
          {"uptime", "seconds", ""},
          {"rssi", "dBm", "signal_strength"}}};
#endif

#ifdef _RADAR
    const uint8_t numVars = 3;
    std::array<std::array<std::string, 3>, numVars> vars =
        {{{"motion", "", ""},
          {"uptime", "seconds", ""},
          {"rssi", "dBm", "signal_strength"}}};
#endif

    const unsigned long throttle = 10000; // milliseconds

    // -------------------------------------------------------//
    // -------------------------------------------------------//

    bool _initialized = false;
    bool _discoverySent = false;
    bool _newDataReady = false;
    unsigned long _lastReport = 0;

    uint16_t _last_report_size = 0;
    std::string _last_report_string = "";

    class Tracker
    {
    public:
        std::string name;
        std::string entity_id;
        std::string unique_id;
        std::string unit_of_measurement;
        std::string device_class;
        double value = 0;

        std::string friendly_name() { return unique_id + " " + name; }
        std::string state_topic() { return "home/sensor/" + unique_id + "/state"; }
        std::string discovery_topic() { return "home/sensor/" + unique_id + "/" + name + "/config"; }
        std::string value_template() { return "{{ value_json." + name + "|default(0) }}"; }

        std::string discovery_payload()
        {
            DynamicJsonDocument doc(1024);
            char buffer[1024];
            doc["name"] = friendly_name();
            doc["stat_t"] = state_topic();
            doc["frc_upd"] = true;
            doc["val_tpl"] = value_template();
            if (unit_of_measurement.length() > 0)
            {
                doc["unit_of_meas"] = unit_of_measurement;
            }
            if (device_class.length() > 0)
            {
                doc["device_class"] = device_class;
            }
            _last_report_size = serializeJson(doc, buffer);
            _last_report_string = buffer;

            return buffer;
        }
    };

    Tracker track[numVars];

    void _init()
    {
        for (int t = 0; t < numVars; t++)
        {
            track[t].unique_id = device_name;
            track[t].name = vars[t][0];
            track[t].unit_of_measurement = vars[t][1];
            track[t].device_class = vars[t][2];
        }
        Serial.println("sensor::init() done.");
    }

    signed int num(std::string n)
    {
        s8_t ret = -1;
        for (int i = 0; i < numVars; i++)
        {
            if (track[i].name == n)
            {
                ret = i;
            }
        }
        return ret;
    }

    bool set(std::string n, double val)
    {
        bool ret = false;
        u8_t tNum = num(n);
        if (tNum == -1)
        {
            Serial.print("ERROR: No var found: ");
            Serial.println(n.c_str());
        }
        else
        {
            track[tNum].value = val;
            _newDataReady = true;
            ret = true;
        }
        return ret;
    }

    signed long _get(std::string n)
    {
        s32_t ret = 0;
        u8_t tNum = num(n);
        if (tNum == -1)
        {
            Serial.print("ERROR: No var found: ");
            Serial.println(n.c_str());
        }
        else
        {
            ret = track[tNum].value;
        }
        return ret;
    }

    bool _send_discovery()
    {
        // only print/debug for now:
        bool ret = true;
        for (int i = 0; i < numVars; i++)
        {
            Serial.print("** var ");
            Serial.println(i);
            Serial.println(track[i].discovery_topic().c_str());
            Serial.println(track[i].discovery_payload().c_str());

            bool ok = mqtt::json(track[i].discovery_topic(), track[i].discovery_payload(), false);
            if (!ok)
            {
                ret = false;
            }
        }
        return ret;
    }

    bool _send_report()
    {
        // only print/debug for now:
        bool ret = false;

        DynamicJsonDocument doc(1024);
        char buffer[1024];
        for (int i = 0; i < numVars; i++)
        {
            doc[track[i].name] = track[i].value;
        }
        _last_report_size = serializeJson(doc, buffer);
        _last_report_string = buffer;

        Serial.print("** report ");
        Serial.println(track[0].state_topic().c_str());
        Serial.println(buffer);

        ret = mqtt::json(track[0].state_topic(), buffer, false);
        return ret;
    }

    void loop()
    {
        if (!_initialized)
        {
            _init();
            _initialized = true;
        }
        else if (!_discoverySent)
        {
            if (mqtt::isConnected())
            {
                bool ok = _send_discovery();
                if (ok)
                {
                    _discoverySent = true;
                    Serial.println("sensor::_send_discovery()");
                }
            }
        }
        else if (_newDataReady)
        {
            if (mqtt::isConnected())
            {
                if (millis() > (_lastReport + throttle))
                {
                    bool ok = _send_report();
                    if (ok)
                    {
                        _newDataReady = false;
                        Serial.println("sensor::_send_report()");
                    }
                    _lastReport = millis();
                }
            }
        }
    }

}

#endif
#endif
