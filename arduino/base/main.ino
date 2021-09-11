// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define UART_TIMEOUT  200
// Time (in milliseconds) to pause between pixels
#define DELAYVAL      250
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

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.clear(); // Set all pixel colors to 'off'
}

void loop(void)
{
    // Run selected way of setting the NeoPixel's color
    gLedControlFuncs[gCurrentLedFuncIdx](gCurrentIteration);
    gCurrentIteration++;
    for(int i = 0; i < NUMPIXELS; i++)
    {         
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
        pixels.show();   // Send the updated pixel colors to the hardware.
    }

    // TODO make control functions returning the delay
    delay(DELAYVAL);
}
