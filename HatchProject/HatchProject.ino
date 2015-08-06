unsigned long startTime;
unsigned long startTime2;
int state = 0;
int state2 = 0;
int count = 0;
int count2 = 0;
int LEDsOn[] = {0,1,2,3,4,5};
int LEDsOn2[] = {0,1,2,3,4,5};
int currentState; //reusable
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
  pinMode(13, OUTPUT);
  
  //Initializing start times
  startTime = millis();
  startTime2 = millis();
}

void loop() {
  
  currentState = digitalRead(10);
  if(millis()-startTime > 60000) {
    level = 5;
  } else if(millis()-startTime > 50000) {
    level = 4;
  } else if (millis()-startTime > 40000) {
    level = 3;
  } else if (millis()-startTime > 30000) {
    level = 2;
  } else if (millis()-startTime > 7000) {
    level = 1;
  } else if (millis()-startTime > 5000) {
    level = 0;
  }
  if (state != currentState) {
    state = currentState;
    Serial.println("CHANGE ONE");
    count = 0; 
  } else {
    count++;
  } 

  if (count > 50) {
    Serial.println("Reset");
    level = 0;
    startTime = millis();
    count = 0;
  } 
  
  currentState = digitalRead(11);
  if(millis()-startTime2 > 60000) {
    level2 = 5;
  } else if(millis()-startTime2 > 50000) {
    level2 = 4;
  } else if (millis()-startTime2 > 40000) {
    level2 = 3;
  } else if (millis()-startTime2 > 30000) {
    level2 = 2;
  } else if (millis()-startTime2 > 7000) {
    level2 = 1;
  } else if (millis()-startTime2 > 5000) {
    level2 = 0;
  }
  if (state2 != currentState) {
    state2 = currentState;
    Serial.println("CHANGE TWO");
    count2 = 0; 
  } else {
    count2++;
  } 

  if (count2 > 50) {
    Serial.println("Reset");
    level2 = 0;
    startTime2 = millis();
    count2 = 0;
  } 
  
  
  turnOnLEDsAt(LEDsOn, level, level2);
  
  delay(50);
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
    
  for(i; i < max(level, level2); i++){
    //The next two if statmenets are there for the lower level,
    //  so that the it keeps looping, even with the second one.
    if (i>level) {
      i = 0;
    }
    if (j>level2) {
      j = 0;
    }
    turnOnLEDAt(i, j);
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
  digitalWrite(13, HIGH);
  delay(50);
}


