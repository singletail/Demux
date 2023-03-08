#ifdef _AUTH
#include "main.h"

namespace auth {

    const String restoreCode = "FJ9YAYEPAG";
    const String serialNumber = "EU-1501-1473-5206";

    const String SERVER = "http://mobile-service.blizzard.com";
    const String ENROLL_PATH = "/enrollment/enroll2.htm";
	const String SYNC_PATH = "/enrollment/time.htm";
	const String RESTORE_PATH = "/enrollment/initiatePaperRestore.htm";
	const String RESTOREVALIDATE_PATH = "/enrollment/validatePaperRestore.htm";

    uint8_t restoreCodeArray[10];
    char serialArray[14];

    String dashString = "-";
    uint8_t dashInt = dashString[0];


    void init() {
        setRestoreCodeArray(restoreCode);
        setSerialArray(serialNumber);

        debugRestoreCodeArray();
        debugSerialArray();
    }

    void setRestoreCodeArray(String codeString)
    {
        // array stripped of unusable items: 0123456789ABCDEFGHJKMNPQRTUVWXYZ
        uint8_t strLen = codeString.length();
        if (strLen == 10) {
            for (size_t i = 0; i < strLen; ++i) {
                uint8_t tempInt = codeString[i];
                if (tempInt > 47 && tempInt < 58) {
                    tempInt -= 48;
                } else {
                    uint8_t mod = tempInt - 55;
                    if (tempInt > 72)
                        mod -= 1;
                    if (tempInt > 75)
                        mod -= 1;
                    if (tempInt > 78)
                        mod -= 1;
                    if (tempInt > 82)
                        mod -= 1;
                    tempInt = mod;
                }
                restoreCodeArray[i] = tempInt;
            }
        }
    }

    uint8_t *getRestoreCodeArray() {
        return restoreCodeArray;
    }

    void setSerialArray(String serialString)
    {
        uint8_t counter = 0;
        uint8_t strLen = serialString.length();
        for (size_t i = 0; i < strLen; ++i) {
            uint8_t charInt = serialString[i];
            if (dashInt != charInt) {
                serialArray[counter] = serialString[i];
                counter++;
            }
        }
    }

    char *getSerialArray() {
        return serialArray;
    }

    void debugRestoreCodeArray() {
        Serial.print("Restore Code Array Transformed:");
        for (size_t i = 0; i < 10; ++i) {
            Serial.print(" ");
            Serial.print(restoreCodeArray[i]);
        }
        Serial.println(" --");
    }

    void debugSerialArray() {
        Serial.print("Serial Array Transformed:");
        for (size_t i = 0; i < 14; ++i) {
            Serial.print(" ");
            Serial.print(serialArray[i]);
        }
        Serial.println(" --");
    }


}
#endif