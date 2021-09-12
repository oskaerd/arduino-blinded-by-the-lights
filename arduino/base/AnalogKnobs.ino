
#define RED_PIN             A3
#define GRN_PIN             A1
#define BLU_PIN             A0

#define ADC_READ_MASK       (~(0x7))

uint32_t AnalogKnobs(uint32_t iteration)
{
    red = (analogRead(RED_PIN) & ADC_READ_MASK) >> 2;

    green = (analogRead(GRN_PIN) & ADC_READ_MASK) >> 2;

    blue = (analogRead(BLU_PIN) & ADC_READ_MASK) >> 2;

    return DELAYVAL;
}
