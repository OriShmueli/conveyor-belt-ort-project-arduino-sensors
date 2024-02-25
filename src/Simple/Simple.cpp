#include <Arduino.h>

#define trigPin 9
#define echoPin 10

int duration, distance;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

char serialArr[18]; //d1234#r123g123b123
int frequency = 0;
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void CreateSerialArray();

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
  //Serial.print("Distance: ");
  //Serial.println(distance);

  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  /*Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");*/
  //delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  /*Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);*/

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  /*Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);*/

  if(Serial.available() > 0){
    
    char inByte = Serial.read();

    if(inByte == 'c'){
      CreateSerialArray();
      Serial.write(serialArr);
      inByte = 'r'; //reset inByte
    }
  }
  
}

void AddDistance(int distance, int from){ //looks like this: 10 cm: --10. 1000 cm 
  for (int i = 3; i >= 0; i--) {
		if (distance / 10 == 0 && distance % 10 == 0)
		{
			serialArr[i+from] = '-';
		}
		else {
			serialArr[i+from] = distance % 10 + '0';
		}
		distance /= 10;	
	}
}

void AddColor(int color, int arrayPosition){
    for (int i = 3; i >= 0; i--) {
		if (distance / 10 == 0 && distance % 10 == 0)
		{
			serialArr[i+arrayPosition] = '-';
		}
		else {
			serialArr[i+arrayPosition] = distance % 10 + '0';
		}
		distance /= 10;	
	}
}

void CreateSerialArray(){
    //d1234r123g123b123
  serialArr[0] = 'd';
  AddDistance(distance, 1); //2, 3, 4 
  serialArr[5] = 'r';
  AddColor(redFrequency, 6); //7, 8
  serialArr[9] = 'g';
  AddColor(greenFrequency, 10); //11, 12
  serialArr[13] = 'b';
  AddColor(blueFrequency, 14); //15, 16
  serialArr[17] = '\0'; //18 characters but the array starting from 0
}