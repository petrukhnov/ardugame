int LED_1 = 4;
int INPUT_1 = 3;
int INPUT_2 = 13;

boolean input1Pressed = false;
boolean input2Pressed = false;

int STATE_PREP = 0;
int STATE_FALSE_START = 1;
int STATE_READY = 2;
int STATE_GAME = 3;
int STATE_RESULT = 4;

int curState = 0;
int winner = 0;

//setup function run once at the beginning
void setup() {
  //pin config
  pinMode(LED_1, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(INPUT_1, INPUT);
  pinMode(INPUT_2, INPUT);

  blinkLeds();
  blinkLeds();
  blinkLeds();
  
  digitalWrite(LED_1, LOW);  //HIGH is to disable led, LOW to enable
  digitalWrite(12, LOW); 
 
}

// the loop function runs over and over again forever
void loop() {

  if(STATE_PREP == curState) {
    //if both hold - blink and start
    if (digitalRead(INPUT_1) == HIGH && digitalRead(INPUT_2) == HIGH) {
      //set
      curState = STATE_READY;
    } 

  } else if (STATE_READY == curState) {  
    blinkLedsFast();
    if (digitalRead(INPUT_1) == LOW && digitalRead(INPUT_2) == LOW) {
      //leds off
      digitalWrite(LED_1, LOW);
      digitalWrite(12, LOW);
      //start after random delay
      waitRandom();
      curState = STATE_FALSE_START;
    }
    
  } else if (STATE_FALSE_START == curState) {
    //todo if pressed too early - other win
    boolean btn1 = (digitalRead(INPUT_1) == HIGH);
    boolean btn2 = (digitalRead(INPUT_2) == HIGH);
    if (btn2 && btn1) {
        curState = STATE_RESULT;
        winner = 0;
    } else if (btn1) {
      curState = STATE_RESULT;
      winner = 2;
    }  else if (btn2) {
      curState = STATE_RESULT;
      winner = 1;
    } else {
      curState = STATE_GAME;
      //leds on
      digitalWrite(LED_1, HIGH);
      digitalWrite(12, HIGH);
    }
    
  } else if (STATE_GAME == curState) {
    
    if (digitalRead(INPUT_1) == HIGH && digitalRead(INPUT_2) == HIGH) {
      //both player fast enough
      curState = STATE_RESULT; 
      winner = 0;
      disableLeds();
    } else if (digitalRead(INPUT_1) == HIGH) {
      curState = STATE_RESULT;
      winner = 1;
      disableLeds();
    }  else if (digitalRead(INPUT_2) == HIGH) {
      curState = STATE_RESULT;
      winner = 2;
      disableLeds();
    }
    
  } else if (STATE_RESULT == curState) {
    delay(3000);
    disableLeds(); 
    
    //set winner
    if (winner == 1) {
      digitalWrite(LED_1, HIGH);  
    } else if (winner == 2) {
      digitalWrite(12, HIGH); 
    } else {
      // draw
      enableLeds();
    }

    //wait 5 seconds
    delay(5000);

    //disable leds
    disableLeds();

    //reset game
    curState = STATE_PREP;
  } 

  delay(10); //wait 0.1 second
  
}

void waitRandom() {
  delay(random(1,5)*1000); //delay 1-5 seconds
}

void disableLeds(){
  digitalWrite(LED_1, LOW);  
  digitalWrite(12, LOW); 
}

void enableLeds(){
  digitalWrite(LED_1, HIGH);  
  digitalWrite(12, HIGH); 
}

void blinkLeds() {
  digitalWrite(LED_1, LOW);  
  digitalWrite(12, LOW);
  delay(500); 
  digitalWrite(LED_1, HIGH);  
  digitalWrite(12, HIGH); 
  delay(500); 
}

void blinkLedsFast() {
  for (int i = 0; i < 5; i++) {
    enableLeds();
    delay(100); 
    disableLeds();
    delay(100); 
   }
}


