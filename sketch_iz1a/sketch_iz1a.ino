#include <MD_MAX72xx.h>
#include <SPI.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define DATA_PIN 23
#define CLK_PIN 18
#define CS_PIN 5

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const int botonPin = 15;
const int buzzerPin = 4;
const int motorVibradorPin = 14;  


byte arrow[8] = {
  B00010000,
  B00110000,
  B11111111,
  B11111111,
  B11111111,
  B00110000,
  B00010000,
  B00000000
};

void setup() {
  Serial.begin(115200);
  pinMode(botonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorVibradorPin, OUTPUT);
  
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 8); 
  mx.clear();

  digitalWrite(buzzerPin, LOW);
  digitalWrite(motorVibradorPin, LOW);

  Serial.println("Listo");
}

void loop() {
  if (digitalRead(botonPin) == HIGH)
    for (int i = 0; i < 8; i++) {
      mx.setRow(0, i, arrow[i]);
    }
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorVibradorPin, HIGH);
    Serial.println("Botón presionado");
  } else {
    mx.clear();
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorVibradorPin, LOW); 
  }

  delay(100);
}
