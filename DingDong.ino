#include <Servo.h>

Servo servoMotor;

const int servo = 3;      //SERVO MOTOR PIN
const int buzzer = 10;    // BUZZER PIN
const int button = 11;                //BUTTON PIN
const int LDR1 = A0;         // LDR1 PIN
const int LDR2 = A1;         //LDR2 PIN

int buttonPushCounter = 0;   // counter for the number of button presses
int lastButtonState = 0;     // previous state of the button

int buttonState = 0;              //BUTTON STATE
int freq = 50;                   // Starting frequency
int LDR1Value = 0;               // variable to store the value coming from the sensor LDR1
int LDR2Value = 0;           // variable to store the value coming from the sensor LDR2

int numberOfPeople = 0;        // variable to store number of people inside room


void setup(){
    pinMode(buzzer, OUTPUT);
    pinMode(button, INPUT);
    servoMotor.attach(servo);
    
    Serial.begin(9600);
}

 
void loop(){
  
    buttonState = digitalRead(button);
    //Serial.print("Button is : ");
    //Serial.println(buttonState);
    LDR1Value = analogRead(LDR1);         
    //Serial.print("LDR 1 senses : ");
    //Serial.println(LDR1Value);          
    LDR2Value = analogRead(LDR2);
    //Serial.print("LDR 2 senses : ");
    //Serial.println(LDR2Value);
           

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {  
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {   
      Serial.println("off");
    }   
    delay(50);
  }
  lastButtonState = buttonState;
  if (buttonPushCounter % 2 == 0) {
    
            if( LDR1Value <= 200 && numberOfPeople < 5 ){
              
                  for( int angle = 0; angle <= 180; angle++ ){
                      servoMotor.write(angle);
                      delay(7);
                  }
              servoMotor.write(0);
              numberOfPeople=numberOfPeople+1;
              delay(1000);
              
            }else if( LDR2Value <= 200 && numberOfPeople <= 5 ){
              
                  for( int angle = 0; angle <= 180; angle++ ){
                      servoMotor.write(angle);
                      delay(7);
                  }
              servoMotor.write(0);              
              numberOfPeople=numberOfPeople-1;
              delay(1000);
              
            }else if( numberOfPeople >= 5 ){
              tone(buzzer, 1000); // Send 1.5KHz sound signal...
              delay(1000);
              noTone(buzzer);
              delay(1000);
            }
    
  } else {
    
             noTone(buzzer);     // Stop sound...
            for( int angle = 180; angle <= 0; angle-- ){
            servoMotor.write(angle);
            delay(7);
            }
  }
Serial.println(numberOfPeople);
}
