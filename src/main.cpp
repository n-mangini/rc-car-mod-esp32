#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <wifi_data.h>
#include <webpage.html>

const int A1A = 26;
const int A1B = 25;
/* const int B1A = 14;
const int B1B = 27; */
const int LED = 12;

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
  //Serial.begin(SERIAL_BAUD);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
/*   pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT); */
  pinMode(LED, INPUT);
  handleWifi();

  server.on("/", handleRoot);
  server.on("/forward", []()
            {
    Serial.println("forward");
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
    server.send(200, "text/plain", "forward"); });

  server.on("/driveStop", []()
            {
    Serial.println("driveStop");
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    server.send(200, "text/plain", "driveStop"); });

  server.on("/back", []()
            {
    Serial.println("back");
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
    server.send(200, "text/plain", "back"); });

  server.on("/right", []()
            {
    Serial.println("right");
/*     digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW); */
    server.send(200, "text/plain", "right"); });

  server.on("/left", []()
            {
    Serial.println("left");
/*     digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH); */
    server.send(200, "text/plain", "left"); });

  server.on("/steerStop", []()
            {
    Serial.println("steerStop");
/*     digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW); */
    server.send(200, "text/plain", "steerStop"); });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  server.handleClient();
}