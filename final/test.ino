// AT+COND8A98B80E0D6
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h> 
#include <Servo.h>

//#define _SS_MAX_RX_BUFF 256

#define WiFi_TX 2
#define WiFi_RX 3

#define RST_PIN 9
#define SS_PIN 10
#define SPEAKER_PIN 4

int noteDurations_init = 4;

const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

const int READ_TIME = 500;
unsigned long prevMillis;

SoftwareSerial esp8266(WiFi_TX,WiFi_RX);
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo_l;
Servo servo_r;

int pos_l = 90, pos_r = 90;
int closeTime_out = 0;
int closeTime_in = 0;

String ssid = "HTC Portable Hotspot 09A3"; // Use you own SSID
String password = "8a298a1ed2a9"; // Use you own Password
String path = "POST /a HTTP/1.1\r\nHost: 61.218.61.151:20000\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 1\r\n\r\n0";
String request = "";
String requestLength = "";
const int timeout = 200;

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void play_success_melody(){
  int noteDuration = 1000 / noteDurations_init;
  int pauseBetweenNotes = noteDuration * 1.30;

  tone(SPEAKER_PIN, 262, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
  tone(SPEAKER_PIN, 500, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
}

void play_error_melody(){
  int noteDuration = 1000 / noteDurations_init;
  int pauseBetweenNotes = noteDuration * 1.30;

  tone(SPEAKER_PIN, 1000, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
  tone(SPEAKER_PIN, 1000, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
  tone(SPEAKER_PIN, 1000, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
  tone(SPEAKER_PIN, 1000, 250);
  delay(pauseBetweenNotes);
  noTone(SPEAKER_PIN);
}

void openDoor_out()
{
  for (; pos_l <= 180; pos_l += 1, pos_r -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_l.write(pos_l);              // tell servo to go to position in variable 'pos'
    servo_r.write(pos_r);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void openDoor_in()
{
  for (; pos_r <= 180; pos_r += 1, pos_l -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_l.write(pos_l);              // tell servo to go to position in variable 'pos'
    servo_r.write(pos_r);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void closeDoor_out()
{
  for (; pos_r <= 90; pos_r += 1, pos_l -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_r.write(pos_r);              // tell servo to go to position in variable 'pos'
    servo_l.write(pos_l);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void closeDoor_in()
{
  for (; pos_l <= 90; pos_l += 1, pos_r -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_r.write(pos_r);              // tell servo to go to position in variable 'pos'
    servo_l.write(pos_l);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void setup() {
  Serial.begin(9600);
  
  esp8266.begin(115200);
  setupESP8266();
  connectToWiFi();
   
  Serial.println("RFID reader is ready!");
  SPI.begin();
  mfrc522.PCD_Init(); 
  servo_l.attach(5);
  servo_r.attach(6);
  servo_l.write(pos_l);
  servo_r.write(pos_r); 
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    byte *id = mfrc522.uid.uidByte; // 取得卡片的UID
    if(id[0] == 169 && id[1] == 216 && id[2] == 65 && id[3] == 195)
    {
      Serial.println("Welcome home!");
      play_success_melody();
      openDoor_in();
      sendToAPI("card", "A9D841C3");
      closeDoor_in();
    }
    else if(id[0] == 121 && id[1] == 146 && id[2] == 51 && id[3] == 232)
    {
      Serial.println("Welcome home!");
      play_success_melody();
      openDoor_in();
      sendToAPI("card", "799233E8");
      closeDoor_in();
    }
    else
    {
      Serial.println("Unknown login!");
      play_error_melody();
      sendToAPI("card", "Fail:" + String(id[0], HEX) + String(id[1], HEX) + String(id[2], HEX) + String(id[3], HEX));
    }
    mfrc522.PICC_HaltA(); // 讓卡片進入停止模式
  }
}

void sendToAPI(String _type, String _id)
{
  request = path;
  requestLength = String(request.length());
  startTCPConnection();
  sendGetRequest();
  closeTCPConnection();
}

String atCommand(String command, int timeout) {
  String response = "";
  esp8266.println(command);

  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
  }

  Serial.println(response);
  return response;
}

void setupESP8266() {
  atCommand("AT+RST", timeout);
  atCommand("AT+CWMODE=1", timeout);
}

void connectToWiFi() {
  String connect = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
  atCommand(connect, 6000);
  atCommand("AT+CIFSR", timeout);
}

void startTCPConnection() {
  String connect = "AT+CIPSTART=\"TCP\",\"61.218.61.151\",20000";
  atCommand(connect, timeout);
}

void closeTCPConnection() {
  atCommand("AT+CIPCLOSE", timeout);
}

String sendGetRequest() {
  atCommand("AT+CIPSEND=" + requestLength, timeout);
  String response = atCommand(request, 6000);
  return response;
}
