// #define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
// #define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int available_med[] = {0,0};

int echo[] = {3,5,7,9};
int trigpin[] = {2,4,6,8};
int motors[] = {10,11,12,13};
int i;
void setup() {
  for(i=0;i<4;i++)
  {
    pinMode(trigpin[i], OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echo[i], INPUT); // Sets the echoPin as an INPUT
    pinMode(motors[i], OUTPUT); // Sets the motor driver pins as an OUTPUT
  }
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Medicine Vending Machine"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

int ultrasonic_dist(int uid_no)
{
  delay(2000);
  // Clears the trigPin condition
  digitalWrite(uid_no*2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(uid_no*2, HIGH);
  delayMicroseconds(10);
  digitalWrite(uid_no*2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(uid_no*2+1, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  distance = map(distance, 0, 1103, 0, 400);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void update_medicines()
{
  int dist1 = ultrasonic_dist(3);
  if(dist1>=18)
  {
    Serial.println("No Medicines found in Row 2");
    available_med[1] = 0;  
  }
  else{
    Serial.println("Medicines found in Row 2");
    available_med[1]= 1;
  }
  delay(1000);
  dist1 = ultrasonic_dist(4);
  if(dist1>=18)
  {
    Serial.println("No Medicines found in Row 1");
    available_med[0] = 0;  
  }
  else{
    Serial.println("Medicines found in Row 1");
    available_med[0] = 1;
  }
  delay(1000);
}

void order_medicines(int row_no)
{
  if(available_med[row_no-1])
  {
    Serial.print("Dispatching medicines from row ");
    Serial.print(row_no);
    Serial.print("\n");
    while(ultrasonic_dist(row_no)>=10)
    {
      digitalWrite((4+row_no)*2,LOW);
      digitalWrite((4+row_no)*2+1,HIGH);
    }
    Serial.print("Order Successfuly dispatched from row ");
    Serial.print(row_no);
    Serial.print("\n");
    digitalWrite((4+row_no)*2,LOW);
    digitalWrite((4+row_no)*2+1,LOW);
    delay(3000);
    update_medicines();
  }
  else{
    Serial.print("No medicines in the row ");
    Serial.print(row_no);
    Serial.print("\n");
  }
}

void loop() 
{
  update_medicines();
  order_medicines(1);
//  delay(20000);
  order_medicines(2);
//  delay(20000);
}
