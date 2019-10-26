int motor1p=3;
int motor1n=5;
int motor2p=10;
int motor2n=11;

void setup() {
  pinMode(motor1p,OUTPUT);
  pinMode(motor1n,OUTPUT);
  pinMode(motor2n,OUTPUT);
  pinMode(motor2p,OUTPUT);
}

void loop() {
  Serial.begin(9600);
  digital_pwm(motor2p, 1, 3000);
  exit(0);
}


void digital_pwm(int pin, float duty, int duration){
  const static float freq = 20;
  const static int period = (int)(1000.0/freq);
  
  // number of ms of high signal over 1s
  int total_high_time = (int)(duty*1000.0);
  // number of ms of low signal over 1s
  int total_low_time = 1000 - total_high_time;
  
  int pulses = duration/period;

  // ms of high/low signal per pulse
  int high_time = total_high_time/freq;
  int low_time = total_low_time/freq;

  for(int i =0; i < pulses; i++){
    digitalWrite(pin, HIGH);
    delay(high_time);
    digitalWrite(pin, LOW);
    delay(low_time);
  }
}