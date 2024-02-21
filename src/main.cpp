#include <Arduino.h>

#define trigPin 9
#define echoPin 10

float duration, distance;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;


//timer related 
bool isTimerSet = false;
bool cancelTimer = false;
bool enterTimerState = false;
unsigned long previousTime =0;
unsigned long eventInterval = 500;
unsigned long startMillis;  //some global variables available anywhere in the program

void setup() {

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  startMillis = millis();
}

void loop() {

  //distance sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}


void sendData(){
  
  if(isTimerSet){

    unsigned long currentTime = millis();
    if(enterTimerState){
      startMillis = currentTime;
      enterTimerState = false;
    }

    if(currentTime - startMillis >= eventInterval){
      //CreateSerialArray();
      //Serial.write(serialArr);
      //send here an error message

      enterTimerState = true;
      startMillis = currentTime;
    }
  }else{
    
  }

}

void reciveData(){
  while(Serial.available() > 0){
    
    //Serial.print("Avaliable");

    char inByte = Serial.read();
    if(inByte == 'c'){
      //CreateSerialArray();
      //Serial.write(serialArr);
      inByte = 'r';
    }

  }
}