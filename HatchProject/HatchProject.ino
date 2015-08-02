unsigned long startTime;
int state = 0;
int count = 0;
int LEDsOn[] = {0,1,2,3,4,5};
int currentState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //3 Inputs into the decoder to produce 8 Inputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  //The input of wheel excersize machine
  pinMode(10, INPUT);

  //The input of other excersize macine
  pinMode(11, INPUT);

  //G2A and G2B Low (Connected in circuitry)
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//  Serial.println("Starting");

  // UPDATE LEDsOn
//  Serial.println(sizeof(LEDsOn));
  //turnOnLEDsAt(LEDsOn);
//  delay(1000);

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
//    Serial.println(sizeof(LEDs));
//    Serial.print("LED ON:: ");
//    Serial.println(LEDs[i]);
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
  
////  Serial.print("a: ");
//  Serial.println(a);
////  Serial.print("b: ");
// Serial.println(b);
////  Serial.print("c: ");
//  Serial.println(c);
////  Serial.println("---------");
  if(machine == 1) {
    digitalWrite(2, c);
    digitalWrite(3, b);
    digitalWrite(4, a);
  } else if (machine == 2) {
    digitalWrite(5, c);
    digitalWrite(6, b);
    digitalWrite(7, a);
  }
//  digitalWrite(2, LOW);
//  digitalWrite(3, LOW);
//  digitalWrite(4, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(50);
}


