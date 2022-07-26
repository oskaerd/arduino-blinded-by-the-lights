// todo get few sinuses for different amplitudes
const uint8_t sinus_vals[] = {
    85, 90, 96, 101, 106,     
    112, 117, 122, 126, 131,  
    135, 140, 144, 147, 151,  
    154, 157, 160, 162, 164,  
    166, 168, 169, 169, 170,  
    170, 170, 169, 168, 167,  
    165, 163, 161, 159, 156,  
    153, 149, 146, 142, 138,  
    133, 129, 124, 119, 114,  
    109, 104, 98, 93, 88,     
    82, 77, 72, 66, 61,       
    56, 51, 46, 41, 37,       
    32, 28, 24, 21, 17,       
    14, 11, 9, 7, 5,
    3, 2, 1, 0, 0,
    0, 1, 1, 2, 4,
    6, 8, 10, 13, 16,
    19, 23, 26, 30, 35,
    39, 44, 48, 53, 58,
    64, 69, 74, 80, 85,
};

#define NUM_SAMPLES   sizeof(sinus_vals)
#define ONE_QUATER    (NUM_SAMPLES / 4)
#define ONE_THIRD     (NUM_SAMPLES / 3)
#define A_HALF        (NUM_SAMPLES / 2)

#define DELAY_PIN         A0
#define PHASE_PIN         A1
#define GREEN_PIN         A3

#define DELAY_MIN         20
#define DELAY_MAX         250
#define DELAY_CTRL_RANGE  ((uint32_t)(DELAY_MAX - DELAY_MIN))
#define ADC_MAX           1023

// todo move and remove
#define ADC_READ_MASK       (~(0x7))

u32 SinusLeds(uint32_t mainLoopIteration)
{
    uint32_t color = mainLoopIteration % NUM_SAMPLES;
    uint32_t delayVal = (DELAY_MIN + ((DELAY_CTRL_RANGE * analogRead(DELAY_PIN)) / ADC_MAX));

    uint32_t phase = (A_HALF + ((analogRead(PHASE_PIN) * ((uint32_t)NUM_SAMPLES)) / ADC_MAX)) % NUM_SAMPLES;

    red = sinus_vals[(color + phase) % NUM_SAMPLES];
    blue = sinus_vals[color];
    green = (analogRead(GREEN_PIN) & ADC_READ_MASK) >> 2;

    return delayVal;
}
