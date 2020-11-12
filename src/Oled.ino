#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); //sets to correct type of oled screen

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x71); // TCA9548A address is 0x70
  Wire.write(1 << bus);         // send byte to select bus
  Wire.endTransmission();
}

void hello(void)
{
  Wire.begin();
  u8g2.begin();
  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  u8g2.drawStr(25, 10, "Hello World!"); // write something to the internal memory
  u8g2.sendBuffer();                    // transfer internal memory to the display
}

void setup()
{
  Wire.begin();
  u8g2.begin();
  TCA9548A(0); // tell the TCA9548A we want to use I2C bus number zero (to talk to the OLED)
  hello();     // clear the internal memory
  TCA9548A(1);
  hello();
  TCA9548A(2);
  hello();
  TCA9548A(3);
  hello();
  TCA9548A(4);
  hello();
  TCA9548A(5);
  hello();
  TCA9548A(6);
  hello();
}

void loop()
{
}
