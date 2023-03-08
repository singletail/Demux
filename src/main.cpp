#include "main.h"

void setup()
{
  debug::init();
  net::init();
  timer::init();
  geo::init();
}

void tick()
{
  Serial.println(ntp::NTP_TimeString_Full());
  net::check();
}

void loop()
{
  timer::check();
}

void delayed_network_setup()
{
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