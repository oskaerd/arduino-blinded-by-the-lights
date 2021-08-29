

void AnalogKnobs(uint8_t adjust)
{
  const uint8_t inertia = 6;
          red = analogRead(RED_PIN) / 6;
        if (red <= inertia)
          red = 0;
        green = analogRead(GRN_PIN) / 6;
        if (green <= inertia)
          green = 0;
        blue = analogRead(BLU_PIN) / 6;
        if (blue <= inertia)
          blue = 0;
}

void SinusLeds(uint8_t color)
{
    red = sinus_vals[(color+A_HALF)%NUM_SAMPLES];
    blue = sinus_vals[color];
}
