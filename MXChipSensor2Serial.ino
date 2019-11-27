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
#include "LSM6DSLSensor.h"
#include <OledDisplay.h>


DevI2C *i2c;
HTS221Sensor *sensorTH;
LSM6DSLSensor *sensorAG;
float humidity = 0;
float temperature = 0;
unsigned char id;

int accelerometerAxes[3]; // [0]=X [1]=Y [2]=XZ
int gyroscopAxes[3]; // [0]=X [1]=Y [2]=Z


void setup() {
  // Hardware initialization
  Screen.init();

  i2c = new DevI2C(D14, D15);
  sensorTH = new HTS221Sensor(*i2c);
  sensorAG = new LSM6DSLSensor(*i2c, D4, D5);
  
  sensorTH -> init(NULL);
  sensorAG -> init(NULL);

  sensorAG->enableAccelerator();
  sensorAG->enableGyroscope();

  // enable
  sensorTH -> enable();
}

void loop() {
   sensorAG->resetStepCounter();
            sensorAG->getXAxes(accelerometerAxes);
            sensorAG->getGAxes(gyroscopAxes);

  Serial.print("{");
  Serial.printf("\"ax\":%d,\"ay\":%d,\"az\":%d", accelerometerAxes[0], accelerometerAxes[1], accelerometerAxes[2]);
  Serial.print(",");
  Serial.printf("\"gx\":%d,\"gy\":%d,\"gz\":%d", gyroscopAxes[0], gyroscopAxes[1], gyroscopAxes[2]);
  Serial.print(",");
  
  // Get temperature
  sensorTH -> getTemperature(&temperature);
  Serial.printf("\"t\":%.1f",temperature);
  Serial.print(",");

  // Get humidity
  sensorTH -> getHumidity(&humidity);
  Serial.printf("\"h\":%.1f",humidity);
  Serial.println("}");
  
  // disable the sensor
  //sensorTH -> disable();
  // reset
  //sensorTH -> reset();

  //char buf[300];
  //sprintf(buf, "H: %.1f\nT: %.1f", humidity, temperature);
  //sprintf(buf, "%d\n%d\n%d", accelerometerAxes[0], accelerometerAxes[1], accelerometerAxes[2]);
  //Screen.print(buf, true);
  delay(50);
}
