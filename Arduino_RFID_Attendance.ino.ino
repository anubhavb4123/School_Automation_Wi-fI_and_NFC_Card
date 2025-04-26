#include <SPI.h> 
#include <MFRC522.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#define SS_PIN 10 
#define RST_PIN 9 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create 
MFRC522 instance 
// LED pins 
#define GREEN_LED_PIN 3 
#define RED_LED_PIN 4 
// Valid UIDs of students 
byte validUIDs[][4] = { 
{0x73, 0x6A, 0x4C, 0x28},  // UID of student 1 
{0xCE, 0x56, 0x4C, 0x22},  // UID of student 2 
{0xDE, 0xB2, 0xA2, 0xA1},  // UID of student 3 
{0xFE, 0xFE, 0x36, 0x22},  // UID of student 4 
}; 
// Student names 
const char* studentNames[] = { 
"Anubhav Bajpai",  // Name of student 1 
"Akshay Bajpai",   // Name of student 2 
"Vaibhavi Singh",  // Name of student 3 
"Aishwarya Mishra" // Name of student 4 
}; 
// LCD I2C display 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust the 
address and size according to your display 
void setup() { 
Serial.begin(9600);      
communication 
SPI.begin();              
 // Initialize serial 
// Initiate SPI bus 
  // Initiate MFRC522 
mfrc522.PCD_Init();     
lcd.init();               
// Initialize the LCD display 
lcd.backlight();        
lcd.clear(); 
lcd.setCursor(2, 0); 
  // Turn on the backlight 
lcd.print("Scan ID card"); 
Serial.println("Ready to read RFID cards"); 
// Set LED pins as output 
pinMode(GREEN_LED_PIN, OUTPUT); 
pinMode(RED_LED_PIN, OUTPUT); 
// Turn off both LEDs initially 
digitalWrite(GREEN_LED_PIN, LOW); 
digitalWrite(RED_LED_PIN, LOW); 
} 
void loop() { 
// Look for new cards 
if (mfrc522.PICC_IsNewCardPresent()) { 
if (mfrc522.PICC_ReadCardSerial()) { 
// Show UID on serial monitor 
Serial.print("UID tag: "); 
for (byte i = 0; i < mfrc522.uid.size; i++) { 
Serial.print("0x"); 
if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0"); 
Serial.print(mfrc522.uid.uidByte[i], HEX); 
if (i < mfrc522.uid.size - 1) Serial.print(", "); 
} 
Serial.println(); 
Serial.print("UID Number: "); 
String content = ""; 
for (byte i = 0; i < mfrc522.uid.size; i++) { 
content.concat(String(mfrc522.uid.uidByte[i] < 
0x10 ? "0" : "")); 
content.concat(String(mfrc522.uid.uidByte[i], 
HEX)); 
} 
content.toUpperCase(); 
Serial.println(content); 
// Check if the UID matches any of the valid UIDs 
bool uidMatched = false; 
int studentIndex = -1; 
for (int i = 0; i < sizeof(validUIDs) / 
sizeof(validUIDs[0]); i++) { 
if (memcmp(mfrc522.uid.uidByte, validUIDs[i], 
mfrc522.uid.size) == 0) { 
uidMatched = true; 
studentIndex = i; 
break; 
} 
} 
// Perform actions based on UID match 
if (uidMatched) { 
digitalWrite(GREEN_LED_PIN, HIGH); 
digitalWrite(RED_LED_PIN, LOW); 
updateAttendance(studentIndex + 1, "Present"); 
delay(3000);  // Keep the green LED on for 3 
seconds 
digitalWrite(GREEN_LED_PIN, LOW); 
} else { 
digitalWrite(GREEN_LED_PIN, LOW); 
digitalWrite(RED_LED_PIN, HIGH); 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print("ID doesn't match"); 
delay(2000);  // Keep the red LED on for 2 seconds 
digitalWrite(RED_LED_PIN, LOW); 
} 
lcd.clear(); 
lcd.setCursor(2, 0); 
lcd.print("Scan ID card"); 
delay(1000);    
} 
mfrc522.PICC_HaltA();   // Stop reading 
mfrc522.PCD_StopCrypto1();  // Stop encryption on 
PCD 
} 
} 
// Function to update attendance in the database 
void updateAttendance(int studentID, const char* 
status) { 
// Display the name of the student on the LCD 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print(studentNames[studentID - 1]);  // -1 to adjust 
for array indexing 
lcd.setCursor(0, 1);  // Set cursor to the second line 
lcd.print("~"); 
lcd.setCursor(2, 1);  // Set cursor position after 4 pixels 
lcd.print(status); 
}