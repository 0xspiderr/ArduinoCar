#include <Arduino.h>
#include <IRremote.h>

// BAUD RATE
#define BAUD_RATE 9600

// INFRARED 
#define IR_RECV_PIN 12
IRRawDataType receivedData;

// CAR ACTION CONTROL IR CODES
#define IR_LEFT_CODE 0xF30CFF00           // button 1 on remote
#define IR_FORWARD_CODE 0xE718FF00        // button 2 on remote
#define IR_BACKWARDS_CODE 0xE31CFF00      // button 5 on remote
#define IR_RIGHT_CODE 0xA15EFF00          // button 3 on remote
#define IR_BRAKE_CODE 0xE916FF00          // button ch+ on remote
#define IR_SPEED_INC_CODE 0xEA15FF00      // button '+' on remote
#define IR_SPEED_DEC_CODE 0xf807FF00      // button '-' on remote
#define IR_RESET_SIGNAL 0x0

// MOTOR A PINS
#define ENA  10
#define IN1A 9
#define IN2A 8
// MOTOR B PINS
#define ENB 5
#define IN3B 6
#define IN4B 7

#define MAX_SPEED 255

byte carSpeed = 128;
byte steerSpeed = 128;

void setup() 
{
  Serial.begin(BAUD_RATE);

  // IR setup
  IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);

  // Set motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1A, OUTPUT);
  pinMode(IN2A, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3B, OUTPUT);
  pinMode(IN4B, OUTPUT);

  // Turn off motors
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
  digitalWrite(IN3B, LOW);
  digitalWrite(IN4B, LOW);
}

void driveForward()
{
  // Set motor A speed
  analogWrite(ENA, carSpeed);
  // Turn on motor A
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
  // Set motor B speed
  analogWrite(ENB, carSpeed);
  // Turn on motor B
  digitalWrite(IN3B, HIGH);
  digitalWrite(IN4B, LOW);
}

/*
void increaseSpeed()
{
  if(carSpeed < MAX_SPEED && steerSpeed < MAX_SPEED)
  {
    carSpeed <<= 1;
    steerSpeed <<= 1;
  }
  Serial.println(carSpeed);
  Serial.println(steerSpeed);
}

void decreaseSpeed()
{
  if(carSpeed > 0 && steerSpeed > 0)
  {
    carSpeed >>= 1;
    steerSpeed >>= 1;
  }
  Serial.println(carSpeed);
  Serial.println(steerSpeed);
}
*/

void driveBackwards()
{
  // Set motor A speed
  analogWrite(ENA, carSpeed);
  // Turn on motor A
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, HIGH);
  // Set motor B speed
  analogWrite(ENB, carSpeed);
  // Turn on motor B
  digitalWrite(IN3B, LOW);
  digitalWrite(IN4B, HIGH);
}

void steerRight()
{
  // Set motor A speed
  analogWrite(ENA, steerSpeed);
  // Turn on motor A
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
  // Set motor B speed
  analogWrite(ENB, 0);
  // Turn off motor B
  digitalWrite(IN3B, LOW);
  digitalWrite(IN4B, LOW);
}

void steerLeft()
{
  // Set motor A speed
  analogWrite(ENA, 0);
  // Turn off motor A
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
  // Set motor B speed
  analogWrite(ENB, steerSpeed);
  // Turn off motor B
  digitalWrite(IN3B, HIGH);
  digitalWrite(IN4B, LOW);
}

// Turn off motors
void brake()
{
  // Set motor A speed to 0
  analogWrite(ENA,0);
  // Turn off motor A
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
  // Set motor B speed to 0
  analogWrite(ENB, 0);
  // Turn off motor B
  digitalWrite(IN3B, LOW);
  digitalWrite(IN4B, LOW);
}

void loop() 
{
  if(IrReceiver.decode())
  {
    // IR debugging lines
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    
    receivedData = IrReceiver.decodedIRData.decodedRawData;
    switch(receivedData)
    {
      case IR_FORWARD_CODE:
        driveForward();
        break;
      case IR_BACKWARDS_CODE:
        driveBackwards();
        break;
      case IR_LEFT_CODE:
        steerLeft();
        break;
      case IR_RIGHT_CODE:
        steerRight();
        break;
      case IR_BRAKE_CODE:
        brake();
        break;
      /*
      case IR_SPEED_INC_CODE:
        increaseSpeed();
        break;
      case IR_SPEED_DEC_CODE:
        decreaseSpeed();
        break;
      */
      default:
        // Brake if something goes wrong.
        Serial.println("Something went wrong");
        brake();
        break;
    }
    IrReceiver.resume();
  }
}