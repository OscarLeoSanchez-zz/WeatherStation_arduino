#define rot_pin A0


void setup() {
Serial.begin(9600);
pinMode(rot_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reader=analogRead(rot_pin);
  Serial.println(reader*0.36);
  delay(1000); 
}
