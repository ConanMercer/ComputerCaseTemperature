// --- Libraries
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h> // Library to communicate with IR sensors

// --- Variables and settings
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
Adafruit_MLX90614 IR_1 = Adafruit_MLX90614(0x5A); // MLX90614 address is 0x5A
double TEMP;
static char outstr[15];

// --- Voids
void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x71); // TCA9548A address is 0x71
  Wire.write(1 << bus);         // send byte to select bus
  Wire.endTransmission();
}

void temp(void)
{
  TEMP = IR_1.readObjectTempC();                    // store temp in a double
  u8g2.clearBuffer();                               // clear the internal memory
  u8g2.drawStr(0, 50, dtostrf(TEMP, 5, 1, outstr)); // convert double to string
  u8g2.drawStr(80, 50, "\xb0");                     // hex code for degrees celsius
  u8g2.drawStr(84, 50, " C");
  u8g2.sendBuffer(); // transfer internal memory to the display
}

void description(void)
{
  Wire.begin();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.drawStr(10, 10, "Infrared Temperature");
  u8g2.drawStr(10, 30, "Sensing");
  u8g2.drawStr(10, 50, "Platform");
  u8g2.sendBuffer();
}

void setup()
{
  u8g2.setBusClock(100000);           // set I2C to 100KHz so it is compatable with MLX90614
  u8g2.begin();                       // Initialise OLED screens
  IR_1.begin();                       // Initialise IR sensor
  u8g2.setFont(u8g2_font_helvR24_tf); // choose a suitable font
}

void loop()
{
  TCA9548A(1);
  temp();
  delay(1000);
}
