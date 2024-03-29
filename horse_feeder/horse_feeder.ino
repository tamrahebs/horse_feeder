#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int switchPin_1 = 12; //the switch 1 to connect to pin 12
const int switchPin_2 = 13; //the switch 2 to connect to pin 13

int switchState_1 = 0;         // variable for reading the pushbutton status
int switchState_2 = 0;

const int relay_forwards_1 = 2;
const int relay_backwards_1 = 3;

const int relay_forwards_2 = 4;
const int relay_backwards_2 = 5;

const int relay_forwards_3 = 6;
const int relay_backwards_3 = 7;

const int relay_forwards_4 = 8;
const int relay_backwards_4 = 9;

const int OnHour_1 = 19;
const int OnMin_1 = 5;
const int OnSec_1 = 40;

const int OnHour_2 = 19;
const int OnMin_2 = 6;
const int OnSec_2 = 40;

//for the song to play setup code 
const int buzzer = 10; //Define pin 10, can use other PWM pins  (5,6 or 9)
                       //Note pins 3 and 11 can't be used when using the tone function in Arduino Uno
const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song

//*****************************************
#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
//*****************************************
int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
};
//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(56000);
  if (! rtc.begin()){
    Serial.println("Couldn't find RTC");
    while (1);
  }
  pinMode(switchPin_1, INPUT); //initialize thebuttonPin as input
  pinMode(switchPin_2, INPUT); //initialize thebuttonPin as input
 
  pinMode(relay_forwards_1, OUTPUT);//set relay as an output
  pinMode(relay_backwards_1, OUTPUT);//set relay as an output
  digitalWrite(relay_forwards_1, LOW);
  digitalWrite(relay_backwards_1, HIGH);
  
  pinMode(relay_forwards_2, OUTPUT);//set relay as an output
  pinMode(relay_backwards_2, OUTPUT);//set relay as an output
  digitalWrite(relay_forwards_2, LOW);
  digitalWrite(relay_backwards_2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now(); // get current time
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay (1000);
  
//read the state of the switch value
  switchState_1 = digitalRead(switchPin_1);
  
// if the current time is the same as the OnHour and OnMin then play the song and extend and retract the linear actuator
  if(now.hour() == OnHour_1 && now.minute() == OnMin_1 && now.second() == OnSec_1){
    if (switchState_1 == HIGH ) { //if it is,the state is HIGH
    for (int i=0;i<76;i++){              //203 is the total number of music notes in the song
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);}//delay is used so it doesn't go to the next loop before tone is finished playing
      
 digitalWrite(relay_forwards_1, HIGH);
 digitalWrite(relay_backwards_1, LOW);//Activate the relay one direction, they must be different to move the motor
 delay(12000); // wait 12 seconds
 Serial.println("hold 10 seconds");
 

 digitalWrite(relay_forwards_1, LOW);
 digitalWrite(relay_backwards_1, LOW);//Deactivate both relays to brake the motor
 delay(10000);// wait 10 seconds


 digitalWrite(relay_forwards_1, LOW);
 digitalWrite(relay_backwards_1, HIGH);//Activate the relay the other direction, they must be different to move the motor
 delay(12000);// wait 12 seconds

// OnMin_1 = OnMin_1 + 2;

 //if(OnMin_1 == 60){
  //    ++OnHour_1;
   //   OnMin_1 = 0;
   // }
   // if(OnHour_1 == 24){
   //   OnHour_1 = 1;
   // }
  }
  else {
  digitalWrite(relay_forwards_1, LOW);
  digitalWrite(relay_backwards_1, HIGH);
  Serial.println("Skip me!");
  }
  }  

 switchState_2 = digitalRead(switchPin_2);

 if(now.hour() == OnHour_2 && now.minute() == OnMin_2 && now.second() == OnSec_2){
  if (switchState_2 == HIGH ) { //if it is,the state is HIGH 
    for (int i=0;i<76;i++){              //203 is the total number of music notes in the song
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);}//delay is used so it doesn't go to the next loop before tone is finished playing
      
 digitalWrite(relay_forwards_2, HIGH);
 digitalWrite(relay_backwards_2, LOW);//Activate the relay one direction, they must be different to move the motor
 delay(12000); // wait 12 seconds
 Serial.println("hold 10 seconds");
 

 digitalWrite(relay_forwards_2, LOW);
 digitalWrite(relay_backwards_2, LOW);//Deactivate both relays to brake the motor
 delay(10000);// wait 10 seconds


 digitalWrite(relay_forwards_2, LOW);
 digitalWrite(relay_backwards_2, HIGH);//Activate the relay the other direction, they must be different to move the motor
 delay(12000);// wait 12 seconds

//OnMin_2 = OnMin_2 + 2;
    //Serial.println("LIGHT ON");
  
   // else if(now.hour() == OffHour && now.minute() == OffMin && now.second() == OffSec){
    //  digitalWrite(relay,HIGH); // turn relay OFF
    //  Serial.println("LIGHT OFF");
    //  OnMin = OnMin + 2;
    //  ++OffMin;
   // }
    //if(OnMin_2 == 60){
    //  ++OnHour_2;
    //  OnMin_2 = 0;
   // }
   // if(OnHour_2 == 24){
   //   OnHour_2 = 1;
   // }
}
else {
  digitalWrite(relay_forwards_2, LOW);
  digitalWrite(relay_backwards_2, HIGH);
  Serial.println("Skip me!");
  }
 }

}
