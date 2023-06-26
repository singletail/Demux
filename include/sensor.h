#ifdef _SENSOR

#ifndef _SENSOR_H
#define _SENSOR_H

namespace sensor
{
    void _init();
    signed int num(std::string n);
    bool set(std::string n, double val);
    signed long _get(std::string n);
    bool _send_discovery();
    bool _send_report();
    void loop();

}

#endif
#endif
