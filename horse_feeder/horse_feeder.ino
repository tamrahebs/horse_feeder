#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int relay_forwards_1 = 2;
int relay_backwards_1 = 3;

int relay_forwards_2 = 4;
int relay_backwards_2 = 5;

int relay_forwards_3 = 6;
int relay_backwards_3 = 7;

int relay_forwards_4 = 8;
int relay_backwards_4 = 9;

int OnHour_1 = 18;
int OnMin_1 = 43;
int OnSec_1 = 1;

int OnHour_2 = 18;
int OnMin_2 = 44;
int OnSec_2 = 1;

//int OffHour = 18;
//int OffMin = 45;
//int OffSec = 40;

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

// if the current time is the same as the OnHour and OnMin then play the song and extend and retract the linear actuator
  if(now.hour() == OnHour_1 && now.minute() == OnMin_1 && now.second() == OnSec_1){
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

 OnMin_1 = OnMin_1 + 2;

 if(OnMin_1 == 60){
      ++OnHour_1;
//      ++OffHour;
      OnMin_1 = 0;
 //     OffMin = 0;
    }
    if(OnHour_1 == 24){
      OnHour_1 = 1;
 //     OffHour = 1;
    }
  }
  
 if(now.hour() == OnHour_2 && now.minute() == OnMin_2 && now.second() == OnSec_2){
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


 //digitalWrite(relay_forwards_1, LOW);

 //digitalWrite(relay_backwards_1, LOW);//Deactivate both relays to brake the motor

 //delay(2000);// wait 2 seconds

//Serial.println("Hold 2 seconds");
OnMin_2 = OnMin_2 + 2;
    //Serial.println("LIGHT ON");
  
   // else if(now.hour() == OffHour && now.minute() == OffMin && now.second() == OffSec){
    //  digitalWrite(relay,HIGH); // turn relay OFF
    //  Serial.println("LIGHT OFF");
    //  OnMin = OnMin + 2;
    //  ++OffMin;
   // }
    if(OnMin_2 == 60){
      ++OnHour_2;
//      ++OffHour;
      OnMin_2 = 0;
 //     OffMin = 0;
    }
    if(OnHour_2 == 24){
      OnHour_2 = 1;
 //     OffHour = 1;
    }
}

}
