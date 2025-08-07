// testing this code is possible in the Arduino IDE
// all include-files have to be added to the libraries folder within the Arduino 
#include "SdsDustSensor.h"
#include <phyphoxBle.h> 

// tested on Arduino Leonardo with Serial1
SdsDustSensor sds(Serial1); // passing HardwareSerial& as parameter

void setup() {
  Serial.begin(9600);
  sds.begin(); // this line will begin Serial1 with given baud rate (9600 by default)

  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  Serial.println(sds.setQueryReportingMode().toString()); // ensures sensor is in 'query' reporting mode
}

void loop() {
  sds.wakeup();
  delay(5000); // working 5 seconds

  PmResult pm = sds.queryPm();
  if (pm.isOk()) {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);

  } else {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }

  WorkingStateResult state = sds.sleep(); // sleep during off-time... everyone needs a break
  if (state.isWorking()) {
    Serial.println("Problem with sleeping the sensor.");
  } else {
    Serial.println("Sensor is sleeping");
    delay(5000); // wait 1 minute
  }
}
