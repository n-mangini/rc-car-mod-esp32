#include <Arduino.h>

int LDR_Val = 0;
int sensor = 13;
int led = 12;

// selectora 3 posiciones
const int switch_pos1 = 35;
const int switch_pos2 = 32;

void setup()
{
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    // switch 3 posiciones
    pinMode(switch_pos1, INPUT_PULLUP);
    pinMode(switch_pos2, INPUT_PULLUP);
}

void checkAutomaticLights()
{
    if (LDR_Val > 100)
    {
        Serial.println(" High intensity: ");
        Serial.println(LDR_Val);
        digitalWrite(led, LOW);
    }
    else
    {
        Serial.println("LOW Intensity ");
        Serial.println(LDR_Val);
        digitalWrite(led, HIGH);
    }
    delay(1000);
}

void turnOnLights()
{
    Serial.println("MANUAL ON");
    digitalWrite(led, HIGH);
}

void turnOffLights()
{
    Serial.println("MANUAL OFF");
    digitalWrite(led, LOW);
}

void controlLights()
{
    //turn on 
    if (digitalRead(switch_pos1) == LOW)
        turnOnLights();
    else if (digitalRead(switch_pos1) == HIGH && digitalRead(switch_pos2) == HIGH)
        checkAutomaticLights();
    else if (digitalRead(switch_pos2) == LOW)
        turnOffLights();
}

void loop()
{
    LDR_Val = analogRead(sensor);
    controlLights();
}
