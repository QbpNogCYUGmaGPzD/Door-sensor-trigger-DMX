/*
 * Tutorial 5: Ultrasonic Range Finder
 * 
 * Prints the distance measured from the
 * range finder over serial. Place the board on your desk
 * and open up the serial monitor. Move an object in front of the
 * ultrasonic sensor and you'll see the distance to the object
 * printed out over serial.
 *
 * The circuit:
 * - 5v, ground connected to Ultrasonic sensor
 * - digital pin 4 conneceted to Ultrasonic sensor echo pin
 * - digital pin 5 conneceted to Ultrasonic sensor trig pin
 *
 * created 3 Nov 2008
 * by David A. Mellis
 * modified 30 Aug 2011
 * by Tom Igoe
 * modified 14 August 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://www.arduino.cc/en/Tutorial/Ping
 *
 */
// include the library
#include <LiquidCrystal.h>

// all of our LCD pins
int lcdRSPin = 7;
int lcdEPin = 6;
int lcdD4Pin = 5;
int lcdD5Pin = 4;
int lcdD6Pin = 3;
int lcdD7Pin = 2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(lcdRSPin, lcdEPin,
                  lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

int person = 0;
int temp = 0;

// the pins connected to the Ultrasonic sensor
int echoPin = 11;
int trigPin = 12;

void setup()
{
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);

    // set the pinmode on our ultrasonic echo, and tric pins
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

void loop()
{
    float distanceCentimeters;
    int pulseLenMicroseconds;

    // bit-bang a small square wave
    // on the trig pin to start the range
    // finder
    digitalWrite(trigPin, LOW);
    delayMicroseconds(20);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(trigPin, LOW);

    // measure the pulse length from the echo pin
    pulseLenMicroseconds = pulseIn(echoPin, HIGH);

    // calculate the distance using the speed of sound
    distanceCentimeters = pulseLenMicroseconds / 29/ 2;

    lcd.setCursor(6, 0);
    
    // print it out over serial
    lcd.print(distanceCentimeters);
    lcd.print(" ");
    
    if (distanceCentimeters < 60 && temp == 0) {person++; temp = 1;}
    if (distanceCentimeters > 60 && temp == 1) {temp = 0;}
    
    lcd.setCursor(7, 1);
    if (person < 10) {lcd.print("0");}
    lcd.print(person);

    delay(10);
}
