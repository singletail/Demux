// http://ip-api.com/json/{query}?fields=42526719

#ifdef _WIFI
#include "main.h"

namespace geo
{

    StaticJsonDocument<512> json;

    const String host = "ip-api.com";
    const String uri = "json/?fields=42526719";
    const uint8_t port = 80;

    const char *success = "success";

    bool isSetup = false;

    int16_t offset = -14400;
    double_t latitude;
    double_t longitude;
    char country[16];
    char countryCode[3];
    char region[3];
    char city[32];
    char zip[6];
    char timezone[32];
    char ip[16];

    void init()
    {
        // offset = -14400;
    }

    void fetch()
    {
        String message;
        message = http::get(host, port, uri);

        Serial.print("Debug: ");
        Serial.println(message);

        char *incomingJson = new char[message.length() + 1];
        strcpy(incomingJson, message.c_str());

        DeserializationError error = deserializeJson(json, incomingJson);
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        const char *response_status = json["status"];
        if (strcmp(response_status, success) == 0)
        {
            parseJson();
            debugJson();
        }
        else
        {
            Serial.print("Json data error: ");
            Serial.println(response_status);
        }
    }

    void parseJson()
    {
        Serial.println("parseJson()");
        offset = json["offset"];
        latitude = json["lat"];
        longitude = json["lon"];
        strcpy(country, json["country"]);
        strcpy(countryCode, json["countryCode"]);
        strcpy(region, json["region"]);
        strcpy(city, json["city"]);
        strcpy(zip, json["zip"]);
        strcpy(timezone, json["timezone"]);
        strcpy(ip, json["query"]);
        isSetup = true;
    }

    void debugJson()
    {
        Serial.print("Geo Offset: ");
        Serial.println(offset);
        Serial.println(latitude, 6);
        Serial.println(longitude, 6);
        Serial.println(country);
        Serial.println(countryCode);
        Serial.println(region);
        Serial.println(city);
        Serial.println(zip);
        Serial.println(timezone);
        Serial.println(ip);
        Serial.println(isSetup);
    }

    int16_t getOffset()
    {
        return offset;
    }

    char *getIp()
    {
        return ip;
    }

    double_t getLatitude()
    {
        return latitude;
    }

    double_t getLongitude()
    {
        return longitude;
    }

    char *getCity()
    {
        return city;
    }

    char *getRegion()
    {
        return region;
    }

    char *getZip()
    {
        return zip;
    }

    char *getCountryCode()
    {
        return countryCode;
    }
}

#endif