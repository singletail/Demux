#ifndef _INCLUDE_INC
#define _INCLUDE_INC

//   ***   ALWAYS   ***   //

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "debug.h"
#include "timer.h"

//   ***   COMMON   ***   //

#include "led.h"

#ifdef _WIFI
#include <WiFi.h>
#include <esp_event.h>
#include <esp_wifi.h>
#include "net.h"

#include "ntp.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "http.h"
#include "geo.h"
#include <ArduinoJson.h>
#endif

#ifdef _MQTT
#include "mqtt.h"
#include <PubSubClient.h>
#endif

//   ***   SENSORS   ***   //

#include "sensor.h"

#ifdef _GAS
#include "gas.h"
#include "buzzer.h"
#endif

#ifdef _BME
#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "sensor/bme.h"
#endif

#ifdef _RADAR
#include "radar.h"
#endif

#ifdef _PIR
#include "sensor/pir.h"
#endif

#ifdef _SR04M
#include "sensor/sr04m.h"
#endif

#ifdef _SR04M2
#include "sensor/sr04m2.h"
#include <HardwareSerial.h>
#endif

//   ***   INPUT   ***   //

#ifdef _BUTTON
#include "output/button.h"
#endif

//   ***   OUTPUT   ***   //

#ifdef _AUDIO
#include "output/audio.h"
#include "output/beep.h"
#endif

#ifdef _LED_INT
#include "output/led_int.h"
#endif

#ifdef _LED_EXT
#include "output/led_ext.h"
#endif

//   ***   DISPLAY   ***   //

#ifdef _OLED
#include <U8g2lib.h>
#include "oled.h"
#endif

#ifdef _7SEGMENT
#include "7seg.h"
#include <TM1637Display.h>
#endif



//   ***   UTILITY   ***   //

#ifdef _HWTIMER
#include "hw/hwtimer.h"
#endif

// ***   BLE **** //
#ifdef _BLE
#include "ble.h"
#endif

//   ***   END   ***   //

#endif
