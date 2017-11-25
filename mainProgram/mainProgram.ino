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

String getDirecction(){
        int reader = analogRead(rot_pin);
        if       (reader >=0 && reader < 32 )  return "N";
        else if (reader >=32 && reader < 96 ) return "NNE";
        else if (reader >=96 && reader < 160 ) return "NE";
        else if (reader >=160 && reader < 224 ) return "ENE";
        else if (reader >=224 && reader < 288 ) return "E";
        else if (reader >=288 && reader < 352 ) return "ESE";
        else if (reader >=352 && reader < 416 ) return "SE";
        else if (reader >=416 && reader < 480 ) return "SSE";
        else if (reader >=480 && reader < 544 ) return "S";
        else if (reader >=544 && reader < 607 ) return "SSO";
        else if (reader >=607 && reader < 671 ) return "SO";
        else if (reader >=671 && reader < 735 ) return "OSO";
        else if (reader >=735 && reader < 799 ) return "O";
        else if (reader >=799 && reader < 863 ) return "ONO";
        else if (reader >=863 && reader < 927 ) return "NO";
        else if (reader >=927 && reader < 991 ) return "NNO";
        return "N";        
        
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








