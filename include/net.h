#ifdef _WIFI

#ifndef _NET_H
#define _NET_H

namespace net
{
    void init();
    // void WiFionEvent(system_event_id_t WiFiEvent, system_event_info_t WiFiEventInfo);
    void net_event(WiFiEvent_t event, WiFiEventInfo_t info);
    void init_network_modules();
    void check();

    bool getStatus();
    const char *getDisplayStatus();
    const char *getDisplayBase();
    const char *getStatusString();
    char *getEventString(int evtNum);

    signed int Net_RSSI();
    char *Net_SSID();
    char *Net_MAC();
    int Net_Status();
}

#endif
#endif
