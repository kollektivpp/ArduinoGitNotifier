#include "SoftwareSerial.h"
#include "LiquidCrystal.h"

const int bluetoothRx = 12;
const int bluetoothTx = 13;
const int ledPin = 11;
const char delimiter[] = "%%%";

const int lcdRs = 8;
const int lcdE  = 9;
const int lcdD4 = 4;
const int lcdD5 = 5;
const int lcdD6 = 6;
const int lcdD7 = 7;

LiquidCrystal lcd(lcdRs, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
String msg = "";
char lcdMsg[16];

void setup() {
    Serial.begin(115200);

    bluetooth.begin(9600);
    bluetooth.write("$$$");
    delay(100);
    bluetooth.write("U,9600,N");
    bluetooth.begin(9600);

    pinMode(ledPin, OUTPUT);

    lcd.begin(16, 2);

    lcd.setCursor(0,0);
    lcd.print("ich warte");
}

void loop() {
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

        for (int i = 0; i < 16; i++) {
            lcdMsg[i] = msg[i];
        }

        lcd.setCursor(0,0);
        lcd.print(lcdMsg);

        bluetooth.print(msg);
        bluetooth.print(delimiter);

        msg = "";
        digitalWrite(ledPin, LOW);
    }
}
