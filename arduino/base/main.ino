// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
Adafruit_NeoPixel allUnits[] = {
    Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_UNIT0_PIN, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_UNIT1_PIN, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_UNIT2_PIN, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_UNIT3_PIN, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_UNIT4_PIN, NEO_GRB + NEO_KHZ800),
};

#define NEOPIXEL_UNITS_COUNT  (sizeof(allUnits)/sizeof(Adafruit_NeoPixel))
#define FOR_ALL_UNITS(i) for(uint8_t i = 0; i < NEOPIXEL_UNITS_COUNT; i++)

#define UART_TIMEOUT  1000

#define MIN_COLOR     100
#define MAX_COLOR     170


void setup(void)
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

    //attachInterrupt(digitalPinToInterrupt(ALGO_CHANGE_BTN_PIN), ChangeAlgoButtonIsr, FALLING);

    Serial.begin(115200);
    Serial.setTimeout(UART_TIMEOUT);

    FOR_ALL_UNITS(i)
    {
        // INITIALIZE NeoPixel strip object (REQUIRED)
        allUnits[i].begin();
        // Set all pixel colors to 'off'
        allUnits[i].clear();
    }
}

void loop(void)
{
    // Run selected way of setting the NeoPixel's color
    //uint32_t delayVal = gLedControlFuncs[gCurrentLedFuncIdx](gCurrentIteration);
    uint32_t delayVal = SinusLeds(gCurrentIteration);
    gCurrentIteration++;
    
    FOR_ALL_UNITS(unit)
    {
        for(int i = 0; i < NUMPIXELS; i++)
        {         
            // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
            allUnits[unit].setPixelColor(i, allUnits[unit].Color(red, green, blue));
            // Send the updated pixel colors to the hardware.
            allUnits[unit].show();
        }
    }

    delay(delayVal);
}
