const int m_leftp = 3; 
const int m_leftn = 5; 

const int m_rightp = 10; 
const int m_rightn = 11; 

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m_leftp, OUTPUT);
  pinMode(m_leftn, OUTPUT);
  pinMode(m_rightp, OUTPUT);
  pinMode(m_rightn, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  turn_forward(360, 0.8, 0);
  delay(2000);

  turn_forward(180, 0.8, 0);
  delay(2000);

  turn_forward(360, 0.2, 0);
  delay(2000);
  
  turn_forward(90, 0.4, 0);
  delay(2000);

  turn_forward(180, 0.4, 0);
  delay(2000);

  turn_forward(360, 0.4, 0);
  delay(2000);

  turn_forward(90, -0.2, 0);
  delay(2000);

  turn_forward(180, -0.2, 0);
  delay(2000);

  turn_forward(360, -0.2, 0);
  delay(2000);
  
  turn_forward(90, -0.4, 0);
  delay(2000);

  turn_forward(180, -0.4, 0);
  delay(2000);

  turn_forward(360, -0.4, 0);
  delay(2000);

}

void turn_forward(int angle, float v, float after_v){
  float left_speed = v;
  float right_speed = v;
  const static float k = 1; // constant in [0, 1]
  const static float TURN_TIME = 1000;

  float diff = k*angle/360.0;
  if (diff < 0){
    left_speed += left_speed * diff;
  } else {
    right_speed += right_speed * -diff;
  }

  left_motors(left_speed);
  right_motors(right_speed);
  
  delay(TURN_TIME);
  left_motors(after_v);
  right_motors(after_v);
}

void left_motors(float duty_cycle) {
  if (duty_cycle < 0) {
    digital_pwm(m_leftp, duty_cycle);
  } else {
    duty_cycle = -duty_cycle;
    digital_pwm(m_leftn, duty_cycle);
  }
}

void right_motors(float duty_cycle) {
  if (duty_cycle < 0) {
    digital_pwm(m_rightp, duty_cycle);
  } else {
    duty_cycle = -duty_cycle;
    digital_pwm(m_rightn, duty_cycle);
  }
}

void digital_pwm(int pin, float dt){
  digital_pwm(pin, dt, 100);
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
  Serial.println(high_time);
  Serial.println(low_time);
  for(int i =0; i < pulses; i++){
    digitalWrite(pin, HIGH);
    delay(high_time);
    digitalWrite(pin, LOW);
    delay(low_time);
  }
}