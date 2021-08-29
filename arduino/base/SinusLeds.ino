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


void SinusLeds(uint32_t mainLoopIteration)
{
    // TODO add control of phase and pulse and amplitude with knobs
    uint32_t color = mainLoopIteration % NUM_SAMPLES;
    red = sinus_vals[(color+A_HALF) % NUM_SAMPLES];
    blue = sinus_vals[color];
}
