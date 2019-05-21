#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include "Arduino.h"

#include "VernierLib.h"

#define SENSOR_NUM 5
#define MEASURE_NUM 10
VernierLib Vernier;
float sensorReading;
float Eo = 252.72; //Enter the values from your calibration here
// void printSensorInfo();
float pin[SENSOR_NUM] = {A0, A1, A2, A3, A5};
float sum[SENSOR_NUM], min[SENSOR_NUM], max[SENSOR_NUM], rawCount[SENSOR_NUM],
    voltage[SENSOR_NUM], value[SENSOR_NUM][MEASURE_NUM];

void printDigits(int digits);
void showCurrentTime();
void setCurrentTime(int year, int month, int day, int hour, int minute, int second);
void setup()
{
  Serial.begin(9600);
  setSyncProvider(RTC.get);
  setCurrentTime(19, 5, 21, 17, 0, 2);
  while (timeStatus() != timeSet)
    ;
}

void loop()
{
  // sensorReading = Vernier.readSensor();
  showCurrentTime();
  Serial.print(",");
  memset(value, 0, sizeof(value));
  for (int i = 0; i < SENSOR_NUM; i++)
  {
    sum[i] = 0.0;
    min[i] = 1024;
    max[i] = -1;
    voltage[i] = 0;
    rawCount[i] = 0;
  }

  for (int i = 0; i < SENSOR_NUM; i++)
  {
    for (int j = 0; j < MEASURE_NUM; j++)
    {
      value[i][j] = analogRead(pin[i]);
      sum[i] += value[i][j];
      if (min[i] > value[i][j])
      {
        min[i] = value[i][j];
      }
      if (max[i] < value[i][j])
      {
        max[i] = value[i][j];
      }
    }
  }
  for (int i = 0; i < SENSOR_NUM; i++)
  {
    sum[i] -= (min[i] + max[i]);
    rawCount[i] = (sum[i]) / (MEASURE_NUM - 2);
    voltage[i] = rawCount[i] / 1023 * 5;
    // Serial.print(i + 1);
    // Serial.print("번째 센서 값들: \t");
    // for (int j = 0; j < MEASURE_NUM; j++)
    // {
    //   Serial.print(value[i][j]);
    //   Serial.print("\t");
    // }
    // Serial.println();
  }
  // Serial.println();
  // Serial.println();
  // Serial.println();

  // for (int i = 0; i < SENSOR_NUM; i++)
  // {
  //   Serial.print(i + 1);
  //   Serial.print("번값\t");
  //   Serial.print("  ");
  // }
  // Serial.println();
  // for (int i = 0; i < SENSOR_NUM; i++)
  // {
  //   Serial.print(rawCount[i], 3);
  //   Serial.print("   ");
  // }
  // Serial.println();
  // Serial.println();
  // Serial.println();

  // for (int i = 0; i < SENSOR_NUM; i++)
  // {
  //   Serial.print(i + 1);
  //   Serial.print("번 전압");
  // }
  // Serial.println();
  for (int i = 0; i < SENSOR_NUM; i++)
  {
    if (i == 0 || i == 3)
    {
      Serial.print(voltage[i], 3);
      Serial.print(",");
    }
  }
  Serial.println();
  delay(5000);
}

void setCurrentTime(int year, int month, int day, int hour, int minute, int second)
{
  setTime(hour, minute, second, day, month, year);
}
void showCurrentTime()
{
  Serial.print(year());
  Serial.print("-");
  Serial.print(month());
  Serial.print("-");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
}

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
