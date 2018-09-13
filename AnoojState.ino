enum AdherenceState {
  DORMANT, // 0
  INDICATOR, // 1
  DISPENSING, // 2
  ADHERENCE_NOTIFICATION  // 3
};
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Servo.h>
int speakerPin = 23;
int buttonPin = 53; // Hidden pushbutton

int dispensePin = 13; // Dispense button
bool dispensePinTarget = false;

// int indicatorLEDPin = 22; // LED that blinks during the Indicator state
/* Origiint redPin = 30; // LED that blinks during the Indicator state
int bluePin = 31;
int greenPin = 32;
int servo1pin = 39; */

int redPin = 30; // LED that blinks during the Indicator state
int bluePin = 31;
int greenPin = 32;
int servo1pin = 39;
Servo myservo;  // create servo object to control a servo

long interval = 30000;  // 30 seconds
long previousMilliseconds = 0;
long currentMilliseconds = 0;
int val = 0;


// Notice that this is a global variable that keeps track if the program should play the notes.
// The value of the variable will be changed each time the user presses the hidden button.
bool playNotes = false;
int length = 15; // the number of notes
char notes[] = "ggggggggggggggg";
int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int tempo = 100;
bool ledFlipper = false;
bool notification = false;


LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x3f for a 16 chars and 2 line display

AdherenceState currentState;

// WiFi Parameters

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  11
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // you can change this clock speed
Adafruit_CC3000_Client client;
// #define WLAN_SSID       "AS iPad"    // >>> Change WiFi // cannot be longer than 32 characters!
#define WLAN_SSID       "Sh Guest"  // >>> Change WiFi
#define WLAN_PASS       "21807Summit" // >>> Change WiFi
//#define WLAN_SSID       "KISDWiFi" // >>> Change WiFi
//#define WLAN_PASS       "onekatyisd" // >>> Change WiFi
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
// received before closing the connection.  If you know the server
// you're accessing is quick to respond, you can reduce this value.

#define IFTTT_WEBSITE           "maker.ifttt.com"

//#define IFTTT_KEY               "b5SyWgV9aKH8JHiclKw3w3" // >>> Change IFTTT Anish
#define IFTTT_KEY               "dixpEdWZuPeCgv5Vj4nz4b" // >>> Change IFTTT Anooj

#define IFTTT_EMAIL_EVENT_NAME  "Send_Email_From_Maker_Post"
#define IFTTT_SMS_EVENT_NAME    "Send_SMS_From_Maker_Post"
uint32_t ifttt_ip = 0;


