#include "BluetoothSerial.h" //Header File for Serial Bluetooth
BluetoothSerial ESP_BT; //Object for Bluetooth
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

Adafruit_SSD1306 display(128, 64);
String incoming;// varible store received data
int M1A = 17; // motor pins
int M1B = 16;
int M2A = 27;
int M2B = 18;

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();

  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("ESP32_Blutooth_car"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode(M1A, OUTPUT); // configure outputs
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

}

void loop() {

  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = char(ESP_BT.read()); //Read what we received
  }
  Serial.println(incoming);
  if (incoming == "F") { // forward
    Serial.println("Forward");
    Display("Forward");
    Forward();
  }
  else if (incoming == "B") { // reverse
    Serial.println("Reverse");
    Display("Reverse");
    Backward();
  }
  else if (incoming == "R") { //turn right
    Serial.println("Right");
    Display("Right");
    Right();
  }
  else if (incoming == "L") { // turn left
    Serial.println("Left");
    Display("Left");
    Left();
  }



  else {
    Stop();

    Display("Stop");
  }
  delay(20);
}

void Forward() {

  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);

}

void Backward() {

  digitalWrite(M1B, HIGH);
  digitalWrite(M1A, LOW);
  digitalWrite(M2B, HIGH);
  digitalWrite(M2A, LOW);

}
void Right() {

  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, HIGH);
  digitalWrite(M2A, LOW);

}
void Left() {

  digitalWrite(M1B, HIGH);
  digitalWrite(M1A, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);

}

void Stop() {
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);

}


void Display(String commond) { // display data
  display.clearDisplay();

  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 20);            // Start at top-left corner
  display.println(commond);
  display.display();
}
