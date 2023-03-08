#ifdef _AUTH

#ifndef _AUTH_H
#define _AUTH_H

#include "main.h"

namespace auth {
    void init();
    void setRestoreCodeArray(String codeString);
    uint8_t *getRestoreCodeArray();
    void debugRestoreCodeArray();
    void setSerialArray(String serialString);
    char *getSerialArray();
    void debugSerialArray();
}

#endif
#endif