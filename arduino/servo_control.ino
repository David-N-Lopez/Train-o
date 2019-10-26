#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position
int x;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}
 
void loop() {
  while (Serial.available() > 0) {
    delay(10);
    x = Serial.read();
    int end_angle = 100;
    int begin_angle = 38;
    
    for (pos = begin_angle; pos <= end_angle; pos += 1) {
      myservo.write(pos);
      delay(15); 
    }
    for (pos = end_angle; pos >= begin_angle; pos -= 1) { 
      myservo.write(pos);
      delay(15); 
    }                               
  }
}