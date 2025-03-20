#include <Arduino.h>
#include <IRremote.h>

// Baud rate
#define BAUD_RATE 9600

// INFRARED 
#define IR_RECV_PIN 12
IRRawDataType receivedData;

// CAR ACTION CONTROL IR CODES
#define IR_LEFT_CODE 0xF30CFF00
#define IR_FORWARD_CODE 0xE718FF00
#define IR_RIGHT_CODE 0xA15EFF00
#define IR_BRAKE_CODE 0xE916FF00
#define IR_RESET_SIGNAL 0x0

// MOTOR A PINS
#define ENA  9
#define IN1A 8
#define IN2A 7

void setup() 
{
  Serial.begin(BAUD_RATE);

  // IR setup
  IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);

  // Set motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1A, OUTPUT);
  pinMode(IN2A, OUTPUT);

  // Turn off motors
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
}

void driveForward()
{
  // Set motor A speed
  analogWrite(ENA, 128);
  // Turn on motor A
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
}

void brake()
{
  // Set motor A speed to 0
  analogWrite(ENA,0);

  // Turn off motor A
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
}

void loop() 
{
  if(IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data

    receivedData = IrReceiver.decodedIRData.decodedRawData;
    switch(receivedData)
    {
      case IR_FORWARD_CODE:
        driveForward();
        break;
      case IR_BRAKE_CODE:
        brake();
      default:
        // Brake if something goes wrong.
        Serial.println("Something went wrong");
        brake();
        break;
    }
    IrReceiver.resume();
  }
}
