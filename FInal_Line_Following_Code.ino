// ====connection definitions=======

//IR Sensors
const int leftIR = A0; 
const int rightIR = A1; 

//L298N Motor Driver 
const int ENA = 3;
const int IN1 = 6;
const int IN2 = 7;

const int ENB = 11;
const int IN3 = 8;
const int IN4 = 9;


// USS sensor pins
const int trigPin = A3;
const int echoPin = A2;


//control logic 
bool started = false; 
bool obstacle = false; 

int motorSpeed = 65; 
const int obstacleDistance = 10;   // cm – stop whenever something is closer

// ===============FUNCTIONS==========================================

void followLine() {
  int leftState = digitalRead(leftIR);
  int rightState = digitalRead(rightIR);

  Serial.print(leftState);
  Serial.println(rightState);

  if (leftState == 0 && rightState == 0) {
    Serial.println("forward!");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }

  if (leftState == 0 && rightState == 1) {
    Serial.println("left!");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
  if (leftState == 1 && rightState == 0) {
    Serial.println("right!");
    Serial.println("forward!");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }

  if (leftState == 1 && rightState == 1) {
    Serial.println("stop!");
        Serial.println("right!");
    Serial.println("forward!");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }


}

bool remotestart() {
  const int wavedistance = 3; 
  long duration; 
  int distance; 

  // triggering the uss pulse 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measuring the pulse duration
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // converting to cm 

  if (distance > 0 && distance < wavedistance) { 
    return true;
  }

  return false;
}

bool detectObstacle() {
  long duration;
  int distance;

  // ping with the same USS pair
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration  = pulseIn(echoPin, HIGH, 20000UL);   // 20 ms timeout
  if (duration == 0) return false;               // timeout → no reading
  distance  = duration * 0.034 / 2;              // µs → cm

  return (distance > 0 && distance < obstacleDistance);
}

// ===============SETUP============================================
void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

}

// ===============LOOP============================================
void loop() {
  if (!started) { 
    if (remotestart()) {  
      started = true; 
    }
  }
  
  if (started) {

    if (detectObstacle()) {
      // full stop
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      Serial.println("Obstacle detected – waiting…");

      // stay here until path clears
      while (detectObstacle()) {
        delay(50);
      }

      Serial.println("Obstacle cleared!");
    }
    
    followLine();
  }
}