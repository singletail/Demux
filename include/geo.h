#ifdef _WIFI

#ifndef _GEO_H
#define _GEO_H

#include "main.h"

namespace geo
{

    void init();
    void fetch();
    void parseJson();
    void debugJson();

    int16_t getOffset();
    char *getIp();
    double_t getLatitude();
    double_t getLongitude();

    char *getCity();
    char *getRegion();
    char *getZip();
    char *getCountryCode();
}

#endif
#endif