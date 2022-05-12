// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int available_med[] = {0,0};

int echo[] = {2,4,6,8};
int trigpin[] = {3,5,7,9};
int motors[] = {10,11,12,13};
int i;
void setup() {
  for(i=0;i<4;i++)
  {
    pinMode(motors[i], OUTPUT); // Sets the motor driver pins as an OUTPUT
    pinMode(trigpin[i], OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echo[i], INPUT); // Sets the echoPin as an INPUT
  }
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Medicine Vending Machine"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

int ultrasonic_dist(int uid_no)
{
  // Clears the trigPin condition
  digitalWrite(uid_no*2+1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(uid_no*2+1, HIGH);
  delayMicroseconds(10);
  digitalWrite(uid_no*2+1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(uid_no*2, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  distance = map(distance, 0, 1103, 0, 400);
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
  return distance;
}
void loop() {
  // put your main code here, to run repeatedly:
  int i,j;
  delay(2000);
  for(i=0;i<20;i++)
  {
    j = ultrasonic_dist(1);
    Serial.print("Distance from sensor 1 is ");
    Serial.print(j);
    Serial.print("\n");
  }
  delay(2000);
  for(i=0;i<20;i++)
  {
    j = ultrasonic_dist(2);
    Serial.print("Distance from sensor 2 is ");
    Serial.print(j);
    Serial.print("\n");
  }
  delay(2000);
  for(i=0;i<20;i++)
  {
    j = ultrasonic_dist(3);
    Serial.print("Distance from sensor 3 is ");
    Serial.print(j);
    Serial.print("\n");
  }
  delay(2000);
  for(i=0;i<20;i++)
  {
    j = ultrasonic_dist(4);
    Serial.print("Distance from sensor 4 is ");
    Serial.print(j);
    Serial.print("\n");
  }
  delay(2000);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(2000);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  delay(2000);
}
