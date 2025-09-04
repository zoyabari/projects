#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
const int servoPin = 13;
int startPos = 90;

Servo myservo;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void moveServo(int targetPos, int stepDelay = 15) {
  if (targetPos > startPos) {
    for (int pos = startPos; pos <= targetPos; pos++) {
      myservo.write(pos);
      delay(stepDelay);
    }
  } else if (targetPos < startPos) {
    for (int pos = startPos; pos >= targetPos; pos--) {
      myservo.write(pos);
      delay(stepDelay);
    }
  }
  startPos = targetPos;
}

void swingLeft() {
  moveServo(0);
}

void swingRight() {
  moveServo(180);
}

void autoPlay() {
  for (int i = 0; i < 15; i++) {
    int randomPos = random(0, 181);
    moveServo(randomPos, random(5, 20));
    delay(random(500, 1500));
  }
  reset();
}

void reset() {
  Serial.println("Resetting to center...");
  moveServo(90);
}

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(startPos);
  delay(1000);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey) {
    Serial.println(customKey);

    switch(customKey) {
      case 'A':
        swingLeft();
        break;
      case 'B':
        swingRight();
        break;
      case 'C':
        autoPlay();
        break;
      case 'D':
        reset();
        break;
      default:
        Serial.println("Use buttons A, B, C, or D");
        break;
    }
  }
}
