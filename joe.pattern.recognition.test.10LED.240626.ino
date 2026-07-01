//TESTED AND WORKING Simon Says Game, joeljai. circuit construction same as 4bit binary adder
//input pins for buttons
const int pinb0 = A0;
const int pinb1 = A1;
const int pinb2 = A2;
const int pinb3 = A3;
const int pinbStart = A4;
// for outputing the random pattern digits - yellow
const int pinOb0 = 6;
const int pinOb1 = 7;
const int pinOb2 = 8;
const int pinOb3 = 9;

const int pinOb[] = {pinOb0,pinOb1,pinOb2,pinOb3};

//for outputting the inputted answer pattern from user - red
const int pinAnsb0 = 2;
const int pinAnsb1 = 3;
const int pinAnsb2 = 4;
const int pinAnsb3 = 5;

const int pinAnsb[] = {pinAnsb0,pinAnsb1,pinAnsb2,pinAnsb3};

//random seed pin
const int pinRandom = A5;

//control LED - green
const int pinControlLED = 12;

//timer LED - rightmost red 
const int pinTimer = 10;

//last states for the buttons
int blaststate[] = {HIGH,HIGH,HIGH,HIGH,HIGH};

//timing for green control LED 
bool toggleCLED = true;
int counterC = 0;
int counterCMax = 3;

//timing for red timing led
bool toggleTLED = false;
int counterT = 0;

//timing counters or bools
bool start = false;
bool seqEnd = false;
int ms = 500;

//for output rand pattern
bool startPatternO = false;
bool endPatternO = false;
int outputTimer = -1;
const int maxPattern = 3; 
int generatedPattern[maxPattern][4];

//for input
bool inputmode = false;
int Ans0 = 0;int Ans1 = 0;int Ans2 = 0;int Ans3 = 0;
int counterAns = 0;
int answerPattern[maxPattern][4];
bool end = false;

//win check
bool win = true;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A5));

  pinMode(pinb0, INPUT_PULLUP);
  pinMode(pinb1, INPUT_PULLUP);
  pinMode(pinb2, INPUT_PULLUP);
  pinMode(pinb3, INPUT_PULLUP);
  pinMode(pinbStart, INPUT_PULLUP);

  pinMode(pinOb0, OUTPUT);
  pinMode(pinOb1, OUTPUT);
  pinMode(pinOb2, OUTPUT);
  pinMode(pinOb3, OUTPUT);

  pinMode(pinAnsb0, OUTPUT);
  pinMode(pinAnsb1, OUTPUT);
  pinMode(pinAnsb2, OUTPUT);
  pinMode(pinAnsb3, OUTPUT);
  pinMode(pinTimer, OUTPUT);

  pinMode(pinControlLED, OUTPUT);
}

void loop() {

  //controlLED green func
  counterC += 1;
  if (counterC >= counterCMax) {
    counterC = 0;
    toggleCLED = !toggleCLED;
  }
  digitalWrite(pinControlLED, toggleCLED);

  int bStartstate = digitalRead(pinbStart);
  if (blaststate[4] == HIGH && bStartstate == LOW){
    if (!start)
      start = true;
  }

  if (start && !seqEnd) {
    startSeq();
    startPatternO = true;
    seqEnd = true;
  }

  if (outputTimer >= maxPattern && !endPatternO) { //+1 FOR MAXPATTERN
    endPatternO = true;
    delay(500);
    clearOutputLED();
    digitalWrite(pinTimer, LOW);
    delay(500);
    counterCMax = 1;
    counterC = 0;
    inputmode = true;
    ms = 100;
  }

  if (inputmode) {
    if (!end) {
      input(Ans0, Ans1, Ans2, Ans3);
      outputans(Ans0, Ans1, Ans2, Ans3);
      if (counterAns < maxPattern)  {
        if (blaststate[4] == HIGH && bStartstate == LOW){
          storeAnsPattern(counterAns);
          clearAnsLED();
          counterAns += 1;
          Serial.println(counterAns);
        }
      }else{
          wincheck();
          end = true;
          endGame();
          ms = 1500;
      }
    }
  }

  if (startPatternO && !endPatternO) {
    //timing LED func
    counterT += 1;
    if (counterT >= 2) {
      counterT = 0;
      toggleTLED = !toggleTLED;
      outputTimer += 1;
    digitalWrite(pinTimer, toggleTLED);
    if (outputTimer < maxPattern) {
      outputRandPattern(outputTimer);
    }
   }
  }
  blaststate[4] = bStartstate;
  //debug("countercmax");
  delay(ms);
}

void startSeq() {
  int prev = 0;
  for (unsigned int j = 0; j < 2; j++) {
    for (unsigned i = 0; i < 4; i++) {
      digitalWrite(pinOb[3 - prev], LOW);
      digitalWrite(pinAnsb[prev], LOW);
      digitalWrite(pinOb[3 - i], HIGH);
      digitalWrite(pinAnsb[i], HIGH);
      prev = i;
      delay(400);
    }
  digitalWrite(pinOb[0], LOW);
  digitalWrite(pinAnsb[3], LOW);
  }
  delay(300);
  for (unsigned i = 0; i < maxPattern; i++) {
    digitalWrite(pinAnsb3, HIGH);
    delay(200);
    digitalWrite(pinAnsb3, LOW);
    delay(200);
  }
}

