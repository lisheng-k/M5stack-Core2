
/*
Read me: Lisheng Kuang 2022-11-28
there si sth wrong in the official code from M5stack company.
to fix the problem:
leave Wire.begin() as it is but replace Wire with Wire1 in the two 
functions Servo_write_us90() and Servo_write_angle().

Explanation: M5Core2 uses Wire1 for the internal I2C and Wire for 
the external I2C (Groove port). Wire1 is initialized in M5.begin() 
and used for the touch screen.
*/
/*
the hardware:https://docs.m5stack.com/en/module/servo

*/
/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit for more information: https://docs.m5stack.com/en/module/servo
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/module/servo
*
* Product: SERVO.
* Date: 2021/9/2
*******************************************************************************
  Use SERVO Module to control the rotation of 12-channel servo.
  使用 SERVO 模块控制 12 通道舵机的旋转。
*/

#include <Arduino.h>
#include <M5Core2.h>
#include <Wire.h>

#define SERVO_ADDR 0x53
void setup() 
{
  M5.begin(true, false, true, true, kMBusModeInput);
  /*   kMBusModeOutput,powered by USB or Battery
  kMBusModeInput,powered by outside input need to fill in this Otherwise M5Core2 will not work properly
  由外部供电时此项必填,否则M5Core2将无法正常工作 */
  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(70, 100);
  M5.Lcd.print("12 Servo Example");

  Wire.begin(32, 33, 100000UL);
}

// addr 0x01 mean control the number 1 servo by us
void Servo_write_us(uint8_t number, uint16_t us) 
{
  Wire1.beginTransmission(SERVO_ADDR);
  Wire1.write(0x00 | number);
  Wire1.write(us & 0x00ff);
  Wire1.write(us >> 8 & 0x00ff);
  Wire1.endTransmission();
}

// addr 0x11 mean control the number 1 servo by angle
void Servo_write_angle(uint8_t number, uint8_t angle) 
{
  Wire1.beginTransmission(SERVO_ADDR);
  Wire1.write(0x10 | number);
  Wire1.write(angle);
  Wire1.endTransmission();
}

void loop() 
{
  for (uint8_t i = 0; i < 12; i++) 
  {
    Servo_write_us(i, 700);
     //Servo_write_angle(i, 0);
  }
  delay(1000);
  for (uint8_t i = 0; i < 12; i++) 
  {
    Servo_write_us(i, 2300);
     //Servo_write_angle(i, 180);
  }
  delay(1000);

}
