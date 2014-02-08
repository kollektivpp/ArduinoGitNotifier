#include "SoftwareSerial.h"

const int bluetoothRx = 2;
const int bluetoothTx = 3;
const int ledPin = 12;
const char delimiter[] = "%%%";


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

        bluetooth.print(msg);
        bluetooth.print(delimiter);

        msg = "";
        digitalWrite(ledPin, LOW);
    }
}
