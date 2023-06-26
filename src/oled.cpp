#ifdef _OLED

#include "main.h"
#include <U8g2lib.h>

namespace oled
{

#ifdef _HELTEC
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);
#endif

#ifdef _DEVKITC
    // U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_SCL, OLED_SDA);
    U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, OLED_SCL, OLED_SDA);
#endif

    char tempWifi[64] = {'\0'};
    char tempIp[64] = {'\0'};
    char tempAddress[64] = {'\0'};
    char tempLatLon[64] = {'\0'};

    void init()
    {
        u8g2.begin();
        u8g2.enableUTF8Print();
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_luRS18_tf);
        u8g2.drawStr(0, 32, "O Hai!");
        u8g2.sendBuffer();
    }

    void update()
    {
        u8g2.setFont(u8g2_font_DigitalDiscoThin_tf);
        u8g2.setFontDirection(0);
        u8g2.firstPage();
        do
        {
            // Heltec is 128 x 64

            // Wifi

            if (net::getStatus() == true)
            {

                // WiFi symbol
                // u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
                u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
                u8g2.drawUTF8(0, 8, "\u00f8"); // WiFi

                // WiFi Signal Strength
                sprintf(tempWifi, "%s%s", net::getDisplayBase(), net::getDisplayStatus());
                u8g2.setFont(u8g2_font_profont10_tf);
                u8g2.setCursor(10, 8);
                u8g2.print(tempWifi);

                // NTP Time
                u8g2.setFont(u8g2_font_profont12_tn);
                u8g2.setCursor(76, 8);
                u8g2.print(ntp::NTP_TimeString());

                // Some Geolocation info
                // lat, lon, ip, city, region, zip, countryCode

                // IP
                sprintf(tempIp, "%s", geo::getIp());
                u8g2.setFont(u8g2_font_profont12_tf);
                u8g2.setCursor(0, 24);
                u8g2.print(tempIp);

                // address-ish
                sprintf(tempAddress, "%s, %s %s %s", geo::getCity(), geo::getRegion(), geo::getZip(), geo::getCountryCode());
                u8g2.setFont(u8g2_font_profont12_tf);
                u8g2.setCursor(0, 36);
                u8g2.print(tempAddress);

                sprintf(tempLatLon, "%.04f %.04f", geo::getLatitude(), geo::getLongitude());
                u8g2.setCursor(0, 50);
                u8g2.print(tempLatLon);
            }

            u8g2.setFont(u8g2_font_helvB24_tf);

#ifdef _RADAR
            u8g2.drawUTF8(0, 48, radar::getStatus());
#endif

            // u8g2.print(status_wifi_ssid);
            // u8g2.print("Hello!");

            // u8g2.setCursor(0, 28);
            // u8g2.print(status_wifi_rssi);

            // u8g2.setCursor(0, 42);
            // u8g2.print(arr_status_wifi);

            // u8g2.setCursor(64, 42);
            // u8g2.print(arr_status_mqtt);

            // u8g2.setCursor(0, 56);
            // u8g2.print(status_debug);

        } while (u8g2.nextPage());
    }

    // ProFont 10: u8g2_font_profont10_tf
    // ProFont 14: u8g2_font_profont22_tf
    // Helvetica Reg 14: u8g2_font_helvR14_tf
    // Helvetica Bold 14: u8g2_font_helvB14_tf
    // NBP Smart Patrol 12: u8g2_font_smart_patrol_nbp_tf
    // Unifont 12: u8g2_font_unifont_tf
    // DA Digital Disco 12: u8g2_font_DigitalDiscoThin_tf
    // Lucida 18: u8g2_font_luRS18_tf
    // Freedom 26: u8g2_font_freedoomr25_tn
    // More: https://github.com/olikraus/u8g2/wiki/fntlistall

}

#endif