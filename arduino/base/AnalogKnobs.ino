uint32_t AnalogKnobs(uint32_t adjust)
{
    const uint8_t inertia = 6;
    uint16_t adcRead;

    red = analogRead(RED_PIN) / 6;
    if (red <= inertia)
        red = 0;

    green = analogRead(GRN_PIN) / 6;
    if (green <= inertia)
        green = 0;

    blue = analogRead(BLU_PIN) / 6;
    if (blue <= inertia)
        blue = 0;

    return DELAYVAL;
}
