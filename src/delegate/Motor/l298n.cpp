#include <Arduino.h>

//MOTOR 1
int IN1 = 26;
int IN2 = 25;
int ENA = 27;
//MOTOR 2
int IN3 = 13;
int IN4 = 12;
int ENB = 14;

void setup()
{
    Serial.begin(115200);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void loop()
{
    Serial.println("adelante");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    delay(4000);

    Serial.println("stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    delay(4000);

    Serial.println("atras");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 255);
    delay(4000);

    Serial.println("stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    delay(4000);




    Serial.println("izquierda");
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 128);
    delay(4000);

    Serial.println("stop");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    delay(4000);

    Serial.println("derecha");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, 128);
    delay(4000);

    Serial.println("stop");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    delay(4000);
}