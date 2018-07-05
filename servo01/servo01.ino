volatile unsigned long pwm;
volatile boolean done;
unsigned long start;

unsigned long currentMillis;

long previousMillis = 0;    // set up timers
long interval = 20;        // time constant for timers

void setup() {
  pinMode(2, INPUT);
  attachInterrupt(0, timeit, CHANGE);
  
  Serial.begin(115200);

}


void timeit() {
    if (digitalRead(2) == HIGH) {
      start = micros();
    }
    else {
      pwm = micros() - start;
      done = true;
    }
  }


void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {  //start timed event
      previousMillis = currentMillis;
      
      if (!done)
          return;                         
      Serial.println (pwm);
      done = false;      

  } // end of timed event

}



