#include <SharpIR.h>

#define ir A0
#define model 20150

int sensorValue = analogRead(A0);
int switchPin = 2;              // switch is connected to pin 2
int val;                        // variable for reading the pin status
int buttonState;                // variable to hold the last button state

SharpIR sharp(ir, 25, 93, model);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)



void setup()
{
  Serial.begin(9600);
  pinMode (ir, INPUT);
  delay(2000);  
}





void loop()
{
  delay(200);   

  int dis = sharp.distance();  // this returns the distance to the object you're measuring
  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  
  
}
  

