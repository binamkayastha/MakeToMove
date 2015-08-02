/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

unsigned long startTime;
int state = 0;
int count = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(9, INPUT);
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  startTime = millis();
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int currentState = digitalRead(9);
  Serial.println(currentState);
  
  if(state == currentState) {
    count++;
  } else if (state != currentState) {
    count = 0;
    if(millis()-startTime > 50000) {
      Serial.print("This is current time: ");
      Serial.println(millis());
      Serial.print("This is the start time: ");
      Serial.println(startTime);
      Serial.print("You've been running for 1 while");
      /*
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      */     
    
    } else if (millis()-startTime > 40000) {
      Serial.print("You've been running for 2 while");
      /*
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      */     
    } else if (millis()-startTime > 30000) {
      digitalWrite(3, HIGH);
      /*
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      */
    } else if (millis()-startTime > 20000) {
      digitalWrite(4, HIGH);
      /*
      digitalWrite(10, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      */
    } else if (millis()-startTime > 10000) {
      digitalWrite(5, HIGH);
      /*
      digitalWrite(10, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      digitalWrite(10, LOW);
      */
    }
    
    state = currentState;
  }
  
  if (count >50) {
    Serial.println("Reset");
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    Serial.print("This is current time: ");
    Serial.println(millis());
    Serial.print("This is the start time: ");
    Serial.println(startTime);
      
    startTime = millis();
    Serial.print("bleh");
    Serial.print("This is current time: ");
    Serial.println(millis());
    Serial.print("This is the start time: ");
    Serial.println(startTime);
    count = 0;
  }
  
//  if((state == currentState) && ((millis()-startTime)>1000) && !wasChangedRecently) {
//    startTime = millis();
//    wasChangedRecently = false;
//    Serial.println("RESTARTED");
//  }
//  if((state!=currentState) && (millis()-startTime>1000)) {
//    Serial.println("You've been running for a while");
//    state=currentState;
//    wasChangedRecently = true;
//  }
  
//  if(state!=currentState) {
//    startTime = millis();
//    state = currentState;
//    Serial.println("RESTARTED");
//  }
//  if (millis() > (startTime+10000)) {
//    Serial.println("You've been pedeling for some time");
//  }
  delay(100);
}
