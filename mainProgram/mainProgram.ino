#include <stdint.h>
#include "SparkFunBME280.h"
#include "Wire.h"
#include "SPI.h"


int var1=0;       // Temperatura  grados celsius
int var2=0;       // Humedad  %  
int var3=0;       // Presion hPa  
int var4=1000;    // Velocidad viento  m/s  
int var5=4;       // Direccion    
int var6=500;     // Radiacion W/m2  


//Variables encoder direccion
#define pinDirection A0

//Variables sensor radiacion
#define pinRadiation A1

//Variables encoder velocidad
int hits = 0;
float wheel_radius = 1;
volatile unsigned int current_time;
long time_interval = 500;
 
//Variables sensor BME280

BME280 sensorPHT;


//Funciones encoder velocidad
int getSpeed(){
	int velocity = (hits*(wheel_radius*59)*0.01)/(time_interval); 
	hits = 0;
	current_time = millis();
	return velocity;
}

void count () {
	hits++;
}

//Funciones encoder direccion
int getDirection(){
        int reader = analogRead(pinDirection);
        if       (reader >=0 && reader < 32 )  return 1;
        else if (reader >=32 && reader < 96 ) return 2;
        else if (reader >=96 && reader < 160 ) return 3;
        else if (reader >=160 && reader < 224 ) return 4;
        else if (reader >=224 && reader < 288 ) return 5;
        else if (reader >=288 && reader < 352 ) return 6;
        else if (reader >=352 && reader < 416 ) return 7;
        else if (reader >=416 && reader < 480 ) return 8;
        else if (reader >=480 && reader < 544 ) return 9;
        else if (reader >=544 && reader < 607 ) return 10;
        else if (reader >=607 && reader < 671 ) return 11;
        else if (reader >=671 && reader < 735 ) return 12;
        else if (reader >=735 && reader < 799 ) return 13;
        else if (reader >=799 && reader < 863 ) return 14;
        else if (reader >=863 && reader < 927 ) return 15;
        else if (reader >=927 && reader < 991 ) return 16;
        return 1;        
}

//Funciones sensor radiacion

int getRadiation(){
  int rad = (analogRead(pinRadiation)*3*4.8)+30;
  return rad;
}

//Funciones programa

String getLenMsg(){
  String var1S;
  String var2S;
  String var3S;
  String var4S;
  String var5S;
  String var6S;
  String msg;
  var1S=var1S+var1;
  var2S=var2S+var2;
  var3S=var3S+var3;
  var4S=var4S+var4;
  var5S=var5S+var5;
  var6S=var6S+var6;
  msg=msg+var1S.length()+","+var2S.length()+","+var3S.length()+","+var4S.length()+","+var5S.length()+","+var6S.length();
  return msg; 
}


String getMsg(){
  String mes;
  mes=mes+var1+","+var2+","+var3+","+var4+","+var5+","+var6;
  return mes;
}

void setup () { 
	Serial.begin(9600);
	pinMode(pinDirection, INPUT); //
  pinMode(pinRadiation, INPUT);
	attachInterrupt(1, count, CHANGE);
	current_time = millis();
  sensorPHT.settings.commInterface = SPI_MODE;
  sensorPHT.settings.chipSelectPin = 10;  // 53--> Arduino Mega     10-->Arduino Uno
  sensorPHT.settings.runMode = 3; //  3, Normal mode
  sensorPHT.settings.tStandby = 0; //  0, 0.5ms
  sensorPHT.settings.filter = 0; //  0, filter off
  sensorPHT.settings.tempOverSample = 1;
  sensorPHT.settings.pressOverSample = 1;
  sensorPHT.settings.humidOverSample = 1;
  delay(10);
  sensorPHT.begin();
}

void loop (){	
  var1 = sensorPHT.readTempC();
  var2 = sensorPHT.readFloatHumidity();
  var3 = sensorPHT.readFloatPressure()/100;
  var5 = getDirection();
  var6 = getRadiation();
  String mesLen = getLenMsg();
  String text=getMsg();
	if (millis() >= current_time + time_interval){
		var4=getSpeed();
	}
  while (Serial.available()) { 
      char order = Serial.read(); 
      if(order = '1'){
        Serial.print(mesLen);
        Serial.print(text); 
      }   
   }
}	








