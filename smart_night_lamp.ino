#include <Servo.h>

int buttonState = 0;
int buttonState_tm1 = 0;

const int buttonPin = 0;
const int ledPinRed = 6;
const int ledPinBlue = 5;
const int ledPinGreen = 3;
const int servoMotorPin = 9;

int valLedRed = 0;
int valLedGreen = 0;
int valLedBlue = 0;

int pwmRed = 0;
int pwmGreen = 0;
int pwmBlue = 0;

int valPotentiometer = 0;
int cmdPosServo = 0;

int _max_pwm_val = 100;

Servo myservo;

void setup() {
  pinMode(buttonPin, INPUT);
  myservo.attach(servoMotorPin);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  valPotentiometer = analogRead(A0);
  
  if(buttonState > buttonState_tm1){
    delay(200);
    valLedRed = random(_max_pwm_val);
    valLedGreen = random(_max_pwm_val);
    valLedBlue = random(_max_pwm_val);
  }

  cmdPosServo = map(valPotentiometer, 0, 1023, 0, 180);
  valPotentiometer = map(valPotentiometer, 0, 1023, 0, _max_pwm_val);

  pwmRed = (int) constrain(valLedRed + (valPotentiometer - _max_pwm_val/2.0), 0.0, _max_pwm_val);
  pwmGreen = (int) constrain(valLedGreen + (valPotentiometer - _max_pwm_val/2.0), 0, _max_pwm_val);
  pwmBlue = (int) constrain(valLedBlue + (valPotentiometer - _max_pwm_val/2.0), 0, _max_pwm_val);
    
  changeColor(pwmRed, pwmGreen, pwmBlue);
  myservo.write(cmdPosServo);
  
  buttonState_tm1 = buttonState;
  delay(15);
}

void changeColor(int red, int green, int blue){
  analogWrite(ledPinRed, red);
  analogWrite(ledPinGreen, green);
  analogWrite(ledPinBlue, blue);
}
