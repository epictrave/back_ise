
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
void setup()
{
  Serial.begin(9600);
  Vernier.autoID(); // this is the routine to do the autoID
  printSensorInfo();
  Serial.println();
  Serial.println();
  Serial.println();
}

void loop()
{
  // sensorReading = Vernier.readSensor();
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
    Serial.print(i + 1);
    Serial.print("번째 센서 값들: \t");
    for (int j = 0; j < MEASURE_NUM; j++)
    {
      Serial.print(value[i][j]);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.println();
  Serial.println();
  Serial.println();

  for (int i = 0; i < SENSOR_NUM; i++)
  {
    Serial.print(i + 1);
    Serial.print("번값\t");
    Serial.print("  ");
  }
  Serial.println();
  for (int i = 0; i < SENSOR_NUM; i++)
  {
    Serial.print(rawCount[i], 3);
    Serial.print("   ");
  }
  Serial.println();
  Serial.println();
  Serial.println();

  for (int i = 0; i < SENSOR_NUM; i++)
  {
    Serial.print(i + 1);
    Serial.print("번 전압");
  }
  Serial.println();
  for (int i = 0; i < SENSOR_NUM; i++)
  {
    Serial.print(voltage[i], 3);
    Serial.print("   ");
  }
  Serial.println();
  Serial.println();
  delay(5000);
}
void printSensorInfo()
{
  // print out information about the sensor found:
  Serial.println("Sensor Information:");
  Serial.print("Sensor ID number: ");
  Serial.print("\t");
  Serial.println(Vernier.sensorNumber());
  Serial.print("Sensor Name: ");
  Serial.print("\t");
  Serial.println(Vernier.sensorName());
  Serial.print("Short Name: ");
  Serial.print("\t");
  Serial.println(Vernier.shortName());
  Serial.print("Units: ");
  Serial.print("\t");
  Serial.println(Vernier.sensorUnits());
  Serial.print("ID voltage level: ");
  Serial.print("\t");
  Serial.println(Vernier.voltageID());
  Serial.print("Page: ");
  Serial.print("\t");
  Serial.println(Vernier.page());
  Serial.print("slope: ");
  Serial.print("\t");
  Serial.println(Vernier.slope());
  Serial.print("intercept: ");
  Serial.print("\t");
  Serial.println(Vernier.intercept());
  Serial.print("cFactor:");
  Serial.print("\t");
  Serial.println(Vernier.cFactor());
  Serial.print("calEquationType: ");
  Serial.print("\t");
  Serial.println(Vernier.calEquationType());
  Serial.print("Distance: ");
  Serial.print("\t");
  Serial.println(Vernier.distance());
}