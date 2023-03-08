#ifdef _7SEGMENT
#include "main.h"

#define CLK_1 23
#define DIO_1 22

#define CLK_2 19
#define DIO_2 18

namespace seg {
    uint8_t data[4];
    uint16_t prevInt = 10000;

    char randchars[11] = {'A', 'C', 'E', 'F', 'H', 'J', 'L', 'P', 'S', 'T', 'U'};

  //
  //      A
  //     ---
  //  F |   | B
  //     -G-
  //  E |   | C
  //     ---
  //      D

  //   XGFEDCBA 
    const uint8_t segments[20] = {
        0b00111111,    // 0
        0b00000110,    // 1
        0b01011011,    // 2
        0b01001111,    // 3
        0b01100110,    // 4
        0b01101101,    // 5
        0b01111101,    // 6
        0b00000111,    // 7
        0b01111111,    // 8
        0b01101111,    // 9
        0b01110111,    // A
  //      0b01111100,    // b
        0b00111001,    // C
  //      0b01011110,    // d
        0b01111001,    // E
        0b01110001,    // F
        0b01110110,    // H
        0b00011110,    // J
        0b00111000,    // L
        0b01110011,    // P
        0b01101101,    // S
        0b00111110,    // U
    };

    TM1637Display display1(CLK_1, DIO_1);
    TM1637Display display2(CLK_2, DIO_2);

    void init() {
        srand(analogRead(A0));
        display1.setBrightness(0x0f);
        display2.setBrightness(0x0f);
        display1.clear();
        display2.clear();
    }

    void test() {
        display1.clear();

        data[0] = display1.encodeDigit(1);
        data[1] = display1.encodeDigit(2);
        data[2] = display1.encodeDigit(3);
        data[3] = display1.encodeDigit(4);

        display1.setSegments(data);
    }

    void time() {
        uint16_t t = ntp::intTime();
        uint8_t p = 1;
        uint8_t l = 3;
        uint8_t dots = 0;

        if (t > 999) {
            l = 4;
            p = 0;
        }

        if (ntp::boolSec()) {
            dots = 0b11100000;
        }
        
        if (t < prevInt) {
            display1.clear();
            display2.clear();
        }

        prevInt = t;
        display1.showNumberDecEx(t, dots, false, l, p);
        display2.showNumberDecEx(t, dots, false, l, p);
    }

    void random() {
      display1.showNumberDecEx(roll(), 0, true, 4, 0);
      display2.showNumberDecEx(roll(), 0, true, 4, 0);
    }

    void value(uint16_t val) {
      display1.showNumberDecEx(val, 0, false, 4, 0);
    }

    void randomChars() {
      for(int i = 0; i < 4; i++) {
        data[i] = randCharFromArray();
      }
      display1.setSegments(data);
      for(int i = 0; i < 4; i++) {
        data[i] = randCharFromArray();
      }
      display2.setSegments(data);
    }

    uint8_t randCharFromArray() {
      return segments[rand() % 20];
    }

    int roll(void) {
      return rand() % 10000;
    }

}

#endif


/*

include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};

TM1637Display display(CLK, DIO);

void setup()
{
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);

  // All segments on
  display.setSegments(data);
  delay(TEST_DELAY);

  // Selectively set different digits
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  delay(TEST_DELAY);


//  for(k = 3; k >= 0; k--) {
//	display.setSegments(data, 1, k);
//	delay(TEST_DELAY);
//	}

  display.clear();
  display.setSegments(data+2, 2, 2);
  delay(TEST_DELAY);

  display.clear();
  display.setSegments(data+2, 2, 1);
  delay(TEST_DELAY);

  display.clear();
  display.setSegments(data+1, 3, 1);
  delay(TEST_DELAY);


  // Show decimal numbers with/without leading zeros
  display.showNumberDec(0, false); // Expect: ___0
  delay(TEST_DELAY);
  display.showNumberDec(0, true);  // Expect: 0000
  delay(TEST_DELAY);
	display.showNumberDec(1, false); // Expect: ___1
	delay(TEST_DELAY);
  display.showNumberDec(1, true);  // Expect: 0001
  delay(TEST_DELAY);
  display.showNumberDec(301, false); // Expect: _301
  delay(TEST_DELAY);
  display.showNumberDec(301, true); // Expect: 0301
  delay(TEST_DELAY);
  display.clear();
  display.showNumberDec(14, false, 2, 1); // Expect: _14_
  delay(TEST_DELAY);
  display.clear();
  display.showNumberDec(4, true, 2, 2);  // Expect: __04
  delay(TEST_DELAY);
  display.showNumberDec(-1, false);  // Expect: __-1
  delay(TEST_DELAY);
  display.showNumberDec(-12);        // Expect: _-12
  delay(TEST_DELAY);
  display.showNumberDec(-999);       // Expect: -999
  delay(TEST_DELAY);
  display.clear();
  display.showNumberDec(-5, false, 3, 0); // Expect: _-5_
  delay(TEST_DELAY);
  display.showNumberHexEx(0xf1af);        // Expect: f1Af
  delay(TEST_DELAY);
  display.showNumberHexEx(0x2c);          // Expect: __2C
  delay(TEST_DELAY);
  display.showNumberHexEx(0xd1, 0, true); // Expect: 00d1
  delay(TEST_DELAY);
  display.clear();
  display.showNumberHexEx(0xd1, 0, true, 2); // Expect: d1__
  delay(TEST_DELAY);
  
	// Run through all the dots
	for(k=0; k <= 4; k++) {
		display.showNumberDecEx(0, (0x80 >> k), true);
		delay(TEST_DELAY);
	}

  // Brightness Test
  for(k = 0; k < 4; k++)
	data[k] = 0xff;
  for(k = 0; k < 7; k++) {
    display.setBrightness(k);
    display.setSegments(data);
    delay(TEST_DELAY);
  }
  
  // On/Off test
  for(k = 0; k < 4; k++) {
    display.setBrightness(7, false);  // Turn off
    display.setSegments(data);
    delay(TEST_DELAY);
    display.setBrightness(7, true); // Turn on
    display.setSegments(data);
    delay(TEST_DELAY);  
  }

 
  // Done!
  display.setSegments(SEG_DONE);

  while(1);
}
*/