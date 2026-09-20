//include the servo library
#include <Servo.h>

//Set the servo Angle
int servoAngle=90;

// Creates a servo object for controlling the servo motor
Servo myServo; 

//Define the PWM pin  which attached to Servo
int servoPin=9;



//Defines Trig and Echo pins of the UltraSonic Sensor
const int trigPin =10;
const int echoPin =11;



//Left two motors
int pwmA= 5;
int in1A=3;
int in2A=4;

//Right two motors
int pwmB=6;
int in1B=7;
int in2B=8;

//Standby
const int STBY=2;

//MotorSpeed values

int motorSpeed =180;


          //                           Main Function

void setup() {

 // Ultra sonic 
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  //Setup the pin for the Servo
  myServo.write(90);
  myServo.attach(servoPin);

// Set all the motor control pins to outputs
  pinMode(pwmA,OUTPUT);
  pinMode(in1A,OUTPUT);
  pinMode(in2A,OUTPUT);

  pinMode(pwmB,OUTPUT);
  pinMode(in1B,OUTPUT);
  pinMode(in2B,OUTPUT);

// TB6612FNG standby
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  Serial.begin(9600);

  stopMotors();

  delay(1000);


}

void loop() {

  // Look stright
  myServo.write(90);
  delay(200);

  //Measure Distance
  int distance =getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");



  //If there no Obstacle

  if (distance>20){
    moveForward();
  }

  //If there Obstacle

  else {
    stopMotors();
    delay(300);
  
    //Check left
    
    myServo.write(180);
    delay(500);

    int leftDistance = getDistance();

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.println(" cm");

    //Check Right

    myServo.write(0);
    delay(500);

    int rightDistance = getDistance();

    Serial.print("Right : ");
    Serial.print(rightDistance);
    Serial.println(" cm");
    
    // return servo to center
    myServo.write(90);
    delay(300);

    // Decide direction
    if(leftDistance>rightDistance){
      turnLeft();
      delay(600);
    }

    else {
      turnRight();
      delay(600);
    }

    stopMotors();
    delay(200);

  }

}




  //                              Other Functions


  // Ultra sonic sensor distance function

  int getDistance(){
    
    //Make sure trigger starts LOW
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send 10 microsecond pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    //Measure echo
    int duration = pulseIn(echoPin, HIGH,30000);

    //If no echo received
    if(duration ==0){
      return 400;
    }

    //calculate distance
    int calculatedDistance = duration * 0.034 /2;
    return calculatedDistance;
  }                            


  //Move Forward

  void moveForward(){

    //left side forward
    digitalWrite(in1A,HIGH);
    digitalWrite(in2A,LOW);

    //right side forward
    digitalWrite(in1B,HIGH);
    digitalWrite(in2B,LOW);

    //Motor speed
    analogWrite(pwmA,motorSpeed);
    analogWrite(pwmB,motorSpeed);
  }

  //Stop Motors
  
  void stopMotors(){

    //Set Motorspeed to 0
    analogWrite(pwmA,0);
    analogWrite(pwmB,0);

    // Stop left side
    digitalWrite(in1A,LOW);
    digitalWrite(in2A,LOW);

    // stop right side
    digitalWrite(in1B,LOW);
    digitalWrite(in2B,LOW);

  }


  //Turn left

   void turnLeft(){

    //left side backward
    digitalWrite(in1A,LOW);
    digitalWrite(in2A,HIGH);

    //right side forward
    digitalWrite(in1B,HIGH);
    digitalWrite(in2B,LOW);

    //Motor speed
    analogWrite(pwmA,motorSpeed);
    analogWrite(pwmB,motorSpeed);
  }


  //Turn Right

   void turnRight(){

    //left side forward
    digitalWrite(in1A,HIGH);
    digitalWrite(in2A,LOW);

    //right side forward
    digitalWrite(in1B,LOW);
    digitalWrite(in2B,HIGH);

    //Motor speed
    analogWrite(pwmA,motorSpeed);
    analogWrite(pwmB,motorSpeed);
  }
























