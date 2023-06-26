#ifdef _MQTT

#include "main.h"

namespace mqtt
{
    const char *broker = MQTT_BROKER;
    const char *user = MQTT_USER;
    const char *pass = MQTT_PASS;
    const char *id = MQTT_ID;

    const uint16_t port = 1883;
    char receive_buffer[128];

    void callback(char *topic, byte *payload, unsigned int length)
    {
        for (int i = 0; i < length; i++)
        {
            if (i < 128)
            {
                receive_buffer[i] = payload[i];
            }
            receive_buffer[i + 1] = {'\0'};
        }
        Serial.print("MQTT RECEIVE: ");
        Serial.println(receive_buffer);
    }

    WiFiClient wifiClient;
    PubSubClient mqttClient;

    //(broker, port, callback, espClient);

    void init()
    {
        Serial.println("- MQTT Setup");
        mqttClient.setClient(wifiClient);
        mqttClient.setServer(broker, port);
        mqttClient.setCallback(callback);
        setBufferSize(2048);
        setKeepAlive(300);
    }

    void setBufferSize(uint16_t bsize)
    {
        bool ok = mqttClient.setBufferSize(2048);
        if (ok == true)
        {
            Serial.println("- PubSubClient buffer size changed.");
        }
        else
        {
            Serial.println("- WARNING: PubSubClient buffer size NOT changed.");
        }
        Serial.print("- PubSubClient buffer size: ");
        Serial.println(mqttClient.getBufferSize());
    }

    void setKeepAlive(uint16_t kadur)
    {
        mqttClient.setKeepAlive(kadur);
        Serial.print("- PubSubClient keepAlive set to ");
        Serial.print(kadur);
        Serial.println(". Probably.");
    }

    void connect()
    {
        bool ok = mqttClient.connect(id, user, pass);
        if (ok == true)
        {
            Serial.println("+ MQTT Connected ");
        }
        else
        {
            Serial.println("- MQTT Error: Could not connect ");
        }
    }

    void subscribe(char *topic)
    {
        mqttClient.subscribe(topic);
    }

    void check()
    {
        if (mqttClient.connected() != true)
        {
            Serial.println("- MQTT check fail - not connected.");
            connect();
        }
    }

    void send(char *topic, char *msg)
    {
        check();
        if (mqttClient.connected() == true)
        {
            mqttClient.publish(topic, msg);
            Serial.print("+++ MQTT Sent: ");
            Serial.println(topic);
            Serial.print("+++ Json: ");
            Serial.println(msg);
        }
        else
        {
            Serial.println("- MQTT Send Error: Not Connected.");
        }
    }

    bool json(std::string topic, std::string msg, bool retain)
    {
        bool ok = false;
        check();
        if (mqttClient.connected())
        {
            const char *topic_c = topic.c_str();
            const char *msg_c = msg.c_str();
            ok = mqttClient.publish(topic_c, msg_c, retain);
            Serial.print("+++ MQTT Sent: ");
            Serial.println(topic_c);
            Serial.print("+++ Json: ");
            Serial.println(msg_c);
        }
        else
        {
            Serial.println("- MQTT SendMsg Error: Not Connected.");
        }
        return ok;
    }

    bool isConnected()
    {
        return mqttClient.connected();
    }
}

#endif