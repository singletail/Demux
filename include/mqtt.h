#ifdef _MQTT

#ifndef _MQTT_H
#define _MQTT_H

namespace mqtt
{
    void init();
    void setBufferSize(uint16_t bsize);
    void setKeepAlive(uint16_t kadur);

    void callback(char *topic, byte *payload, unsigned int length);
    void connect();
    void subscribe(char *topic);
    void check();
    void send(char *topic, char *msg);
    bool json(std::string topic, std::string msg, bool retain);

    bool isConnected();
}
#endif
#endif
