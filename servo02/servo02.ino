#include <PID_v1.h>  //PID loop from http://playground.arduino.cc/Code/PIDLibrary

double Pk1 = 1;  //speed it gets there
double Ik1 = 0;
double Dk1 = 0;

double Setpoint1, Input1, Output1, Output1a;    // PID variables

PID PID1(&Input1, &Output1, &Setpoint1, Pk1, Ik1 , Dk1, DIRECT);    // PID Setup

volatile unsigned long pwm;
volatile boolean done;
unsigned long start;

int pot;

unsigned long currentMillis;

long previousMillis = 0;    // set up timers
long interval = 20;        // time constant for timers

void setup() {
  pinMode(2, INPUT);
  pinMode(A0, INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  attachInterrupt(0, timeit, CHANGE);
  
  Serial.begin(115200);

  PID1.SetMode(AUTOMATIC);              // PID Setup - trousers SERVO
  PID1.SetOutputLimits(-255, 255);
  PID1.SetSampleTime(20);

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

      pot = analogRead(A0);
      Serial.print(pot);
      Serial.print(" , ");
      Serial.print (pwm);
      Serial.print(" , ");

      Input1 = map(pwm,1000,2000,-255,255);
      Setpoint1 = map(pot,0,1023,-255,255);
      PID1.Compute();

      Serial.println(Output1);    

      if (Output1 > 0) {
        analogWrite(5, Output1);
        analogWrite(6, 0);
      }
      else if (Output1 < 0) {
        Output1a = abs(Output1);
        analogWrite(5, 0);
        analogWrite(6, Output1a);
      }

      
      
      if (!done)
            return;               
            done = false;   
     
  } // end of timed event

}