void outputRandPattern(int row) {
  int randomList[] = {0,0,0,0};
  randomize(randomList);
  for (unsigned int col = 0; col < 4; col++) {
      generatedPattern[row][col] = randomList[col];
      Serial.print(generatedPattern[row][col]);
  }
  Serial.println(row);
  Serial.println();
  digitalWrite(pinOb0, randomList[0]);
  digitalWrite(pinOb1, randomList[1]);
  digitalWrite(pinOb2, randomList[2]);
  digitalWrite(pinOb3, randomList[3]);
}

void randomize(int interlist[4]) {
  bool allZeros = true;
  for (unsigned int r = 0; r < 4; r++) {
    interlist[r] = random(2);
    if (interlist[r] == 1) {
      allZeros = false;
    }
  }
  if (allZeros) {
    randomize(interlist);
  }
}

void clearOutputLED() {
  digitalWrite(pinOb0, LOW);
  digitalWrite(pinOb1, LOW);
  digitalWrite(pinOb2, LOW);
  digitalWrite(pinOb3, LOW);
}

void clearAnsLED() {
  digitalWrite(pinAnsb0, LOW);
  digitalWrite(pinAnsb1, LOW);
  digitalWrite(pinAnsb2, LOW);
  digitalWrite(pinAnsb3, LOW);
  Serial.println("cleared pins");
}

void illumOutputLED() {
  digitalWrite(pinOb0, HIGH);
  digitalWrite(pinOb1, HIGH);
  digitalWrite(pinOb2, HIGH);
  digitalWrite(pinOb3, HIGH);
}

void illumAnsLED() {
  digitalWrite(pinAnsb0, HIGH);
  digitalWrite(pinAnsb1, HIGH);
  digitalWrite(pinAnsb2, HIGH);
  digitalWrite(pinAnsb3, HIGH);
}

void debug(String option) {
  if (option == "patt") {
    for (int i = 0; i < maxPattern; i++) {
      Serial.println("");
      for (int j = 0; j < 4; j++){
        Serial.print(generatedPattern[i][j]);
      }
    }
  }else{
    if (option == "countercmax") {
      Serial.println(counterCMax);
      Serial.println("next");
    }
  }
}

void input(int &Ans0, int &Ans1, int &Ans2, int &Ans3) {
  int bstate[] = {digitalRead(pinb0), digitalRead(pinb1), digitalRead(pinb2), digitalRead(pinb3)};
  if (bstate[0] == LOW && blaststate[0] == HIGH) {
    Ans0 = !Ans0;
  }
  if (bstate[1] == LOW && blaststate[1] == HIGH) {
    Ans1 = !Ans1;
  }
  if (bstate[2] == LOW && blaststate[2] == HIGH) {
    Ans2 = !Ans2;
  }
  if (bstate[3] == LOW && blaststate[3] == HIGH) {
    Ans3 = !Ans3;
  }

  for (unsigned i = 0; i < 4; i++) {
    blaststate[i] = bstate[i];
  }
}

void outputans(int Ans0, int Ans1, int Ans2, int Ans3) {
  digitalWrite(pinAnsb0, Ans0);
  digitalWrite(pinAnsb1, Ans1);
  digitalWrite(pinAnsb2, Ans2);
  digitalWrite(pinAnsb3, Ans3);
}

void storeAnsPattern(int row2) {
  Serial.println("written");
  answerPattern[row2][0] = Ans0; 
  answerPattern[row2][1] = Ans1; 
  answerPattern[row2][2] = Ans2; 
  answerPattern[row2][3] = Ans3; 
  Ans0 = 0;Ans1 = 0;Ans2 = 0;Ans3 = 0;
}

void wincheck() {
  for (unsigned int row = 0; row < maxPattern; row++) {
    for (unsigned int col = 0; col < 4; col++) {
      Serial.print(generatedPattern[row][col]);
      Serial.print(" is being compared with input ");
      Serial.println(answerPattern[row][col]);
      if (generatedPattern[row][col] != answerPattern[row][col]) {
        win = false;
        //Serial.println("lost");
      }
    }
  }
  if (win) {
    Serial.println("winnn");
  }
}

void endGame() {
  for (unsigned int i = 0; i < 3; i++) {
    if (win) {
      illumOutputLED();
      illumAnsLED();
      digitalWrite(pinTimer, HIGH);
    }else{
      digitalWrite(pinAnsb[i], HIGH);
    }
    delay(300);
    if (win) {
      clearOutputLED();
      clearAnsLED();
      digitalWrite(pinTimer, LOW);
    }else{
      digitalWrite(pinAnsb[i], LOW);
    }
    delay(300);

  }
  digitalWrite(pinTimer, LOW);
}