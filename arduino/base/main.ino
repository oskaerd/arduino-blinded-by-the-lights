// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
// todo make table
Adafruit_NeoPixel unit0(NUMPIXELS, NEOPIXEL_UNIT0_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel unit1(NUMPIXELS, NEOPIXEL_UNIT1_PIN, NEO_GRB + NEO_KHZ800);


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
    red = 100;
    blue = 100;

    // todo make for ALL_UNITS define
    unit0.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    unit1.begin();
    unit0.clear(); // Set all pixel colors to 'off'
    unit1.clear();
}

void loop(void)
{
    // Run selected way of setting the NeoPixel's color
    //uint32_t delayVal = gLedControlFuncs[gCurrentLedFuncIdx](gCurrentIteration);
    uint32_t delayVal = SinusLeds(gCurrentIteration);
    gCurrentIteration++;
    for(int i = 0; i < NUMPIXELS; i++)
    {         
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        unit0.setPixelColor(i, unit0.Color(red, green, blue));
        unit1.setPixelColor(i, unit1.Color(red, green, blue));
       // Send the updated pixel colors to the hardware.
        unit0.show();
        unit1.show();
    }

    delay(delayVal);
}
