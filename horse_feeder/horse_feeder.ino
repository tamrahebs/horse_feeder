#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int relay_forwards = 7;
int relay_backwards = 6;

int OnHour = 18;
int OnMin = 19;
int OnSec = 40;
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

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
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
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
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

  250, 125,
  //Rpeat of First Part
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
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(56000);
  if (! rtc.begin()){
    Serial.println("Couldn't find RTC");
    while (1);
  }
  pinMode(relay_forwards, OUTPUT);//set relay as an output

  pinMode(relay_backwards, OUTPUT);//set relay as an output
  digitalWrite(relay_forwards, HIGH);
  digitalWrite(relay_backwards, LOW);
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

// if the current time is the same as the OnHour and OnMin then turn the light on, else turn it off
  if(now.hour() == OnHour && now.minute() == OnMin && now.second() == OnSec){
    for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);}//delay is used so it doesn't go to the next loop before tone is finished playing
      
 digitalWrite(relay_forwards, LOW);

 digitalWrite(relay_backwards, HIGH);//Activate the relay one direction, they must be different to move the motor

 delay(12000); // wait 12 seconds

 Serial.println("Forward hold 12");
 

 digitalWrite(relay_forwards, HIGH);

 digitalWrite(relay_backwards, HIGH);//Deactivate both relays to brake the motor

 delay(2000);// wait 2 seconds

 Serial.println("hold 2 seconds");

 
 digitalWrite(relay_forwards, HIGH);

 digitalWrite(relay_backwards, LOW);//Activate the relay the other direction, they must be different to move the motor

 delay(12000);// wait 12 seconds

Serial.println("back 12 seconds");


 digitalWrite(relay_forwards, HIGH);

 digitalWrite(relay_backwards, HIGH);//Deactivate both relays to brake the motor

 delay(2000);// wait 2 seconds

Serial.println("Hold 2 seconds");
    //Serial.println("LIGHT ON");
  
   // else if(now.hour() == OffHour && now.minute() == OffMin && now.second() == OffSec){
    //  digitalWrite(relay,HIGH); // turn relay OFF
    //  Serial.println("LIGHT OFF");
      OnMin = OnMin + 2;
    //  ++OffMin;
   // }
    if(OnMin == 60){
      ++OnHour;
//      ++OffHour;
      OnMin = 0;
 //     OffMin = 0;
    }
    if(OnHour == 24){
      OnHour = 1;
 //     OffHour = 1;
    }
}

}
