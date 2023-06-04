#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <wifi_data.h>
#include <webpage.html>

const int ENA = 13;
const int IN1 = 12;
const int IN2 = 14;

const int IN3 = 27;
const int IN4 = 26;
const int ENB = 25;

int SPEED = 255;
const int SPEED_MAX = 255;

const int REVERSE_LED = 33;
const int LUCES_BAJAS = 32;

WebServer server(80);

void handleRoot()
{
  server.send(200, "text/html", webpage);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("WifiCar"))
  {
    Serial.println("MDNS Responder Started");
  }
}

void setup(void)
{
  Serial.begin(SERIAL_BAUD);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(REVERSE_LED, OUTPUT);
  pinMode(LUCES_BAJAS, OUTPUT);
  handleWifi();

  server.on("/", handleRoot);
  server.on("/forward", []()
            {
    Serial.println("forward");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, SPEED);
    server.send(200, "text/plain", "forward"); });

  server.on("/driveStop", []()
            {
    Serial.println("driveStop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(REVERSE_LED, LOW);
    server.send(200, "text/plain", "driveStop"); });

  server.on("/back", []()
            {
    Serial.println("back");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, SPEED);
    digitalWrite(REVERSE_LED, HIGH);
    server.send(200, "text/plain", "back"); });

  server.on("/right", []()
            {
    Serial.println("right");
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, SPEED_MAX);
    server.send(200, "text/plain", "right"); });

  server.on("/left", []()
            {
    Serial.println("left");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); 
    analogWrite(ENB, SPEED_MAX);
    server.send(200, "text/plain", "left"); });

  server.on("/steerStop", []()
            {
    Serial.println("steerStop");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW); 
    analogWrite(ENB, 0);
    server.send(200, "text/plain", "steerStop"); });

  server.on("/LightsOn", []()
            {
    Serial.println("LIGHTS MANUAL ON");
    digitalWrite(LUCES_BAJAS, HIGH);
    server.send(200, "text/plain", "Luces encendidas"); });

  server.on("/LightsOff", []()
            {
    Serial.println("LIGHTS MANUAL OFF");
    digitalWrite(LUCES_BAJAS, LOW);
    server.send(200, "text/plain", "Luces apagadas"); });

  server.on("/changeSpeed", []()
            {
  String speedValue = server.arg("speed");
  Serial.println("Speed changed to " + speedValue);
  SPEED = speedValue.toInt();
  server.send(200, "text/plain", "Speed Changed"); });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  server.handleClient();
}