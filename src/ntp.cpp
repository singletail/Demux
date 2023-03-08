#ifdef _WIFI
#include "main.h"

#define DEBUG_NTPClient 1
#define NTP_UPDATE_TIME 3600

namespace ntp
{

    bool NTP_Ready = false;
    const char *ntp_server = "pool.ntp.org";
    char ntp_return[16] = {'\0'};
    char ntp_ft_c[16];

    uint8_t ntp_d = 0;
    uint8_t ntp_h = 0;
    uint8_t ntp_m = 0;
    uint8_t ntp_s = 0;

    char ntp_d_char[8] = {'\0'};
    char ntp_h_char[8] = {'\0'};
    char ntp_m_char[8] = {'\0'};
    char ntp_s_char[8] = {'\0'};

    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, ntp_server, 0, NTP_UPDATE_TIME);

    void NTP_Init(int16_t offset)
    {
        timeClient.setTimeOffset(offset);

        timeClient.begin();
        NTP_Ready = true;
        timeClient.forceUpdate();
    }

    void NTP_Status()
    {
        if (NTP_Ready != true)
        {
            Serial.println("NTP_Init()");
            NTP_Init(geo::getOffset());
        }
    }

    void NTP_GetValues()
    {
        ntp_d = timeClient.getDay();
        ntp_h = timeClient.getHours();
        ntp_m = timeClient.getMinutes();
        ntp_s = timeClient.getSeconds();

        NTP_Get_Day(ntp_d);

        if (ntp_h > 12)
        {
            ntp_h = ntp_h - 12;
        }
        if (ntp_h < 10)
        {
            sprintf(ntp_h_char, " %i", ntp_h);
        }
        else
        {
            sprintf(ntp_h_char, "%i", ntp_h);
        }

        sprintf(ntp_m_char, "%02i", ntp_m);
        sprintf(ntp_s_char, "%02i", ntp_s);
    }

    char *NTP_TimeString()
    {
        NTP_Status();
        NTP_GetValues();

        sprintf(ntp_return, "%s", "--:--:--");
        if (NTP_Ready == true)
        {
            sprintf(ntp_return, "%s:%s:%s", ntp_h_char, ntp_m_char, ntp_s_char);
        }
        return ntp_return;
    }

    char *NTP_TimeString_Full()
    {
        NTP_Status();
        NTP_GetValues();

        sprintf(ntp_return, "%s", "---- --:--:--");
        if (NTP_Ready == true)
        {
            sprintf(ntp_return, "%s %s:%s:%s", ntp_d_char, ntp_h_char, ntp_m_char, ntp_s_char);
        }
        return ntp_return;
    }

    char *NTP_TimeString_Builtin()
    {
        String ntp_ft = timeClient.getFormattedTime();
        sprintf(ntp_ft_c, "%s", ntp_ft.c_str());
        return ntp_ft_c;
    }

    char *NTP_TimeString_Day()
    {
        return ntp_d_char;
    }

    char *NTP_TimeString_Hours()
    {
        return ntp_h_char;
    }

    char *NTP_TimeString_Minutes()
    {
        return ntp_m_char;
    }

    char *NTP_TimeString_Seconds()
    {
        return ntp_s_char;
    }

    bool NTP_isRunning()
    {
        return NTP_Ready;
    }

    unsigned long NTP_epoch()
    {
        return timeClient.getEpochTime();
    }

    char *NTP_Get_Day(uint8_t daynum)
    {
        switch (daynum)
        {
        case 0:
            sprintf(ntp_d_char, "%s", "Sun");
            break;
        case 1:
            sprintf(ntp_d_char, "%s", "Mon");
            break;
        case 2:
            sprintf(ntp_d_char, "%s", "Tues");
            break;
        case 3:
            sprintf(ntp_d_char, "%s", "Wed");
            break;
        case 4:
            sprintf(ntp_d_char, "%s", "Thurs");
            break;
        case 5:
            sprintf(ntp_d_char, "%s", "Fri");
            break;
        case 6:
            sprintf(ntp_d_char, "%s", "Sat");
            break;
        default:
            sprintf(ntp_d_char, "%s", "Lost");
        }
        return ntp_d_char;
    }

    uint16_t intTime()
    {
        uint16_t t;
        uint16_t h;
        uint16_t m;

        h = timeClient.getHours();
        if (h > 12)
            h = h - 12;
        t = (h * 100);

        m = timeClient.getMinutes();
        t = t + m;
        return t;
    }

    bool boolSec()
    {
        bool b = false;
        uint16_t s = timeClient.getSeconds();
        if (s % 2 == 1)
            b = true;
        return b;
    }

}
#endif