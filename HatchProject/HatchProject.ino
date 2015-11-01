unsigned long startTime;
unsigned long startTime2;
int state = 0;
int state2 = 0;
unsigned long lastChange;
unsigned long lastChange2;
int LEDsOn[] = {0,1,2,3,4};
int LEDsOn2[] = {0,1,2,3,4};
int currentState; //reusable
boolean active;
boolean active2;
int level = 0;
int level2 = 0;

int i = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //3 Inputs into the decoder to produce 8 Outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  //3 Inputs into the decode2 to produce 8 Outputs
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  //The input of wheel excersize machine
  pinMode(10, INPUT_PULLUP);

  //The input of other excersize macine
  pinMode(11, INPUT_PULLUP);

  //G2A and G2B Low (Connected in circuitry)
  pinMode(12, OUTPUT);
//  pinMode(13, OUTPUT);
  
  //OUTPUT TO THE BUBBLE GUN
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
    
  //Initializing start times
  startTime = millis();
  startTime2 = millis();
}

void loop() {
  
  currentState = digitalRead(10);
  
  if (state != currentState) { //If there is a change
    state = currentState;
    Serial.println("CHANGE ONE");
    lastChange = millis();
    active = true;
  }
  if (millis() - lastChange > 10000) {
    Serial.println("Reset ONE");
    active = false;

    lastChange = millis();
    level--;
    if(level < 0) {level = 0;}    
    startTime = millis();
    startTime -= (level+1)*5000;
  }
  
  if (active) {
    if(millis()-startTime > 30000) {
      digitalWrite(8, HIGH);
      Serial.println("8 Yay");
    } else if(millis()-startTime > 25000) {
      level = 4;
      digitalWrite(8, LOW);
    } else if (millis()-startTime > 20000) {
      level = 3;
      digitalWrite(8, LOW);
    } else if (millis()-startTime > 15000) {
      level = 2;
      digitalWrite(8, LOW);
    } else if (millis()-startTime > 10000) {
      level = 1;
      digitalWrite(8, LOW);
    } else if (millis()-startTime > 5000) {
      level = 0;
      digitalWrite(8, LOW);
    }
  }
  
  currentState = digitalRead(11);
  
  if (state2 != currentState) { //If there is a change
    state2 = currentState;
    Serial.println("CHANGE TWO"); 
    lastChange2 = millis();
    active2 = true;
  }
  
  if (millis() - lastChange2 > 10000) {
    Serial.println("Reset TWO");
    active2 = false;
    lastChange2 = millis();
    level2--;
    if (level2 < 0) {level2 = 0;}
    startTime2 = millis();
    startTime2 -= (level2+1)*5000;
    digitalWrite(13, LOW);
  }
  
  if (active2) {
    if(millis()-startTime2 > 30000) {
      digitalWrite(13, HIGH);
      Serial.println("13 Yay");
    } else if(millis()-startTime2 > 25000) {
      level2 = 4;
      digitalWrite(13, LOW);
    } else if (millis()-startTime2 > 20000) {
      level2 = 3;
      digitalWrite(13, LOW);
    } else if (millis()-startTime2 > 15000) {
      level2 = 2;
      digitalWrite(13, LOW);
    } else if (millis()-startTime2 > 10000) {
      level2 = 1;
      digitalWrite(13, LOW);
    } else if (millis()-startTime2 > 5000) {
      level2 = 0;
      digitalWrite(13, LOW);
    }
  }
  
  turnOnLEDsAt(LEDsOn, level, level2);
  
  delay(100);
}
int leveltest = 0;
int leveltest2 = 0;
void turnOnLEDsAt(int LEDs[], int level, int level2){
  
  if (level != leveltest) {
    Serial.print("LEVEL1 At: ");
    Serial.println(level);
    leveltest = level;
  }
  if(level2 != leveltest2) {
    Serial.print("LEVEL2 At: ");
    Serial.println(level2);
    leveltest2 = level2;
  }
  //The level that is larger, did a complete loop before
  if(level > level2) {
    i = 0;
  } else if (level2 > level) {
    j = 0;
  } else { //if(level == level2)
    i = 0;
    j = 0;
  }
    
  for(int counter = 0; counter < max(level, level2)+1; counter++) {
    if (i>level) {
        i = 0;
      }
      if (j>level2) {
        j = 0;
      }
      turnOnLEDAt(i, j);
      i++;
      j++;
  }
}

void turnOnLEDAt(int pos, int pos2){
  int a, b, c;
  a = b = c = 0;
  
  // assume pos max is 8
  /*
  # -> cba
  0 -> 000
  1 -> 001
  2 -> 010
  3 -> 011
  4 -> 100
  5 -> 101
  6 -> 110
  7 -> 111
  */
  a = pos %2;
  b = ((int) (pos / 2)) % 2;
  c = pos / 4;
  
  digitalWrite(2, c);
  digitalWrite(3, b);
  digitalWrite(4, a);
  
  // assume pos2 max is 8
  a = pos2 %2;
  b = ((int) (pos2 / 2)) % 2;
  c = pos2 / 4;
  digitalWrite(5, c);
  digitalWrite(6, b);
  digitalWrite(7, a);
  
  
  digitalWrite(12, LOW);
//  digitalWrite(13, HIGH);
  delay(50);
  
  // These are some temporary commentsmore
}


