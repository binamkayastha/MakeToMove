unsigned long startTime;
unsigned long startTime2;
int state = 0;
int count2 = 0;
int count = 0;
int count2 = 0;
int LEDsOn[] = {0,1,2,3,4,5};
int LEDsOn2[] = {0,1,2,3,4,5};
int currentState; //reusable

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
  pinMode(10, INPUT);

  //The input of other excersize macine
  pinMode(11, INPUT);

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
    turnOnLEDsAt(LEDsOn, 5);
  } else if(millis()-startTime > 50000) {
    turnOnLEDsAt(LEDsOn, 4);
  } else if (millis()-startTime > 40000) {
    turnOnLEDsAt(LEDsOn, 3);
  } else if (millis()-startTime > 30000) {
    turnOnLEDsAt(LEDsOn, 2);
  } else if (millis()-startTime > 7000) {
    turnOnLEDsAt(LEDsOn, 1);
  } else if (millis()-startTime > 5000) {
    turnOnLEDsAt(LEDsOn, 0);
  }
  if (state != currentState) {
    state = currentState;
    count = 0; 
  } else {
    count++;
  } 

  if (count > 50) {
    Serial.println("Reset");
    turnOnLEDsAt(LEDsOn, 0);
      
    startTime = millis();
    count = 0;
  } 
  
  delay(25);
}

void turnOnLEDsAt(int LEDs[], int level){
  Serial.print("At LEVEL: ");
  Serial.println(level);
  for(int i=0; i < level+1; i++){
    turnOnLEDAt(LEDs[i]);
  }
}

void turnOnLEDAt(int pos, int machine){
  int a, b, c;
  a = b = c = 0;
  
  // assume pos max is 8
  a = pos %2;
  b = ((int) (pos / 2)) % 2;
  c = pos / 4;
  
  if(machine == 1) {
    digitalWrite(2, c);
    digitalWrite(3, b);
    digitalWrite(4, a);
  } else if (machine == 2) {
    digitalWrite(5, c);
    digitalWrite(6, b);
    digitalWrite(7, a);
  }
  
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(50);
}


