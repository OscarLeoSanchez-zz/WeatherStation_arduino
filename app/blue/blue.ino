
int var1=0;
int var2=0;
int var3=0;
int var4=0;
int var5=0;
int var6=0;

int len1;
int len2;
int len3;
int len4;
int len5;
int len6;

void setup() {
  Serial.begin(9600);
}

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

void loop() {
  String mesLen = getLenMsg();
  String text;
  text=text+var1+","+var2+","+var3+","+var4+","+var5+","+var5;
    
  while (Serial.available()) { 
    char order = Serial.read(); 
    if(order = '1')
      Serial.print(mesLen);
      Serial.print(text);
      var1++;
      var2++;
      var3++;
      var4++;
      var5++;
      var6++;      
  }
  
}
