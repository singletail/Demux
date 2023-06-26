#ifdef _WIFI

#ifndef _NET_H
#define _NET_H

namespace net
{
    void init();
    void net_event(WiFiEvent_t event, WiFiEventInfo_t info);
    void init_network_modules();
    void check();

    bool getStatus();
    const char *getDisplayStatus();
    const char *getDisplayBase();
    const char *getStatusString();
    char *getEventString(int evtNum);

}

#endif
#endif
