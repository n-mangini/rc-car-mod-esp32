#include <Arduino.h>

int traccionAdelante = 25;
int traccionAtras = 26;
int direccionIzq = 33;
int direccionDer = 32;

void setup()
{
    Serial.begin(115200);
    pinMode(traccionAdelante, OUTPUT);
    pinMode(traccionAtras, OUTPUT);
    pinMode(direccionIzq, OUTPUT);
    pinMode(direccionDer, OUTPUT);
}

void loop()
{
    // adelante
    digitalWrite(traccionAdelante, HIGH);
    digitalWrite(traccionAtras, LOW);
    Serial.println("adelante");
    delay(500);

    // stop traccion
    digitalWrite(traccionAdelante, LOW);
    digitalWrite(traccionAtras, LOW);
    delay(500);

    // atras
    digitalWrite(traccionAdelante, LOW);
    digitalWrite(traccionAtras, HIGH);
    Serial.println("atras");
    delay(500);

    // stop traccion
    digitalWrite(traccionAdelante, LOW);
    digitalWrite(traccionAtras, LOW);
    delay(500);

    // izquierda
    digitalWrite(direccionIzq, HIGH);
    digitalWrite(direccionDer, LOW);
    Serial.println("izquierda");
    delay(500);

    // stop direccion
    digitalWrite(direccionIzq, LOW);
    digitalWrite(direccionDer, LOW);
    delay(500);

    // derecha
    digitalWrite(direccionIzq, LOW);
    digitalWrite(direccionDer, HIGH);
    Serial.println("derecha");
    delay(500);

    // stop direccion
    digitalWrite(direccionIzq, LOW);
    digitalWrite(direccionDer, LOW);
    delay(500);
}