// const char server_ip_string[] = "172.16.42.2";
uint32_t serverIP = cc3000.IP2U32(172, 16, 42, 3); // >>> Change IP
//uint32_t serverIP = cc3000.IP2U32(10, 65, 160, 71); // >>> Change IP
void setup() {
  
   Serial.begin(115200);
   Serial.println("Starting the machine with initial state");
   
  // lcd.begin(16,2);
  lcd.init();
  
  lcd.backlight();

   // Set up the pin modes 
   pinMode(speakerPin, OUTPUT);
   pinMode(redPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   pinMode(greenPin, OUTPUT);  
   pinMode(buttonPin, INPUT); // declare pushbutton as input
   pinMode(dispensePin, INPUT); // dispense button
   myservo.attach(servo1pin);

  updateLCDDisplay( "    Welcome", " Connecting..." );
  /* Initialise the CC3000 module */
  Serial.println(F("\nInitializing Wifi Breakout..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }



  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("WiFi failed to connect!"));
    updateLCDDisplay( "    Welcome", "Wifi Failed" );
    while(1);
 
  } 

   
  Serial.println(F("Connected!"));
  client = cc3000.connectTCP(serverIP, 80);
 
  updateLCDDisplay( "    Welcome", "Wifi Connected" );
  // Optional SSID scan
 // listSSIDResults();
  delay (5000);

  

  transitionToDormantState(); 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  switch ( currentState ) {
    case DORMANT:
      performDormantState();
      break;
    case INDICATOR:
      performIndicatorState();
      break;
    case DISPENSING:
      performDispensingState();
      break; 
    case ADHERENCE_NOTIFICATION:
      performAdherenceNotificationState();
      break; 
    default:
      Serial.println("FATAL: Unsupported state!");      
      break;
  }
  
}

void setColor(int red, int green, int blue){
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
    digitalWrite(redPin, red);
    digitalWrite(greenPin, green);
    digitalWrite(bluePin, blue);  
  }

void transitionToDormantState() {


  dispensePinTarget =  !digitalRead( dispensePin );
  
  currentState = DORMANT;

  
  // updateLCDDisplay ("Smart Medicine  ", "Dispenser       ");
  updateLCDDisplay ("IntelliDose     ", "                ");

  
  if (notification == false) {
    Serial.println("Dormant State - Green");
    setColor(0, 255, 0);  // green
  }
  else {
    Serial.println("Dormant State - Blinking Red");
    ledFlipper = true;
    
    digitalWrite(bluePin, HIGH);
    while(true) {
        if ( ledFlipper ) {
        
        digitalWrite( redPin, HIGH );
          ledFlipper = false;
        } else {
          digitalWrite( redPin, LOW );
          ledFlipper = true;
        }
        
        // pause
        delay(500);

    val = digitalRead(buttonPin);
    if (val == LOW)
    {
      // The hidden button was pressed 
      notification = false;
      break; 
    }

    val = digitalRead(dispensePin);
   
    if (val == dispensePinTarget )
    {
    // The Dispense button was pressed and we need to transition to the Dispense state
      notification = false;
      transitionToDispenseState();
      break;
    }
            
  }
  
    
  }
  
  
}

void performDormantState() {


  val = digitalRead(buttonPin);
  if (val == LOW)
  {
    notification = false;
    // The hidden button was pressed and we need to transition to the indicator state
    transitionToIndicatorState();  
  }
  
  delay(200);

   
}

void transitionToIndicatorState() {
    Serial.println("Transitioning to Indicator State");
    currentState = INDICATOR;

    // Update LED Screen to tell user to take medicine
    // set cursor position to start of first line on the LCD
    updateLCDDisplay ("Take your     ", "Medicine      ");
    
    setColor(255, 0, 0);  // red
    

    digitalWrite( redPin, LOW ); // Making sure the indicator LED is LOW
    
    previousMilliseconds = millis();
    
    
}



void performIndicatorState() {
  //Serial.println("Performing Indicator State");
  ledFlipper = true;
  digitalWrite( redPin, HIGH );
  
  // Play notes to indicate that the patient needs to take their medication
  for (int i = 0; i < length; i++) {
        if ( ledFlipper ) {
        
        digitalWrite( redPin, HIGH );
          ledFlipper = false;
        } else {
          digitalWrite( redPin, LOW );
          ledFlipper = true;
        }
        
        if (notes[i] == ' ') {
          delay(beats[i] * tempo); // rest
        } else {
          playNote(notes[i], beats[i] * tempo);
        }
    
        // pause between notes
        delay(tempo / 2); 
        //Serial.println("Medication Adherence");      
  }
  digitalWrite( redPin, LOW );

 val = digitalRead(dispensePin);
 Serial.println(val);
  
  if (val == dispensePinTarget )
  {
    // The Dispense button was pressed and we need to transition to the Dispense state
    transitionToDispenseState();
  }

  currentMilliseconds = millis();
  // Check to see if the current time is more than 30 seconds
  // longer than the previously recorded time
  Serial.println( currentMilliseconds - previousMilliseconds );
  if ( currentMilliseconds - previousMilliseconds > interval ) {
    Serial.println("30 seconds is up. Changing state to ADHERENCE_NOTIFICATION");
    // Reset the timer to the current time
    previousMilliseconds = millis();  
    transitionToAdherenceNotificationState();
  }

  delay (200);
}

void transitionToAdherenceNotificationState(){
  currentState = ADHERENCE_NOTIFICATION;
}

void transitionToDispenseState() {
  
  currentState = DISPENSING;
  updateLCDDisplay ("Dispensing       ", "your medicine");
  setColor(0, 0, 255);  // blue
 

}

void DispensePill()
{
  for (int pos = 0; pos <= 180; pos += 30) { // goes from 0 degrees to 180 degrees
    // in steps of 30 degrees
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(1000);                       // wait 1s for the servo to reach the position
  }
/*  for (int pos = 0; pos <= 180; pos += 30) { // goes from 0 degrees to 180 degrees
    // in steps of 30 degrees
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(1000);  
 }*/
}

void performDispensingState() {
  Serial.println("Performing Dispensing State");
  // Servo Motor releases pill
  DispensePill();
  delay(5000);
  // Record Dispensation in Database
  sendMedicationTakenPost();
  
  // Stop LEDs and/or Tones
  Serial.println("Transitioning to Dormant State");
  delay(10000);
  
  transitionToDormantState();
  

}

void performAdherenceNotificationState() {
  Serial.println("Performing Adherence Notification state");
   notification = true;
   sendMedicationNotTakenPost();
  delay(2000);
  Serial.println("Transitioning to Dormant state");
  
  transitionToDormantState();
}


void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }

}

/**************************************************************************/
/*!
    @brief  Begins an SSID scan and prints out all the visible networks
*/
/**************************************************************************/

void listSSIDResults(void)
{
  uint32_t index;
  uint8_t valid, rssi, sec;
  char ssidname[33];

  if (!cc3000.startSSIDscan(&index)) {
    Serial.println(F("SSID scan failed!"));
    return;
  }

  Serial.print(F("Networks found: ")); Serial.println(index);
  Serial.println(F("================================================"));

  while (index) {
    index--;

    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);

    Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
    Serial.println();
    Serial.print(F("RSSI         : "));
    Serial.println(rssi);
    Serial.print(F("Security Mode: "));
    Serial.println(sec);
    Serial.println();
  }
  Serial.println(F("================================================"));

  cc3000.stopSSIDscan();
}



