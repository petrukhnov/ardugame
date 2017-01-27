

int LED_1 = 12;
int INPUT_1 = 13; //avoid digital pins 0,1 for 2 pin buttons
int INPUT_2 = 0;

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
  pinMode(5, OUTPUT);
  pinMode(INPUT_1, INPUT_PULLUP);
  pinMode(INPUT_2, INPUT_PULLUP); //INPUT_PULLUP is for 2 pin buttons

  //blink 3 times to indicate that code is loaded
  blinkLeds();
  blinkLeds();
  blinkLeds();
 
}

// the loop function runs over and over again forever
// for 2 pin buttons, LOW and HIGH is reveresed (pressed button circuit input to ground, which means LOW)
void loop() {

  if(STATE_PREP == curState) {
    //if both hold - blink and start
    if (digitalRead(INPUT_1) == LOW && digitalRead(INPUT_2) == LOW) {
      //set
      curState = STATE_READY;
    } 

  } else if (STATE_READY == curState) {  
    blinkLedsFast();
    if (digitalRead(INPUT_1) != LOW && digitalRead(INPUT_2) != LOW) {
      //leds off
      digitalWrite(LED_1, LOW);
      digitalWrite(5, LOW);
      //start after random delay
      waitRandom();
      curState = STATE_FALSE_START;
    }
    
  } else if (STATE_FALSE_START == curState) {
    //todo if pressed too early - other win
    boolean btn1 = (digitalRead(INPUT_1) == LOW);
    boolean btn2 = (digitalRead(INPUT_2) == LOW);
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
      digitalWrite(5, HIGH);
    }
    
  } else if (STATE_GAME == curState) {
    
    if (digitalRead(INPUT_1) == LOW && digitalRead(INPUT_2) == LOW) {
      //both player fast enough
      curState = STATE_RESULT; 
      winner = 0;
      disableLeds();
    } else if (digitalRead(INPUT_1) == LOW) {
      curState = STATE_RESULT;
      winner = 1;
      disableLeds();
    }  else if (digitalRead(INPUT_2) == LOW) {
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
      digitalWrite(5, HIGH); 
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
  digitalWrite(5, LOW); 
}

void enableLeds(){
  digitalWrite(LED_1, HIGH);  
  digitalWrite(5, HIGH); 
}

void blinkLeds() {
  digitalWrite(LED_1, HIGH);  
  digitalWrite(5, HIGH); 
  delay(500);
  digitalWrite(LED_1, LOW);  
  digitalWrite(5, LOW);
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


