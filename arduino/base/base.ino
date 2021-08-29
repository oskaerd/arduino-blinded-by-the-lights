#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define NEOPIXEL_PIN       2
#define ALGO_CHANGE_BTN_PIN 3
#define NUMPIXELS           8

// NeoPixel Control Algorithms table
typedef void (*LedControl)(uint32_t);

LedControl gLedControlFuncs[] =
{
    // 1. Sinus-based control, phase shift between the Red and Blue sine waves samples
    //    is controled with potentiometer.
    SinusLeds,
    // 2. Three potentiometers control the walues of RGB, pulses a bit.
    AnalogKnobs, 
    // 3. Music
    SerialMusic,
};
#define RBG_CONTROL_CBS_COUNT (sizeof(gLedControlFuncs) / sizeof(LedControl))

uint8_t red, green, blue;
volatile uint8_t gCurrentLedFuncIdx = 0;
uint32_t gCurrentIteration = 0x0;
