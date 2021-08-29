#define RED_PIN             A2
#define GRN_PIN             A1
#define BLU_PIN             A0

void AnalogKnobs(uint32_t adjust)
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
}
