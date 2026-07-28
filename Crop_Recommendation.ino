#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define RE 8
#define DE 7

const byte nitro[] = {0x01,0x03,0x00,0x1e,0x00,0x01,0xe4,0x0c};
const byte phos[]  = {0x01,0x03,0x00,0x1f,0x00,0x01,0xb5,0xcc};
const byte pota[]  = {0x01,0x03,0x00,0x20,0x00,0x01,0x85,0xc0};

byte values[11];

SoftwareSerial mod(2,3);

void setup() {

  Serial.begin(9600);      
  mod.begin(9600);         

  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25,15);
  display.println("NPK Sensor");
  display.setCursor(20,35);
  display.println("Initializing...");
  display.display();
  delay(3000);
}

void loop() {

  int N = (int)nitrogen();
  delay(250);
  int P = (int)phosphorous();
  delay(250);
  int K = (int)potassium();
  delay(250);

  Serial.print(N);
  Serial.print(",");
  Serial.print(P);
  Serial.print(",");
  Serial.println(K);

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,5);
  display.print("N: ");
  display.print(N);

  display.setCursor(0,25);
  display.print("P: ");
  display.print(P);

  display.setCursor(0,45);
  display.print("K: ");
  display.print(K);

  display.display();

  delay(2000);
}

// ================= SENSOR FUNCTIONS =================

byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);

  mod.write(nitro,sizeof(nitro));

  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);

  delay(100);

  for(byte i=0;i<7;i++){
    values[i] = mod.read();
  }

  return values[4];
}

byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);

  mod.write(phos,sizeof(phos));

  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);

  delay(100);

  for(byte i=0;i<7;i++){
    values[i] = mod.read();
  }

  return values[4];
}

byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);

  mod.write(pota,sizeof(pota));

  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);

  delay(100);

  for(byte i=0;i<7;i++){
    values[i] = mod.read();
  }

  return values[4];
}