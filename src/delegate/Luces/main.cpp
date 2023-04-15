/* Switch toggles LED on/off */

#include <Arduino.h>

#define BUTTON_PIN 34
#define LED_PIN LED_BUILTIN

int led_state = LOW;
int button_state;
int last_button_state = HIGH;

void setup()
{
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    button_state = digitalRead(BUTTON_PIN); // read new state

    if (button_state == LOW && last_button_state == HIGH)
    {
        Serial.println("The button is pressed");
        led_state = !led_state;
        digitalWrite(LED_PIN, led_state);
    }

    last_button_state = button_state; // save last state
}
