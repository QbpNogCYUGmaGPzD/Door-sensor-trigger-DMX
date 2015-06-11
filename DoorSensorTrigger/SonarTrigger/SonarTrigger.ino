// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 3 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// # Pin mode: PWM
// # Working Mode: PWM passive control mode.

int URPWM = 3;                                      // PWM Output 0-25000us,every 50us represent 1cm
int URTRIG = 5;                                     // PWM trigger pin
boolean up = true;                                  // create a boolean variable
unsigned long time;                                 // create a time variable
unsigned long urmTimer = 0;                          // timer for managing the sensor reading flash rate

unsigned int Distance = 0;
uint8_t EnPwmCmd[4] = {0x44, 0x22, 0xbb, 0x01};     // distance measure command

int sensorReading = 0;      // variable to store the value read from the sensor pin

const int distanceSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 50;  // threshold value to decide when the detected distance is a visitor or not

boolean visitorEnter = false; //by default there is no vistor inside

void setup() {                                     // Serial initialization
  Serial.begin(9600);                              // Sets the baud rate to 9600
  PWM_Mode_Setup();
}

void loop()
{
  //Start PWM Seq
  if (millis() - urmTimer > 50) {
    urmTimer = millis();
    PWM_Mode();
  }
  
  //Check when visitor passes the sensor
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(distanceSensor);    
  
  // if the sensor reading is greater than the threshold:
  if (sensorReading <= threshold) {
    
    
    
    
    // send the string "Visitor!" back to the computer, followed by newline
    Serial.println("Vistor!");         
  }
}

void PWM_Mode_Setup() {
  pinMode(URTRIG, OUTPUT);                           // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);                        // Set to HIGH

  pinMode(URPWM, INPUT);                             // Sending Enable PWM mode command

  for (int i = 0; i < 4; i++) {
    Serial.write(EnPwmCmd[i]);
  }
}

void PWM_Mode() {                                    // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);                      // reading Pin PWM will output pulses

  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);

  if (DistanceMeasured == 50000) {                 // the reading is invalid.
    Serial.print("Invalid");
  }
  else {
    Distance = DistanceMeasured / 50;              // every 50us low level stands for 1cm
  }
  Serial.print("Distance=");
  Serial.print(Distance);
  Serial.println("cm");
}
