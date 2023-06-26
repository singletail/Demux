#include "main.h"

void setup()
{
  debug::init();
  net::init();
  timer::init();
  geo::init();
#ifdef _MQTT
  mqtt::init();
#endif
#ifdef _LED
  led::init();
#endif
#ifdef _OLED
  oled::init();
#endif
#ifdef _BLE
  ble::init();
#endif
#ifdef _RADAR
  radar::init();
#endif
}

void tick()
{
  // Serial.println(ntp::NTP_TimeString_Full());
  net::check();
#ifdef _MQTT
  mqtt::check();
#endif
#ifdef _OLED
  oled::update();
#endif
#ifdef _RADAR
  radar::read();
#endif
#ifdef _SENSOR
  sensor::loop();
#endif
}

void loop()
{
  timer::check();
#ifdef _LED
  led::pride();
#endif
}

void delayed_network_setup()
{
  Serial.println(F("Delayed Setup"));
#ifdef _WIFI
  // http::init();
  geo::fetch();
  geo::debugJson();
  ntp::NTP_Init(geo::getOffset());
#ifdef _BLE
  ble::scan();
#endif

#endif
}