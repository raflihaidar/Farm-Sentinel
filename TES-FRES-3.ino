#include <PWM.h>
#include <Logger.h>
#include <Arduino.h>
#include <TimerOne.h>

#define PIN_PWM 9
#define TRIG_PIN 5

long frequency = 0;  // 10kHz
int dutyCycle = 50;  // 50%
float time = 0.001; 
int kecepatan;

void setup() {
  // Initialize serial communication 60000 -> 2 
  
  Serial.begin(9600);
  Serial.println("Serial communication initialized.");
  // Set Timer1 in Fast PWM mode with prescaler 1

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(12, LOW);

  // Initialize timers excluding TIMER0
  InitTimersSafe();
  Serial.println("Timers initialized.");

  // Set PWM frequency and duty cycle
 
  SetPinFrequencySafe(11, frequency);  // Konversi ke Hz
  SetPinFrequencySafe(9, frequency);
  SetPinFrequencySafe(12, frequency);
  //directionControl();
  // kecepatan = map(sin(millis() * 0.001), -1, 1, 0, 255);
  // analogWrite(11, kecepatan);
  // Serial.print("kecepatan : " + kecepatan);
  // directionControl();
}

void loop() {
  directionControl();
  Serial.print("PWM frequency set to ");
  Serial.print(frequency);
  Serial.print(" Hz with duty cycle ");
  Serial.print(dutyCycle);
  Serial.println("%.");
  Serial.print("pin :");
  Serial.println(PIN_PWM);
}

void directionControl() {
  // Set motors to maximum speed
  // For PWM, maximum possible values are 0 to 255
  // analogWrite(11, kecepatan);
  tone(11, frequency);
  // pwmWrite(12, map(dutyCycle, 0, 100, 0, 4095));

  // Turn on motor A & B
  digitalWrite(12, HIGH);
  Serial.print(time);

  // delay(1000);

  // Turn off motors
  // digitalWrite(12, LOW);
}