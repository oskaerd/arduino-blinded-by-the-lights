#define RGB_DATA_BYTES  4


typedef union _UartRgbData
{
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t reserved;
    } rgb;
    uint8_t raw[RGB_DATA_BYTES];
} UartRgbData;

static UartRgbData rgbData;

uint32_t SerialMusic(uint32_t iteration)
{
    Serial.readBytes(rgbData.raw, sizeof(uint32_t));

    Serial.print(rgbData.rgb.red);
    Serial.print(' ');
    Serial.print(rgbData.rgb.green);
    Serial.print(' ');
    Serial.print(rgbData.rgb.blue);
    Serial.print(' ');
    Serial.println(rgbData.rgb.reserved);

    red     = rgbData.rgb.red;
    green   = rgbData.rgb.green;
    blue    = rgbData.rgb.blue;

    return 10;
}
