#include <Arduino.h>

int ldrStatus = 0;
int ldrPin = 13;
int ligthsPin = 12;

// selectora 3 posiciones
const int switchPos1 = 33;
const int switchPos2 = 32;

void setup()
{
    Serial.begin(115200);
    pinMode(ligthsPin, OUTPUT);
    // switch 3 posiciones
    pinMode(switchPos1, INPUT_PULLUP);
    pinMode(switchPos2, INPUT_PULLUP);
}

void checkAutomaticLights()
{
    ldrStatus = analogRead(ldrPin);
    if (ldrStatus > 100)
    {
        Serial.println(" HIGH intensity: ");
        Serial.println(ldrStatus);
        digitalWrite(ligthsPin, LOW);
    }
    else
    {
        Serial.println("LOW Intensity ");
        Serial.println(ldrStatus);
        digitalWrite(ligthsPin, HIGH);
    }
}

void turnOnLights()
{
    Serial.println("MANUAL ON");
    digitalWrite(ligthsPin, HIGH);
}

void turnOffLights()
{
    Serial.println("MANUAL OFF");
    digitalWrite(ligthsPin, LOW);
}

void controlLights()
{
    // turn on
    if (digitalRead(switchPos1) == LOW)
        turnOnLights();
    else if (digitalRead(switchPos1) == HIGH && digitalRead(switchPos2) == HIGH)
        checkAutomaticLights();
    else if (digitalRead(switchPos2) == LOW)
        turnOffLights();
    delay(1000);
}

void loop()
{
    controlLights();
}
