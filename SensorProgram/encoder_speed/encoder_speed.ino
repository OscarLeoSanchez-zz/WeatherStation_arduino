#define control_pin 9

int hits = 0;
float wheel_radius = 1;
volatile unsigned int current_time;
long time_interval = 1000; //how often do you want to know velocity (milliseconds)


float getSpeed(){
      float velocity = (hits*(wheel_radius * 59))/time_interval;//the constant is 2*pi/40
      hits=0;
      current_time = millis();
      return velocity;
}

void count()
{
 hits++;
}

void setup ()
{
  Serial.begin(9600);
  attachInterrupt(0, count, CHANGE);
  current_time = millis();
  pinMode(control_pin, OUTPUT);
}

void loop ()
{
  analogWrite(control_pin, 25);
  if ( millis() >= current_time + time_interval)
  {
    Serial.println(getSpeed());
  }
}  
