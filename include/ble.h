#ifdef _BLE

#ifndef _BLE_H
#define _BLE_H

#include "main.h"

namespace ble {
    class MyAdvertisedDeviceCallbacks;
    void scan();
    void report();
    String getAdvTypeFromNum(uint8_t advType);
}

#endif
#endif