#include <LiquidCrystal.h>         
#include <Wire.h>                  

const int rsPin = 9;

const int enablePin = 8;

const int d4Pin = 4;

const int d5Pin = 5;

const int d6Pin = 6;

const int d7Pin = 7;

LiquidCrystal lcd(rsPin, enablePin, d4Pin, d5Pin, d6Pin, d7Pin);   

const int MPU_addr=0x68;        

int16_t axis_X,axis_Y,axis_Z;    

int minVal=265;
int maxVal=402;

double x;
double y;
double z;

int pos = 0;  

void setup()
{
  Wire.begin();                        
  Wire.beginTransmission(MPU_addr);    
  Wire.write(0x6B);                    
  Wire.write(0);                       
  Wire.endTransmission(true);          
  
              
  lcd.begin(16,2);                 
  lcd.print("MARTINOV ANA");   
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduino");
  lcd.setCursor(0,1);
  lcd.print("MPU6050");
  delay(2000);
  lcd.clear();
}

void loop()
{
  Wire.beginTransmission(MPU_addr);  
  Wire.write(0x3B);                             
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); 
  
  axis_X=Wire.read()<<8|Wire.read();  
  axis_Y=Wire.read()<<8|Wire.read(); 
  axis_Z=Wire.read()<<8|Wire.read(); 
    
    int xAng = map(axis_X,minVal,maxVal,-90,90); 
    int yAng = map(axis_Y,minVal,maxVal,-90,90);
    int zAng = map(axis_Z,minVal,maxVal,-90,90);

   x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);     
     int pos = map(x,0,180,0,180); 
     lcd.setCursor(0,0);
     lcd.print("UNGHI");
     lcd.setCursor(0,1);
     lcd.print(x);                
     delay(500);
     lcd.clear();
}
