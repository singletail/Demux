#ifdef _RADAR

#ifndef _RADAR_H
#define _RADAR_H

namespace radar
{
    void init();
    void report();
    void read();
    const char *getStatus();
}

#endif
#endif
