#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int relay = 7;

int OnHour = 18;
int OnMin = 45;
int OnSec = 30;
int OffHour = 18;
int OffMin = 45;
int OffSec = 40;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(56000);
  if (! rtc.begin()){
    Serial.println("Couldn't find RTC");
    while (1);
  }
  pinMode(relay, OUTPUT); // connected to 7 terminal of Relay 
  digitalWrite(relay,HIGH);
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
    digitalWrite(relay,LOW); // turn relay ON
    Serial.println("LIGHT ON");
  }
    else if(now.hour() == OffHour && now.minute() == OffMin && now.second() == OffSec){
      digitalWrite(relay,HIGH); // turn relay OFF
      Serial.println("LIGHT OFF");
      ++OnMin;
      ++OffMin;
    }
    if(OnMin == 60){
      ++OnHour;
      ++OffHour;
      OnMin = 0;
      OffMin = 0;
    }
    if(OnHour == 24){
      OnHour = 1;
      OffHour = 1;
    }
}
