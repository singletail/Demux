#ifdef _7SEGMENT

#ifndef _H_7SEG
#define _H_7SEG

namespace seg
{
    void init();
    void test();
    void time();
    void random();
    void randomChars();
    uint8_t randCharFromArray();
    int roll(void);
    void value(uint16_t val);
}

#endif
#endif
