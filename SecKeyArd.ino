#include <Keypad.h>

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LED pins
const int greenLED = 12;
const int redLED = 11;

// Password setup
String correctPassword = "1234";  // Change this to your desired password
String enteredPassword = "";
const int passwordLength = 4;     // Length of password

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Password Entry System Ready");
  Serial.println("Enter 4-digit password:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {  // If a key is pressed
    Serial.print("*");  // Show asterisk for privacy
    
    // Only accept numeric keys
    if (key >= '0' && key <= '9') {
      enteredPassword += key;  // Add key to entered password
      
      // Check if password is complete
      if (enteredPassword.length() == passwordLength) {
        checkPassword();
      }
    }
    
    // '#' to submit, '*' to clear
    else if (key == '#') {
      checkPassword();
    }
    else if (key == '*') {
      clearPassword();
    }
  }
}

void checkPassword() {
  Serial.println();  // New line after asterisks
  
  if (enteredPassword == correctPassword) {
    Serial.println("ACCESS GRANTED!");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    delay(3000);  // Show success for 3 seconds
    digitalWrite(greenLED, LOW);
  }
  else {
    Serial.println("ACCESS DENIED!");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    delay(2000);  // Show failure for 2 seconds
    digitalWrite(redLED, LOW);
  }
  
  clearPassword();
}

void clearPassword() {
  enteredPassword = "";
  Serial.println("Enter password:");
}