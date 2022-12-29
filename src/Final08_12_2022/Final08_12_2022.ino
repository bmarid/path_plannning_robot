// Motor A
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;
int in3 = 5;
int in4 = 4;


//Ultrasonic----------------------------------
int trigPin = 11;    // Trigger
int echoPin = 10;    // Echo
long duration, cm;

//--------------------------------------------

// 0 is up
// 1 is right
// 2 is down
// 3 is left
int direction = 2;
//  the point in the grid where the robot is

int i = 2;
int j = 0;

int path[8][8] =
{
  {    1,0,0,1,1,1,1,1    }
  ,
  {    1,1,0,1,1,1,1,1    }
  ,
  {    1,1,0,1,1,1,1,1    }
  ,
  {    1,1,0,1,1,1,1,1    }
  ,
  {    1,1,0,0,1,1,1,1    }
  ,
  {    1,1,1,-1,1,1,1,1    }
};
 
void setup()
 
{
 //Ulterasonic
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
}

void forward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255
   // Turn on motor B
 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enB, 200);
  analogWrite(enA, 175);
delay(1800);
   Serial.println("Forward");
    if (direction == 0)
        j = j - 1;
    if (direction == 1)
        i = i + 1;
    if (direction == 2)
        j = j + 1;
    if (direction == 3)
        i = i - 1;
 //changed depend on the distance u want to move
  
  
  }
void backword(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 
  // Set speed to 200 out of possible range 0~255
   // Turn on motor B
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enB, 200);
  analogWrite(enA, 200);
 //changed depend on the distance u want to move
  delay(1500);
  }
 void left(){
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   delay(250);
      Serial.println("Left");
    if (direction == 0)
        direction = 3;
    else if (direction == 1)
        direction = 0;
    else if (direction == 2)
        direction = 1;
    else if (direction == 3)
        direction = 2;
 
  }
   void left_180(){
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    analogWrite(enB, 200);
  analogWrite(enA, 200);
  delay(1000);
  }


   void right(){
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    analogWrite(enB, 200);
  analogWrite(enA, 200);
    delay(500);
     Serial.println("Right");
    if (direction == 0)
        direction = 1;
    else if (direction == 1)
        direction = 2;
    else if (direction == 2)
        direction = 3;
    else if (direction == 3)
        direction = 0;

  }

    void stop_robot(){
  
    digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
  }

void turnAround() {
    //  delay(1000);
    Serial.println("Around");
    if (direction == 0)
        direction = 2;
    else if (direction == 1)
        direction = 3;
    else if (direction == 2)
        direction = 0;
    else if (direction == 3)
        direction = 1;
    delay(500);
    Serial.print("  xcoordinate ");
    Serial.print(i);
  //  delay(500);
    Serial.print(" ycoordinate ");
    Serial.print(j);
   // delay(500);
    Serial.print("  robot direction: ");
    Serial.print(direction);
   // delay(500);
    Serial.println();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
}
long calcDistance(){
  ///Ultra--------------------------------
 // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  //inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
//  Serial.print(inches);
//  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
  return cm;}
//--------------------------------------}

// Gets the number on the Grid of the space right in front of it.
int test_front() {
    if (direction == 0) {
        return path[j - 1][i];
    }
    if (direction == 1) {
        return path[j][i + 1];
    }
    if (direction == 2) {
        return path[j + 1][i];
    }
    if (direction == 3) {
        return path[j][i - 1];
    }
}


// Gets the number on the Grid of the space to the Right of it.
int test_right() {
    if (direction == 0) {
        return path[j][i + 1];

    }
    if (direction == 1) {
        return path[j + 1][i];

    }
    if (direction == 2) {
        return path[j][i - 1];
    }
    if (direction == 3) {
        return path[j - 1][i];
    }
}


// Gets the number on the Grid of the Space to the Left of it.
int test_left() {
    if (direction == 0) {
        return path[j][i - 1];
    }
    if (direction == 1) {
        return path[j - 1][i];
    }
    if (direction == 2) {
        return path[j][i + 1];
    }
    if (direction == 3) {
        return path[j + 1][i];
    }
}
 
// Checks if there is something right in front of it using Grids
int frontOpen() {
    int next = test_front();
    if (next != 1) {
        return next;
    }
    else {
        return 1;
    }
}

// Checks if there is something to the Right of it using Grids
boolean rightOpen() {
    int next = test_right();
    if (next == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Checks if there is something to the Left of it using Grids
boolean leftOpen() {
    int next = test_left();
    if (next == 0) {
        return true;
    }
    else {
        return false;
    }
}

 
void loop()
 
{

if (calcDistance()< 35){
  stop_robot();
  //recalc path
}
   else{
    delay(400);
  if (frontOpen() == 0 || frontOpen() == -1 ){
            forward();
            stop_robot();
            //delay(1000);
           if (frontOpen() == -1 ){stop_robot();
           delay(40000);};
        }
        else
            if (rightOpen() == true) {
                right();
               
            }
            else
                if (leftOpen() == true) {
                    left();
                   
                }
                else {
                    //turnAround();
                    delay(2000);
                }
    }
}
 
