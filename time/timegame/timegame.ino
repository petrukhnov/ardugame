/*
 * Game to teach arduino and programming
 * 28.02.2017 konstantin.petrukhnov@gmail.com
 */

int BUTTON_D6 = 12; //D6 is equivalent to contact 12 on arduino.

int STATE_READY = 0;
int STATE_RND_DELAY = 1;
int STATE_TIME_COUNT = 3;

int curState = 0;
int timeCount = 0;
int buttonPressed = 0;
int rndDelayCount = 0;

/*
 * Executed once after board get power (or new code uploaded)
 */
void setup() {
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(BUTTON_D6, INPUT_PULLUP); //2 contact button
  //indicate that game loaded
  blinkInternalLed(5);
}

/* 
 *  the loop function runs over and over again forever
 */
void loop() {

  //get button state
  buttonPressed = digitalRead(BUTTON_D6)==0; //pullup button return 0 if pressed

  if (curState==STATE_READY) {
    if (buttonPressed) {
      //show that timecounter about to start
      blinkInternalLedFast(3);
      //reset counter
      timeCount = 0;
      //go to next state
      curState = STATE_RND_DELAY;
      rndDelayCount = getRandom(5);

      Serial.println("game is ready, btn pressed");
    } else {
      //if button is not pressed, then just wait
      delay(10);
    }
    
  } else if (curState==STATE_RND_DELAY) {
    
    //check if falsestart
    if (buttonPressed) {
      //fail and goto  to ready state
      Serial.println("Button was pressed too early. GAME OVER.");
      delay(1000); 
      curState = STATE_READY;
    } 
    
    //if delay ended
    if (rndDelayCount<0) {
      //turn led on
      digitalWrite(LED_BUILTIN, LOW); 
      //go to next state
      curState = STATE_TIME_COUNT;     
    } else {
      //wait 1 ms
      delay(1);
      //reduce delay
      rndDelayCount = rndDelayCount-1;
    }
    
    
    
  }  else if (curState==STATE_TIME_COUNT) {
    
    //check putton
    if (buttonPressed) {
      //print result
      Serial.print("Result: "); //output as 1 row
      Serial.print(timeCount);
      Serial.println(" ms."); //println adds line break after string.
      //blink led to confirm press
      blinkInternalLed(5);
      //go to ready state
      curState = STATE_READY;
    } else {
      //inc time
      timeCount = timeCount + 1;
      //wait 1 ms
      delay(1); //shorter delay for more accuracy
    }
    
  }
  

}

// get random value between 1 and max multiplied by 1000 
int getRandom(int max) {
  return random(1,max)*1000;
}

void blinkInternalLedFast(int count) {
  for(int i = 0; i<count; i++){
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);                     
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(100);
  }
}

// blink led 1 or multiple times
void blinkInternalLed(int count) {
  for(int i = 0; i<count; i++){
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
    delay(250);                      // Wait for a 1/4 second
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(500);                      // Wait for 1/2 seconds (to demonstrate the active low LED)
  }
  
}
