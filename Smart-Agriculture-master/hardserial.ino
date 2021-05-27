#include <EEPROM.h>
String inString="";
void sensor();
void operation();
int soil;
int rain,count=0;
byte value;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(A5,INPUT);
  pinMode(A4,INPUT);
  digitalWrite(7,HIGH);
  pinMode(13, OUTPUT);
  delay(2000);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


 // Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial p
}

void loop() { // run over and over
  delay(1000);
  digitalWrite(2,LOW);
  digitalWrite(7,LOW);
    sensor(); 
   value=EEPROM.read(55);
  // Serial.print("value=");
  // Serial.println(value);
   delay(3500);
  
  if (Serial.available()) {
   inString = Serial.readString(); //Read input string from bolt
    delay(2000);
    String readData = "";
    while (Serial.available() > 0 ) {
      readData = readData + (char)Serial.read();
    }
    if (readData.indexOf("RD") != -1) {
      String data;
       rain=analogRead(A4);       //reading rain sensor value
        soil=analogRead(A5);       //reading soil moisture sensor value
      data = String(soil);
      Serial.println(data);
      delay(300);    

    }
  }
   
if(inString=="hello" || value==1)
{
  inString ="";
  count=1;
   EEPROM.update(55,count);
   delay(2500);
  digitalWrite(7,HIGH);
  digitalWrite(2,HIGH);
  delay(1000);
  operation();
  }

}//ending of void loop


void sensor()        // function  declaration for reading sensor 
{
  soil=analogRead(A5);
  Serial.println("Soil moisture percentage ");
  Serial.println(soil/10.24);
  Serial.print("\n");
  delay(100);           //reading soil moisture sensor value
  rain=analogRead(A4);//reading rain sensor value
  Serial.print("rain intensity ");
  Serial.println(soil);
  //Serial.print("rain value");
  delay(100);
  if(soil<400)
  {
    digitalWrite(13,HIGH);
    Serial.println("Motor on");
    }  
    else
    {
      digitalWrite(13,LOW);
      Serial.println("Motor off");
      
      }
  //soil = (soil/1024);
  //Serial.println(soil);
}



void operation(){
  while(1){
    delay(1600);
      sensor();
      delay(500);
      if(Serial.available()>0){
        inString=Serial.readString();
        delay(2000);
       String readData = "";
       while (Serial.available() > 0 ) {
          readData = readData + (char)Serial.read();
        }
         if (readData.indexOf("RD") != -1) {
          String data;
          rain=analogRead(A4);       //reading rain sensor value
          soil=analogRead(A5);       //reading soil moisture sensor value
         data = String(soil);
         delay(300);    

          }
     }
      
     
      delay(2500);
    if(inString=="stop"){
          digitalWrite(7,LOW);
          digitalWrite(2,LOW);
          delay(600);
          count=0;
          EEPROM.update(55,count);
          delay(2500);
          break;
        }
    if(soil<400){
          digitalWrite(2,HIGH);
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.print("Motor on");
          count=0;
          EEPROM.update(55,count);
          delay(2500);
           break;  // check code of this line
       }   //if condition ends here
   if(rain<250){
        delay(6500);
         if(rain<250){
           digitalWrite(2,LOW);
           digitalWrite(LED_BUILTIN, HIGH);
           delay(2500);
            sensor();
            if(rain>250 && soil>400){
              digitalWrite(2,HIGH);
              digitalWrite(LED_BUILTIN, HIGH);
              delay(2500);         
            }
            else{
              digitalWrite(2,LOW);
              digitalWrite(LED_BUILTIN, HIGH);
              delay(500);
            }
            
         } 
      }
      if(rain>250 && soil>400){
        digitalWrite(2,HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
      }
      }   //while ends here
}
