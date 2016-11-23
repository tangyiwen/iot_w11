#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "028";
const char *password = "";
ESP8266WebServer server(80);

char led_status[50];
String webSite;

#define LEDR 5
#define LEDG 4
#define LEDB 14

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}

void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title> NodeMCU 網頁測試 </title>";
  webSite += "<style>";
  webSite += "body{background-color:#D1BBFF; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}";
  webSite += "div{width:500px; text-align: center; margin: 50 auto;}";
  webSite += "</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>RGB LED Control form</h1>";
  webSite += "<p id=\"ledStatus\">You can select a RGB LED color ...</p>";
  webSite += "<form action=\"form1\">";
  webSite += "Color Red<input type=\"text\" id=\"red\" name=\"red\"><br>";
  webSite += "Color Green<input type=\"text\" id=\"green\" name=\"green\"><br>";
  webSite += "Color blue<input type=\"text\" id=\"blue\" name=\"blue\"><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</div>";
  webSite += "</body></html>";
}

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
int red_color = server.arg("red").toInt();
  int green_color = server.arg("green").toInt();
  int blue_color = server.arg("blue").toInt();
  
  analogWrite(LEDR,red_color);
  analogWrite(LEDG,green_color);
  analogWrite(LEDB,blue_color);

  server.send(200,"text/html",webSite);

}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
  buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}




