//Library untuk frekuensi
#include <PWM.h>
#include <Logger.h>
#include <Arduino.h>
#include <TimerOne.h>

//Library untuk RTC
#include <Wire.h>
#include <DS1307RTC.h>

#define ENA 12 //Input l298n (mengatur IN1)
#define IN1 11 //Input l298n (mengatur IN3)
#define ENB 8 //output A
#define IN3 9 //output B

long frequency = 0; //khz (ultrasonik)
const int dutyCycle = 50; //50%
tmElements_t tm;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);

  // Initialize timers excluding TIMER0
  InitTimersSafe();

  // pinMode(IN1, OUTPUT);
  // pinMode(IN3, OUTPUT);
  // pinMode(ENB, OUTPUT);
  // pinMode(ENA, OUTPUT);

  // Set PWM frequency and duty cycle
  // SetPinFrequencySafe(IN1, frequency);
  // SetPinFrequencySafe(IN3, frequency);
  // SetPinFrequencySafe(ENA, frequency);
  // SetPinFrequencySafe(ENB, frequency);
}

void loop() {
  getCurrentTime();
  //directionControl(frequency);
  delay(1000);
}

void getCurrentTime(){
  if (RTC.read(tm)) {
    String current_time = print2digits(tm.Hour) + ":" + print2digits(tm.Minute) + ":" + print2digits(tm.Second);
    Serial.println("Waktu : " + current_time);

    if (tm.Hour < 18) {
      Serial.println("Frekuensi Untuk Burung");
      frequency = 40000;
      Serial.println(frequency);
    } else {
      Serial.println("Frekuensi Untuk Tikus");
      frequency = 50000;
      Serial.println(frequency);
    }

  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void directionControl(long frequency) {
  Serial.print("PWM frequency set to ");
  Serial.print(frequency);
  Serial.print(" Hz with duty cycle ");
  Serial.print(dutyCycle);
  Serial.println("%.");
  Serial.print("pin :");

  //output
  tone(IN1, frequency);
  tone(IN3, frequency);

  //Turn Off motor A & B
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW); 

  // Turn on motor A & B
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

String print2digits(int number) {
  if (number >= 0 && number < 10) {
    return "0" + String(number);
  } else {
    return String(number);
  }
}
