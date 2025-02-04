#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;
const int switchPin = 10; 
const int greenLEDPin = 11; 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char correctCode[5] = "6789"; 
char enteredCode[5] = ""; 
byte index = 0;

void setup() {
    pinMode(switchPin, INPUT_PULLUP);
    pinMode(greenLEDPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (digitalRead(switchPin) == LOW) { 
        char key = keypad.getKey();
        
        if (key) {
            Serial.println(key);
            
            if (index < 4) {
                enteredCode[index] = key;
                index++;
            }
            
            if (index == 4) {
                enteredCode[4] = '\0'; 
                
                if (strcmp(enteredCode, correctCode) == 0) {
                    Serial.println("Koda je pravilna");
                    digitalWrite(greenLEDPin, HIGH);
                } else {
                    Serial.println("Ni pravilno");
                    digitalWrite(greenLEDPin, LOW);
                }
                index = 0; 
            }
        }
    } else {
        digitalWrite(greenLEDPin, LOW); 
        index = 0; 
    }
}
