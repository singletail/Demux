#ifdef _BLE

#include "main.h"

#include <NimBLEDevice.h>
#include <NimBLEAdvertisedDevice.h>
#include "NimBLEEddystoneURL.h"
#include "NimBLEEddystoneTLM.h"
#include "NimBLEBeacon.h"

namespace ble {
    #define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00) >> 8) + (((x)&0xFF) << 8))
    int scanTime = 5; //In seconds
    BLEScan *pBLEScan;
    bool isSetup = false;

    class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
    {
        void onResult(BLEAdvertisedDevice *advertisedDevice) {
            Serial.println("\nB=========>> Parsing new device:");

            // Address
            NimBLEAddress bleAddress = advertisedDevice->getAddress();
            std::string bleAddressString = bleAddress.toString();
            char bleAddressChar[32];
            strcpy(bleAddressChar, bleAddressString.c_str());
            Serial.print("B++ Address: ");
            Serial.println(bleAddressChar);

            // Advertisement Type
            uint8_t bleAdvType = advertisedDevice->getAdvType();
            Serial.print("B== Adv Type: ");
            Serial.println(getAdvTypeFromNum(bleAdvType).c_str());

            // Manufacturer Info
            std::string bleManufData = advertisedDevice->getManufacturerData();
            Serial.print("B++ Manufacturer Data: ");
            Serial.println(bleManufData.c_str());

            // URI
            std::string bleURI = advertisedDevice->getURI();
            if (bleURI != "") {
                Serial.print("B++ URI: ");
                Serial.println(bleURI.c_str());
            }

            // RSSI
            int bleRSSI = advertisedDevice->getRSSI();
            Serial.print("B++ RSSI: ");
            Serial.println(bleRSSI);

            // TX Power  int8_t NimBLEAdvertisedDevice::getTXPower() {
            int8_t bleTX = advertisedDevice->getTXPower();
            Serial.print("B++ TX Power: ");
            Serial.println(bleTX);


            // Name
            if (advertisedDevice->haveName()) {
                Serial.print("B== Name: ");
                Serial.println(advertisedDevice->getName().c_str());
            }

            if (advertisedDevice->haveServiceUUID()) {
                BLEUUID devUUID = advertisedDevice->getServiceUUID();
                Serial.print("B== Device has ServiceUUID: ");
                Serial.print(devUUID.toString().c_str());
            } else {
                if (advertisedDevice->haveManufacturerData() == true) {
                    std::string strManufacturerData = advertisedDevice->getManufacturerData();
                    uint8_t cManufacturerData[100];
                    strManufacturerData.copy((char *)cManufacturerData, strManufacturerData.length(), 0);

                    if (strManufacturerData.length() == 25 && cManufacturerData[0] == 0x4C && cManufacturerData[1] == 0x00) {
                        Serial.print("B== Device is iBeacon: ");
                        BLEBeacon oBeacon = BLEBeacon();
                        oBeacon.setData(strManufacturerData);
                        Serial.printf("ID: %04X Major: %d Minor: %d UUID: %s Power: %d\n", oBeacon.getManufacturerId(), ENDIAN_CHANGE_U16(oBeacon.getMajor()), ENDIAN_CHANGE_U16(oBeacon.getMinor()), oBeacon.getProximityUUID().toString().c_str(), oBeacon.getSignalPower());
                    } else {
                        Serial.print("B== Found beacon: ");
                        Serial.printf("strManufacturerData: %d ", strManufacturerData.length());
                        for (int i = 0; i < strManufacturerData.length(); i++) {
                            Serial.printf("[%X]", cManufacturerData[i]);
                        }
                        Serial.printf("\n");
                    }
                }
                return;
            }

            BLEUUID eddyUUID = (uint16_t)0xfeaa;

            if (advertisedDevice->getServiceUUID().equals(eddyUUID)) {
                std::string serviceData = advertisedDevice->getServiceData(eddyUUID);
                if (serviceData[0] == 0x10) {
                    Serial.println("B====> Found an EddystoneURL beacon!");
                    BLEEddystoneURL foundEddyURL = BLEEddystoneURL();

                    foundEddyURL.setData(serviceData);
                    std::string bareURL = foundEddyURL.getURL();
                    
                    if (bareURL[0] == 0x00) {
                        Serial.println("DATA-->");
                        for (int idx = 0; idx < serviceData.length(); idx++) {
                            Serial.printf("0x%08X ", serviceData[idx]);
                        }
                        Serial.println("\nInvalid Data");
                        return;
                    }

                    Serial.printf("Found URL: %s\n", foundEddyURL.getURL().c_str());
                    Serial.printf("Decoded URL: %s\n", foundEddyURL.getDecodedURL().c_str());
                    Serial.printf("TX power %d\n", foundEddyURL.getPower());
                    Serial.println("\n");
                } else if (serviceData[0] == 0x20) {
                    Serial.println("B====> Found an EddystoneTLM beacon!");
                    BLEEddystoneTLM foundEddyURL = BLEEddystoneTLM();
                    foundEddyURL.setData(serviceData);

                    Serial.printf("Reported battery voltage: %dmV\n", foundEddyURL.getVolt());
                    Serial.printf("Reported temperature from TLM class: %.2fC\n", (double)foundEddyURL.getTemp());
                    int temp = (int)serviceData[5] + (int)(serviceData[4] << 8);
                    float calcTemp = temp / 256.0f;
                    Serial.printf("Reported temperature from data: %.2fC\n", calcTemp);
                    Serial.printf("Reported advertise count: %d\n", foundEddyURL.getCount());
                    Serial.printf("Reported time since last reboot: %ds\n", foundEddyURL.getTime());
                    Serial.println("\n");
                    Serial.print(foundEddyURL.toString().c_str());
                    Serial.println("");
                }
            }
            Serial.println("");
        }
    };

    void scan()
    {
        if (!isSetup) {
            Serial.println("B====> ble::scan begin.");

            BLEDevice::init("Sex Machine");
            pBLEScan = BLEDevice::getScan(); //create new scan
            pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
            pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
            pBLEScan->setInterval(100);
            pBLEScan->setWindow(99); // less or equal setInterval value
        
            isSetup = true;
        }
    }

    void report()
    {
        if (isSetup) {
            BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
            Serial.print("B====> ble::report -- Devices found: ");
            Serial.println(foundDevices.getCount());
            Serial.println("B====> ble::report done.\n");
            pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
        }
    }

    String getAdvTypeFromNum(uint8_t advType) {
        String advTypeStr;
        switch (advType) {
            case 0:
                advTypeStr = "indirect advertising";
                break;
            case 1:
                advTypeStr = "direct advertisng - high duty cycle";
                break;
            case 2:
                advTypeStr = "indirect scan response";
                break;
            case 3:
                advTypeStr = "indirect advertisng - not connectable";
                break;
            case 4:
                advTypeStr = "direct advertising - low duty cycle";
                break;
            default:
                advTypeStr = "unknown";
                break;
        }
        return advTypeStr;
    }
}

#endif