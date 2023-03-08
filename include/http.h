#ifdef _WIFI

#ifndef _HTTP_H
#define _HTTP_H

namespace http
{
    void init();
    uint8_t connected();
    String get(String host, uint16_t port, String uri);

    // void connect();
    // void send();
    // void receive();
    // void disconnect();
}

#endif
#endif