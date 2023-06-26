#ifdef _WIFI

#include "main.h"
#include <HTTPClient.h>
// #include <WiFiClientSecure.h>

namespace http
{
    const bool debug = true;
    const char *server = HTTP_HOST;
    const uint16_t port = 443;

    // WiFiClientSecure *wifiClientSecure = new WiFiClientSecure;
    HTTPClient httpClient;

    void init()
    {
        if (debug)
            Serial.println("http::init()");
        // if (WiFi.isConnected())
        //     wifiClient -> setInsecure();
    }

    uint8_t connected()
    {
        return httpClient.connected();
    }

    String get(String host, uint16_t port, String uri)
    {
        String payload = "Error.";
        if (WiFi.isConnected())
        {
            httpClient.begin(host, port, uri);
            int httpCode = httpClient.GET();
            if (httpCode == HTTP_CODE_OK)
            {
                payload = httpClient.getString();
                // Serial.print("+++ http payload: ");
                // Serial.println(payload);
            }
            else
            {
                payload = "Error" + httpCode;
            }
        }
        else
        {
            Serial.println("http::get Error - WiFi not connected.");
        }
        return payload;
    }

    /*
    void connect() {
        if (!connected()) {
            if (debug)
                Serial.println("http::connect()");
            bool ok;
            ok = httpClient.connect(server, port);
            if (!ok && debug)
                Serial.println("http error");
        }
    }

    void send() {
        if (debug)
            Serial.println("http::send()");

        if (connected) {
            if (debug)
                Serial.println("http connected");
            espHttpClient.begin("http://example.com/index.html");
        } else {
            if (debug)
                Serial.println("http NOT connected");
        }
    }

    void receive() {
        if (espHttpClient.available()) {
            if (debug) {
                Serial.println("http: data waiting");
            }
            Serial.print("http received: ");
            while (httpClient.available()) {
                char c = httpClient.read();
                Serial.print(c);
            }
            Serial.println("");
        }
    }

    void disconnect() {
        espHttpClient.stop();
    }
    */
}

#endif
