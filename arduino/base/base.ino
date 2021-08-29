// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif



// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2

#define RED_PIN A2
#define GRN_PIN A1
#define BLU_PIN A0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t red, green, blue;
uint16_t adcRead;

const uint8_t sinus_vals[] = {
    85, 90, 95, 100, 106, 
    111, 116, 121, 125, 130, 
    134, 139, 143, 146, 150, 
    153, 156, 159, 161, 164, 
    165, 167, 168, 169, 169, 
    170, 169, 169, 168, 167, 
    165, 164, 161, 159, 156, 
    153, 150, 146, 143, 139, 
    134, 130, 125, 121, 116, 
    111, 106, 100, 95, 90, 
    85, 79, 74, 69, 63, 
    58, 53, 48, 44, 39, 
    35, 30, 26, 23, 19, 
    16, 13, 10, 8, 5, 
    4, 2, 1, 0, 0, 
    0, 0, 0, 1, 2, 
    4, 5, 8, 10, 13, 
    16, 19, 23, 26, 30, 
    35, 39, 44, 48, 53, 
    58, 63, 69, 74, 79,
  };

#define NUM_SAMPLES   sizeof(sinus_vals)
#define ONE_QUATER    (NUM_SAMPLES / 4)
#define ONE_THIRD     (NUM_SAMPLES / 3)
#define A_HALF        (NUM_SAMPLES / 2)
#define UART_TIMEOUT  200
// Time (in milliseconds) to pause between pixels
#define DELAYVAL      250
#define MIN_COLOR     100
#define MAX_COLOR     170

void pokretla(uint8_t adjust)
{
  const uint8_t bezwladnosc = 6;
          red = analogRead(RED_PIN) / 6;
        if (red <= bezwladnosc)
          red = 0;
        green = analogRead(GRN_PIN) / 6;
        if (green <= bezwladnosc)
          green = 0;
        blue = analogRead(BLU_PIN) / 6;
        if (blue <= bezwladnosc)
          blue = 0;
}

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  Serial.begin(115200);
  Serial.setTimeout(UART_TIMEOUT);
  red = 100;
  blue = 100;

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop()
{
  //pixels.clear(); // Set all pixel colors to 'off'
  //for (uint8_t color = MIN_COLOR; color < MAX_COLOR; color+=5)
  for (uint8_t color = 0; color < NUM_SAMPLES; color++)
  {
        //blue = sinus_vals[color];
//         red = sinus_vals[(color+A_HALF)%NUM_SAMPLES];
//         blue = sinus_vals[color];
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for(int i=0; i<NUMPIXELS; i++)
        { // For each pixel...
         
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255    
          pixels.setPixelColor(i, pixels.Color(red, green, blue));
      
          pixels.show();   // Send the updated pixel colors to the hardware.
        }

        uint8_t result[2] = {0};
        //pokretla(result);
        Serial.readBytes(result, 2);
        Serial.write(result, 2);

        if (result[0] <= 30)
        {
          red += result[0];
        }
        else
        {
            red -= (result[0] - 30);
        }

        if (result[1] <= 30)
        {
          blue += result[1];
        }
        else
        {
            blue -= (result[1] - 30);
        }

        delay(DELAYVAL); // Pause before next pass through loop
  }
}
