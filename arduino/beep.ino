const int speaker_pin = 13;

void setup(){
  Serial.begin(9600);
  pinMode(speaker_pin, OUTPUT);
}

void loop(){
  //beep(5000);
  digitalWrite(speaker_pin,HIGH);
  delay(2000);
  digitalWrite(speaker_pin,LOW);
  delay(2000);
}

void beep(int duration)
{
  const int freq = 250;
  int period = (int)(1000.0/freq);
  int pulses = duration/period;
  int high_time = period/2;
  
  for(int i = 0; i < pulses; i++){
    digitalWrite(speaker_pin, HIGH);
    delay(high_time);
    digitalWrite(speaker_pin, LOW);
  }
}