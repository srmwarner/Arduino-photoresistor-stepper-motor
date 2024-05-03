#include <Arduino.h>


void RotateMotor(char, int, int);           // function declaration

// define pins
const int stepPin = 12;               // stepper motor pins
const int dirPin = 11;

const int pResistor = A0;             // photoresistor at analog pin A0 (photoresistor is analog, plugging it in to this pin allows us to get a digital value from it)


// initialise variables

int lightValue = 0;             // stores value from photoresistor (0-1023)

bool hasRotatedClockwise;
bool hasRotatedCounterClockwise;


void setup() {

  // initialising every component, setting it as input/output

  pinMode(stepPin,OUTPUT);      // motor is an output 
  pinMode(dirPin,OUTPUT);

  pinMode(pResistor, INPUT);    // photoresistor is an input

}

void loop() {

  lightValue = analogRead(pResistor);       // checks the value on the photoresistor, assigns it to lightValue variable

  if (lightValue > 500)
  {
    if (hasRotatedClockwise != true)           // condition to check if the motor has already rotated clockwise. If it has not, we can enter the code block
    {                                          // this ensures that the motor only rotates once and doesnt infitely enter this block 
      RotateMotor(HIGH, 3000, 300);            // rotate motor - clockwise, with 3000μs between steps, for 600 total steps (3 full rotations)
      hasRotatedClockwise = true;
      hasRotatedCounterClockwise = false;      // set hasRotatedClockwise to true as we have just rotated clockwise, and set hasRotatedCounterClockwise to false as we have not done that
    }
  }
  else
  {
    if (hasRotatedCounterClockwise != true)
    {
      RotateMotor(LOW, 3000, 300);              // rotate motor - anticlockwise, with 3000μs between steps, for 600 total steps (3 full rotations) 
      hasRotatedCounterClockwise = true;
      hasRotatedClockwise = false;              
    }
  }

  delay(1200000);                           // delay for 20 minutes so that the arduino is not executing code constantly (battery saving)

}



void RotateMotor(char direction, int speed, int runtime)
{
  // direction - user inputs HIGH or LOW for direction parameter. HIGH = clockwise, LOW = anticlockwise

  // speed = delay (in microseconds) between steps (higher delay = slower rotation, lower delay = faster rotation)

  // runtime = the total number of steps the motor does (i < runtime in the for loop) 

 
  digitalWrite(dirPin, direction);      // enables clockwise or anticlockwise movement depending on whether user inputted HIGH or LOW for the direction parameter        
 

  for (int i = 0; i < runtime; i++)
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(speed);            // delay between steps (changes rotation speed)
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(speed); 
  }

}
