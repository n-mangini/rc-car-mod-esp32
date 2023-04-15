#include <Arduino.h>

#define TRIG 13
#define ECHO 12
#define BUZZER 14
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(BUZZER, OUTPUT);
}

void loop()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration = pulseIn(ECHO, HIGH);
    distanceCm = duration * SOUND_SPEED / 2;

    if (duration < 6000)
    {
        Serial.print("Distancia: ");
        Serial.print(distanceCm);
        Serial.print(" cm");
        Serial.println();
        int timer = (duration / 20);
        digitalWrite(BUZZER, HIGH);
        delay(timer / 2);
        digitalWrite(BUZZER, LOW);
        delay(timer);
    }
}
