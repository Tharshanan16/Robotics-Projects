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

int MotorSpeed =180;


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
  distance =getDistance();

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




  //                              Other Functions


  // Ultra sonic sensor distance function

  int                             


























}
