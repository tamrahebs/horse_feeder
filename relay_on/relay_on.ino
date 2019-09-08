int relay = 7;
int on_time = 5000;
int on_time_s = on_time/1000;
int off_time = 2000;
int off_time_s = off_time/1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(56000);
  pinMode(relay, OUTPUT); // connected to 7 terminal of Relay 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay,LOW); // turn relay ON
  Serial.print("I am on for ");
  Serial.print(on_time_s);
  Serial.println(" seconds");
  delay(on_time); // keep it ON for on_time in seconds
  digitalWrite(relay,HIGH); // turn relay OFF
  Serial.print("I am off for ");
  Serial.print(off_time_s);
  Serial.println(" seconds");
  delay(off_time); // keep it OFF for off_time in seconds
}
