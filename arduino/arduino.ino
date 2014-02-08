#include "SoftwareSerial.h"
#include "LiquidCrystal.h"

const int bluetoothRx = 2;
const int bluetoothTx = 3;
const int ledPin = 12;
const char delimiter[] = "%%%";

const int lcdRs = 4;
const int lcdE  = 5;
const int lcdD4 = 6;
const int lcdD5 = 7;
const int lcdD6 = 8;
const int lcdD7 = 9;
const int lcdVolt = 10;

LiquidCrystal lcd(lcdRs, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
String msg = "";

void setup() {
    Serial.begin(115200);

    bluetooth.begin(9600);
    bluetooth.write("$$$");
    delay(100);
    bluetooth.write("U,9600,N");
    bluetooth.begin(9600);

    pinMode(ledPin, OUTPUT);
    pinMode(lcdVolt, OUTPUT);
}

void loop() {
    analogWrite(lcdVolt, 150);
    lcd.begin(16, 2);
    lcd.print("hello, world!");
    if (bluetooth.available()) {
        digitalWrite(ledPin, HIGH);
        while (bluetooth.available()) {
            char received = (char)bluetooth.read();
            Serial.println(received);
            msg += received;
        }

        bluetooth.flush();

        Serial.print("Arduino received: ");
        Serial.print(msg);

        bluetooth.print(msg);
        bluetooth.print(delimiter);

        msg = "";
        digitalWrite(ledPin, LOW);
    }
}
