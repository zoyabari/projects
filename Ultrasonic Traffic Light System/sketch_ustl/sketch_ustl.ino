int red = 9;
int yellow = 10;
int green = 11;
int trigPin = 4;
int echoPin = 5;

long duration;
float distance;
bool isClose;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  stop();
}

void loop() {
  distance = readDistance();
  isClose = (distance < 5); 

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm ");

  if (isClose) {
    waitAndGo();
    stop();
  }

  delay(500);
}

float readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distanceCm = (duration * 0.0343) / 2;
  return distanceCm;
}

void stop() {
  digitalWrite(red, HIGH);   
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}

void waitAndGo() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  delay(2000);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(3000); 
}
