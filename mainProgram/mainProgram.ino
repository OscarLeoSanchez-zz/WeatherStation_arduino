#define control_pin 9
#define rot_pin A0

int hits = 0;
float wheel_radius = 1;

volatile unsigned int current_time;
long time_interval = 1000;


float getSpeed(){
	float velocity = (hits*(wheel_radius*59))/(time_interval); 
	hits = 0;
	current_time = millis();
	return velocity;


}

void count () {
	hits++;
}

void setup () { 
	Serial.begin(9600);
	pinMode(rot_pin, INPUT); //
	attachInterrupt(0, count, CHANGE);
	current_time = millis();
	pinMode(control_pin, OUTPUT);

}

void loop (){
	int reader = analogRead(rot_pin);
	analogWrite(control_pin, 25);

	Serial.print(reader*0.36);	
	if (millis() >= current_time + time_interval){
		Serial.println(getSpeed());
	}
	
	delay(1000);
}	