void updateLCDDisplay( String firstLine, String secondLine ) {

 // Serial.print("In updateLCDDisplay"); Serial.print(firstLine); Serial.print(secondLine);
  
  // set cursor position to start of first line on the LCD
  lcd.setCursor(0,0);
  //text to print
  lcd.print(firstLine);
  // set cusor position to start of next line
  lcd.setCursor(0,1);
  lcd.print(secondLine);

}

void sendMedicationTakenPost() {
  updateLCDDisplay ("Recording in       ", "database         ");
  sendPost( "patient_name=Anooj%20Shah&medication_event=Medication%20Taken" );
}

void sendMedicationNotTakenPost() {
    updateLCDDisplay ("Recording in       ", "database         ");
    sendPost( "patient_name=Anooj%20Shah&medication_event=Medication%20Not%20Taken" );
    updateLCDDisplay ("Sending           ", "email            ");
    sendEmailIFTTTPost();
    updateLCDDisplay ("Sending           ", "SMS              ");
    sendSMSIFTTTPost();
    updateLCDDisplay ("Email sent          ", "SMS sent        ");
    delay (5000);
}

void sendPost( String postDataString ) {
 
  //Adafruit_CC3000_Client client = cc3000.connectTCP(serverIP, 80);

//  Serial.println(client.connected());
  Serial.println("start of sendPost");
  char postData[256];
  strncpy(postData, postDataString.c_str(), sizeof(postData));
  postData[sizeof(postData)-1] = 0;

  if(!client.connected()) {
    client = cc3000.connectTCP(serverIP, 80);
  }
  Serial.println("testing connection");
  if (client.connected()) {
      
      Serial.println("About to send data to Node ...");
      
      client.fastrprintln(F("POST /addMedicineInfo HTTP/1.1"));
      Serial.print("POST /addMedicineInfo HTTP/1.1\r\n");
    client.fastrprintln(F("Host: 172.16.42.3")); // >>> Change IP
    //    client.fastrprintln(F("Host: 10.65.160.71")); // >>> Change IP
  
      Serial.print("Host: 172.16.42.3\r\n"); // >>> Change IP
      client.fastrprint(F("Content-Length: "));
      Serial.print("Content-Length: " );
      client.print(postDataString.length());
      Serial.print(postDataString.length());
      client.fastrprint(F("\r\n"));
      Serial.print("\r\n");
      client.fastrprint(F("Content-Type: application/x-www-form-urlencoded\r\n\r\n"));
      Serial.print("Content-Type: application/x-www-form-urlencoded\r\n\r\n");
      client.fastrprint(postData);
      Serial.println(postData);
      client.println();
      updateLCDDisplay ("Recorded in        ", "database         ");
      
  } else {
    Serial.println(F("Database Connection failed"));   
    return;
  }
  unsigned long lastRead = millis();
  while (client.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      lastRead = millis();
    }
  }
  Serial.println("Done...");
  //client.close();
  delay(10000);
  
}

void sendEmailIFTTTPost() {
  sendIFTTTPost( "{}", IFTTT_EMAIL_EVENT_NAME );
}

void sendSMSIFTTTPost() {
  sendIFTTTPost( "{}", IFTTT_SMS_EVENT_NAME ); // >>> Change SMS uncomment if commented
}


void sendIFTTTPost( String postDataString, String eventName ) {
  // Get IFTTT IP Address
  while (ifttt_ip == 0) {
    cc3000.getHostByName(IFTTT_WEBSITE, &ifttt_ip);
    delay(500);
  }
  
  Adafruit_CC3000_Client client = cc3000.connectTCP(ifttt_ip, 80);

  

  char postData[256];
  strncpy(postData, postDataString.c_str(), sizeof(postData));
  postData[sizeof(postData)-1] = 0;

  
  if (client.connected()) {
      
      Serial.println("About to send data to IFTTT ...");
      
      client.fastrprint(F("POST /trigger/"));
      client.print( eventName );
      client.fastrprint(F("/with/key/"));
      client.print( IFTTT_KEY );
      client.fastrprintln(F(" HTTP/1.1"));
      
      Serial.print("POST /trigger/Send_Email_From_Maker_Post/with/key/");
      Serial.print( IFTTT_KEY ); 
      Serial.print( " HTTP/1.1\r\n" );
      client.fastrprintln(F("Host: maker.ifttt.com"));
      Serial.print("Host: maker.ifttt.com\r\n");
      client.fastrprint(F("Content-Length: "));
      Serial.print("Content-Length: " );
      client.print(postDataString.length());
      Serial.print(postDataString.length());
      client.fastrprint(F("\r\n"));
      Serial.print("\r\n");
      client.fastrprint(F("Content-Type: application/json\r\n\r\n"));
      Serial.print("Content-Type: application/json\r\n\r\n");
      client.fastrprint(postData);
      Serial.println(postData);
      client.println();
      
  } else {
    Serial.println(F("IFTTT Connection failed"));   
    return;
  }
  unsigned long lastRead = millis();
  while (client.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (client.available()) {
      //Serial.println("Reading data...");
      char c = client.read();
      Serial.print(c);
      lastRead = millis();
    }
  }
  Serial.println("Done...");
  client.close();
  delay(200);
  
}




