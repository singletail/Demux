#ifndef _MAIN_H
#define _MAIN_H

#include "include.inc"
#include "../config.inc"

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "debug.h"
#include "timer.h"

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

// LED
#ifdef _LED
#include "led.h"
#endif

// Serial
#define SERIAL_BAUD 921600

// WiFI
#ifdef _WIFI
#define NET_TIMEOUT 8000
#endif

// AUTH
#ifdef _AUTH
#include "auth.h"
#endif

void setup();
void tick();
void loop();
void delayed_network_setup();

#endif
