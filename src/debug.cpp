#include "main.h"

namespace debug
{

    inline namespace info
    {
        char chip[8];
        uint8_t cores;
        uint8_t revision;
        int32_t frequency;
        char sdk[8];
        uint32_t sketchSize;
        uint32_t sketchFree;
        char mac[12];
    }

    void init()
    {
        Serial.begin(SERIAL_BAUD);
        Serial.flush();
        collect();
        print();

        // chipinfo();
    }

    void chipinfo()
    {
        const char *ModelStrings[] PROGMEM = {"", "ESP32"};

        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);

        Serial.println("=== esp_chip_info_t ===");
        Serial.printf("Model: %s\r\n", ModelStrings[chip_info.model]);
        Serial.printf("Cores: %d\r\n", chip_info.cores);
        Serial.printf("Revision: %d\r\n", chip_info.revision);

        // Features
        if (chip_info.features & CHIP_FEATURE_EMB_FLASH)
            Serial.println("+ Embedded Flash");

        if (chip_info.features & CHIP_FEATURE_WIFI_BGN)
            Serial.println("+ Wifi-BGN");

        if (chip_info.features & CHIP_FEATURE_BLE)
            Serial.println("+ BLE");

        if (chip_info.features & CHIP_FEATURE_BT)
            Serial.println("+ Bluetooth");

        if (chip_info.features & CHIP_FEATURE_IEEE802154)
            Serial.println("+ IEEE 802.15.4");

        if (chip_info.features & CHIP_FEATURE_EMB_PSRAM)
            Serial.println("+ Embedded PSRAM");

        // MAC Address
        String MACString = "";
        uint64_t chipid = ESP.getEfuseMac();
        for (int i = 0; i < 6; i++)
        {
            if (i > 0)
                MACString.concat(":");
            uint8_t Octet = chipid >> (i * 8);
            if (Octet > 16)
                MACString.concat("0");
            MACString.concat(String(Octet, HEX));
        }
        Serial.println("MAC Address: " + MACString);

        // Flash Size
        uint32_t FlashSize = ESP.getFlashChipSize();
        String ValueString = "";
        do
        {
            String temp = String(FlashSize);
            if (FlashSize >= 1000)
            {
                temp = "00" + temp;
                ValueString = "," + temp.substring(temp.length() - 3, temp.length()) + ValueString;
            }
            else
            {
                ValueString = temp + ValueString;
            }
            FlashSize /= 1000;
        } while (FlashSize > 0);
        Serial.println("Flash Size: " + ValueString);
        /*
            Serial.print("cores: ");
            Serial.println(chipStruct->cores);

            Serial.print("revision: ");
            Serial.println(chipStruct->revision);

            Serial.print("features: ");
            Serial.println(chipStruct->features);
            */
    }

    void collect()
    {
        sprintf(info::chip, "%s", const_cast<char *>(ESP.getChipModel()));
        info::cores = ESP.getChipCores();
        info::revision = ESP.getChipRevision();
        info::frequency = ESP.getCpuFreqMHz();
        sprintf(info::sdk, "%s", const_cast<char *>(ESP.getSdkVersion()));
        info::sketchSize = ESP.getSketchSize();
        info::sketchFree = ESP.getFreeSketchSpace();

#ifdef _WIFI
        sprintf(info::mac, "%s", WiFi.macAddress().c_str());
#endif
    }

    void print()
    {
        Serial.println("*********************");
        Serial.println(PROGRAM_NAME);
        Serial.print("Version: ");
        Serial.println(VERSION);
        Serial.println("---------------------");
        Serial.print("-- Chip: ");
        Serial.println(info::chip);
        Serial.print("-- Cores: ");
        Serial.println(info::cores);
        Serial.print("-- Revision: ");
        Serial.println(info::revision);
        Serial.print("-- Frequency: ");
        Serial.println(info::frequency);
        Serial.print("-- SDK: ");
        Serial.println(info::sdk);
        Serial.print("-- Sketch Size: ");
        Serial.println(info::sketchSize);
        Serial.print("-- Sketch Free: ");
        Serial.println(info::sketchFree);
        Serial.print("-- Mac Address: ");
        Serial.println(info::mac);
        Serial.println("---------------------");

        Serial.print("+- Total Heap:  ");
        Serial.println(ESP.getHeapSize());
        Serial.print("+- Free Heap:   ");
        Serial.println(ESP.getFreeHeap());
        Serial.print("Total PSRAM: ");
        Serial.println(ESP.getPsramSize());
        Serial.print("Free PSRAM:  ");
        Serial.println(ESP.getFreePsram());
    }
}