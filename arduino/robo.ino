#include <Servo.h>
#include <string.h>
#include <assert.h>

Servo servo;
const int begin_pos = 19;
const int end_pos = 100;

const int speaker_pin = 13;

const int m_leftp = 2; 
const int m_leftn = 3; 
const int m_rightp = 4; 
const int m_rightn = 5; 
const static float k = 1;
const int turn_time_max = 5000;

const int buffer_size = 256;
char buffer[buffer_size+1];

const int max_params = 5;

void setup(){
  Serial.begin(9600);
  // setup for servo
  servo.attach(9);
  servo.write(begin_pos);
  
  // setup for speaker
  pinMode(speaker_pin, OUTPUT);
  
  // setup for motor
  pinMode(m_leftp, OUTPUT);
  pinMode(m_leftn, OUTPUT);
  pinMode(m_rightp, OUTPUT);
  pinMode(m_rightn, OUTPUT);
}

void loop(){
  long bytes = Serial.available();
  while (bytes > 0) {
    int len = Serial.readBytesUntil('\n', buffer, buffer_size);
    buffer[len] = '\0';
    
    int num_args = 0;
    char *args[max_params];
    char *arg = strtok(buffer, " \n\r");
    while (arg != 0)
    {
      args[num_args++] = arg;
      arg = strtok(0, " \n\r");
    }
    
    // empty line
    if (num_args <= 0)
    {
      bytes -= len+1;
      continue;
    }
    
    char *cmd = args[0];
    if (strcmp(cmd, "mov") == 0 && (num_args == 2 || num_args == 3))
    {
      if (num_args == 2)
      {
        int dir = atoi(args[1]);
        move_straight(dir);
      }
      else
      {
        assert(num_args == 3);
        int dur = atoi(args[1]);
        int dir = atoi(args[2]);
        move_straight(dur, dir);
      } 
    }
    else if (strcmp(cmd, "snd") == 0)
    {
      play_sound();
    }
    else if ( strcmp(cmd, "turn") == 0 && (num_args == 2 || num_args == 3))
    {
      if (num_args == 2)
      {
        int angle = atoi(args[1]);
        turn(angle);
      }
      else
      {
        int angle = atoi(args[1]);
        int dir = atoi(args[2]);
        turn(angle, dir);
      } 
    }
    else if ( strcmp(cmd, "serve") == 0 )
    {
      play_sound();
      dispense();
    }
    else if ( strcmp(cmd, "stop") == 0)
    {
      stop_motors();
    }
    else 
    {
      Serial.print("Unkown: \'");
      print_str_arr(args, num_args);
      Serial.println("\'");
    }
    
    bytes -= len + 1;
  }
}

void dispense()
{
  Serial.println("Dispensing");
  
  int pos = begin_pos;
  for (; pos <= end_pos; pos += 1) {
    servo.write(pos);
    delay(15); 
  }
  
  for (pos = end_pos; pos >= begin_pos; pos -= 1) { 
    servo.write(pos);
    delay(15); 
  }       
}

void play_sound()
{
  Serial.println("Playing sound");
  
  digitalWrite(speaker_pin, HIGH);
  delay(2000);
  digitalWrite(speaker_pin, LOW);
  //delay(2000);
}

void stop_motors() {
  left_motors(0);
  right_motors(0);
}

void move_straight(int dir)
{
  move_straight(-1, dir);
}


void move_straight(int duration, int dir)
{
  Serial.println("Moving straight");
  Serial.println(duration);
  Serial.println(dir);
  
  left_motors(dir);
  right_motors(dir);
  
  if (duration < 0) {
    return;
  }
  
  delay(duration);
  left_motors(0);
  right_motors(0);
}


void turn(int angle)
{
  turn(angle, 1);
}

// dir: 1 for cc, -1 of ccw
void turn(int angle, int dir){
  Serial.println("Turning");
  Serial.println(angle);
  Serial.println(dir);
  
  int left = dir;
  int right = dir;

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
  
  Serial.print("turn time: ");
  Serial.println(turn_time);
  delay(turn_time);
  
  left_motors(0);
  right_motors(0);
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

void print_str_arr(char **arr, int len)
{
  for( int i = 0; i < len; i++)
  {
    Serial.print(arr[i]);
    if (i < len-1) {
      Serial.print(' ');
    }
  }
}
