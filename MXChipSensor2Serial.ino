/* 
 *  Add support for MXChip to Arduino IDE
 *  
 *  File -> Preferences
 *  Additional Boards Manager URLs
 *  https://raw.githubusercontent.com/VSChina/azureiotdevkit_tools/master/package_azureboard_index.json
 *  
 *  Tools -> Board -> Boards Manager
 *  Install MXChip support
 *  
 *  
 *  MXChip board documentation
 *  https://microsoft.github.io/azure-iot-developer-kit/docs/get-started/
 *  
 */

#include "HTS221Sensor.h"
#include <OledDisplay.h>


DevI2C *i2c;
HTS221Sensor *sensor;
float humidity = 0;
float temperature = 0;
unsigned char id;


void setup() {
  // Hardware initialization
  Screen.init();

  i2c = new DevI2C(D14, D15);
  sensor = new HTS221Sensor(*i2c);

  sensor -> init(NULL);
}

void loop() {
  // enable
  sensor -> enable();
  
  // Get temperature
  sensor -> getTemperature(&temperature);
  Serial.print(temperature);
  
  Serial.print(";");

  // Get humidity
  sensor -> getHumidity(&humidity);
  Serial.println(humidity);
  
  // disable the sensor
  sensor -> disable();
  // reset
  sensor -> reset();

  char buf[100];
  sprintf(buf, "H: %.1f\nT: %.1f", humidity, temperature);
  Screen.print(buf, true);
  delay(1000);
}
