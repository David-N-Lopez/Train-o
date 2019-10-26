const int m_leftp = 2; 
const int m_leftn = 3; 

const int m_rightp = 4; 
const int m_rightn = 5; 

const static float k = 1; // constant in [0, 1]
const int turn_time_max = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m_leftp, OUTPUT);
  pinMode(m_leftn, OUTPUT);
  pinMode(m_rightp, OUTPUT);
  pinMode(m_rightn, OUTPUT);
}

void loop() {
  long bytes = Serial.available();
  if(bytes > 0) {
    long angle = Serial.parseInt();
    // read white space
    Serial.read();
    long v = Serial.parseInt();
    // read new line
    Serial.read();
    Serial.print("angle: ");
    Serial.println(angle);
    Serial.print("v: ");
    Serial.println(v);
    turn_forward(angle, v);
    Serial.println("\n");
  }
}

// after_v: -1 for backward, 1 for forward, 0 stop
void turn_forward(int angle, int after_v){
  
  
  int left = 1;
  int right = 1;

  int turn_time =(int) (k*turn_time_max*abs(angle)/360.0);
  if (angle < 0){
    left = 0;
  } else if (angle > 0){
    right = 0;
  } else {
    left = 0;
    right = 0;
  }

  left_motors(left);
  right_motors(right);
  
  Serial.println(turn_time);
  delay(turn_time);
  
  
  left_motors(after_v);
  right_motors(after_v);
}

void left_motors(int v) {
  if (v > 0)
  {
    digitalWrite(m_leftp, HIGH);
    digitalWrite(m_leftn, LOW);
  } 
  else if (v < 0) 
  {
    digitalWrite(m_leftp, LOW);
    digitalWrite(m_leftn, HIGH);
  } 
  else 
  {
    digitalWrite(m_leftp, LOW);
    digitalWrite(m_leftn, LOW);
  }
}

void right_motors(int v) {
  if (v > 0)
  {
    digitalWrite(m_rightp, HIGH);
    digitalWrite(m_rightn, LOW);
  } 
  else if (v < 0)
  {
    digitalWrite(m_rightp, LOW);
    digitalWrite(m_rightn, HIGH);
  }
  else 
  {
    digitalWrite(m_rightp, LOW);
    digitalWrite(m_rightn, LOW);
  }
}