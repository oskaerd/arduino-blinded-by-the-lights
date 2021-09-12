const uint8_t sinus_vals[] = {
    123, 130, 138, 146, 153,
    161, 168, 175, 182, 189,
    195, 201, 207, 212, 218,
    222, 227, 230, 234, 237,
    239, 242, 243, 244, 245,
    245, 245, 244, 242, 241,
    238, 235, 232, 229, 224,
    220, 215, 210, 204, 198,
    192, 185, 179, 172, 164,
    157, 149, 142, 134, 126,
    119, 111, 103, 96, 88,
    81, 73, 66, 60, 53,
    47, 41, 35, 30, 25,
    21, 16, 13, 10, 7,
    4, 3, 1, 0, 0,
    0, 1, 2, 3, 6,
    8, 11, 15, 18, 23,
    27, 33, 38, 44, 50,
    56, 63, 70, 77, 84,
    92, 99, 107, 115, 122,
};

#define NUM_SAMPLES   sizeof(sinus_vals)
#define ONE_QUATER    (NUM_SAMPLES / 4)
#define ONE_THIRD     (NUM_SAMPLES / 3)
#define A_HALF        (NUM_SAMPLES / 2)

#define DELAY_MIN         20
#define DELAY_MAX         250
#define DELAY_CTRL_RANGE  ((uint32_t)(DELAY_MAX - DELAY_MIN))
#define ADC_MAX           1023


u32 SinusLeds(uint32_t mainLoopIteration)
{
    uint32_t color = mainLoopIteration % NUM_SAMPLES;
    uint32_t delayVal = (DELAY_MIN + ((DELAY_CTRL_RANGE * analogRead(BLU_PIN)) / ADC_MAX));

    red = sinus_vals[(color+A_HALF) % NUM_SAMPLES];
    blue = sinus_vals[color];

    return delayVal;
}
