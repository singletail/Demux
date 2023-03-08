#ifdef _WIFI
#include "main.h"

namespace net
{
    bool debug = false;
    unsigned long last = 0;
    bool is_connected = false;
    char status[32] = {'\0'};
    char displayStatus[32] = {'\0'};
    char ssid[16];
    int8_t rssi;

    void init()
    {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_STA);
        WiFi.onEvent(net_event, WiFiEvent_t::ARDUINO_EVENT_MAX);
        last = millis();
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        if (debug)
            Serial.println("Network Connecting...");
    }

    void init_network_modules()
    {
        delayed_network_setup(); // in main.cpp
    }

    void net_event(WiFiEvent_t event, WiFiEventInfo_t info)
    {
        if (debug)
        {
            Serial.print("*** Network Event: ");
            Serial.print(event);
            Serial.print(" ");
            Serial.println(getEventString(event));
        }
        check();
    }

    void check()
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            if (debug)
                Serial.println("WiFi not connected.");

            if (millis() > (last + NET_TIMEOUT))
            {
                if (debug)
                    Serial.println("Attempting to reconnect.");

                WiFi.disconnect();
                init();
            }
        }
        else
        {
            rssi = WiFi.RSSI();
            sprintf(ssid, "%s", WiFi.SSID().c_str());
            if (is_connected != true)
            {
                is_connected = true;
                Serial.print("Network connected - ");
                Serial.print(ssid);
                Serial.print(" - ");
                Serial.println(rssi);
                init_network_modules();
            }
        }
    }

    bool getStatus()
    {
        bool st = false;
        if (WiFi.status() == WL_CONNECTED)
        {
            st = true;
        }
        return st;
    }

    const char *getDisplayStatus()
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            sprintf(displayStatus, "%s", getStatusString());
        }
        else
        {
            sprintf(displayStatus, "%i", rssi);
        }
        return displayStatus;
    }

    const char *getDisplayBase()
    {
        return ssid;
    }

    const char *getStatusString()
    {
        switch (WiFi.status())
        {
        case 0:
            sprintf(status, "%s", "WL_IDLE_STATUS");
            break;
        case 1:
            sprintf(status, "%s", "WL_NO_SSID_AVAIL");
            break;
        case 2:
            sprintf(status, "%s", "WL_SCAN_COMPLETED");
            break;
        case 3:
            sprintf(status, "%s", "WL_CONNECTED");
            break;
        case 4:
            sprintf(status, "%s", "WL_CONNECT_FAILED");
            break;
        case 5:
            sprintf(status, "%s", "WL_CONNECTION_LOST");
            break;
        case 6:
            sprintf(status, "%s", "WL_DISCONNECTED");
            break;
        case 255:
            sprintf(status, "%s", "WL_NO_SHIELD");
            break;
        default:
            sprintf(status, "%s", "Unknown");
        }
        return status;
    }

    char *getEventString(int evtNum)
    {
        switch (evtNum)
        {
        case 0:
            sprintf(status, "%s", "SYSTEM_EVENT_WIFI_READY");
            break;
        case 1:
            sprintf(status, "%s", "SYSTEM_EVENT_SCAN_DONE");
            break;
        case 2:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_START");
            break;
        case 3:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_STOP");
            break;
        case 4:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_CONNECTED");
            break;
        case 5:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_DISCONNECTED");
            break;
        case 6:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_AUTHMODE_CHANGE");
            break;
        case 7:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_GOT_IP");
            break;
        case 8:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_LOST_IP");
            break;
        case 9:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_WPS_ER_SUCCESS");
            break;
        case 10:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_WPS_ER_FAILED");
            break;
        case 11:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_WPS_ER_TIMEOUT");
            break;
        case 12:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_WPS_ER_PIN");
            break;
        case 13:
            sprintf(status, "%s", "SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP");
            break;
        case 14:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_START");
            break;
        case 15:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_STOP");
            break;
        case 16:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_STACONNECTED");
            break;
        case 17:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_STADISCONNECTED");
            break;
        case 18:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_STAIPASSIGNED");
            break;
        case 19:
            sprintf(status, "%s", "SYSTEM_EVENT_AP_PROBEREQRECVED");
            break;
        case 20:
            sprintf(status, "%s", "SYSTEM_EVENT_GOT_IP6");
            break;
        case 21:
            sprintf(status, "%s", "SYSTEM_EVENT_ETH_START");
            break;
        case 22:
            sprintf(status, "%s", "SYSTEM_EVENT_ETH_STOP");
            break;
        case 23:
            sprintf(status, "%s", "SYSTEM_EVENT_ETH_CONNECTED");
            break;
        case 24:
            sprintf(status, "%s", "SYSTEM_EVENT_ETH_DISCONNECTED");
            break;
        case 25:
            sprintf(status, "%s", "SYSTEM_EVENT_ETH_GOT_IP");
            break;
        case 26:
            sprintf(status, "%s", "SYSTEM_EVENT_MAX");
            break;
        default:
            sprintf(status, "%s", "Unknown");
        }
        return status;
    }

}

#endif
