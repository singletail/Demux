#ifdef _WIFI

#ifndef _NTP_H
#define _NTP_H

namespace ntp
{

    void NTP_Init(int16_t offset);
    void NTP_Status();
    void NTP_GetValues();

    char *NTP_TimeString();
    char *NTP_TimeString_Full();

    char *NTP_TimeString_Builtin();

    char *NTP_TimeString_Day();
    char *NTP_TimeString_Hours();
    char *NTP_TimeString_Minutes();
    char *NTP_TimeString_Seconds();

    unsigned long NTP_epoch();
    char *NTP_Get_Day(uint8_t daynum);
    bool NTP_isRunning();

    uint16_t intTime();
    bool boolSec();
}

#endif
#endif
