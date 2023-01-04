
#include<LiquidCrystal.h>

#include<SoftwareSerial.h>

SoftwareSerial mySerial(2,3); // 2 tx 3rx

LiquidCrystal lcd(13,12,11,10,9,8);


//const int sensorIn = A3;
//int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
//
//double Voltage = 0;
//double VRMS = 0;
//double AmpsRMS = 0;


String web_data;
/****************************************/
int webdata_len;
/****************************************/

int t;
char x[5];


String datas; 

String Power_Data;

String grid_Data;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

mySerial.begin(9600);
  

  
  pinMode(A0,INPUT);//eb


  pinMode(A1,INPUT);//power theft

    pinMode(A2,INPUT);// active grid

        
    
 pinMode(7,OUTPUT);///PT Relay

  pinMode(6,OUTPUT);//Grid 1 relay

  
  pinMode(5,OUTPUT);//Grid 2 relay
  

  pinMode(4,OUTPUT);//eb relay
  
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Energy meter  ");
  lcd.setCursor(0,1);
  lcd.print("Power Theft Sys ");
  delay(2000);
  lcd.clear();

}

void loop() 
{
       

  
int a1=analogRead(A1);


if(a1>500)
{
  lcd.setCursor(0,1);
  lcd.print("P-T-D");
 
  digitalWrite(7,LOW);
 

  Power_Data="DET";

     gsm("Power Theft Det");
          delay(1000);

  
}

else if(a1<500)
{
  lcd.setCursor(0,1);
  lcd.print("P-Nor");
   digitalWrite(7,HIGH);
     
Power_Data="Nor";
   
}

int a2=analogRead(A2);


if(a2<500)
{
  lcd.setCursor(7,1);
  lcd.print("G-N");
 
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);

  grid_Data="Grid_Nor";



  
}
else if (a2>500 )
{
  lcd.setCursor(7,1);
   lcd.print("G-C");

   
  digitalWrite(6,LOW);
  
  digitalWrite(5,HIGH);

 grid_Data="Grid_Cut";

    gsm("Active Grid cut");
          delay(1000);

}

        
        int a=analogRead(A0);
        
        
        if(a==0)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:0   ");
          lcd.setCursor(9,0);
          lcd.print("         ");
          
          digitalWrite(4,HIGH);
        }
        else if(a>100 && a<200)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:100  ");
        
          
          digitalWrite(4,HIGH);
          
        }
        else if(a>200 && a<300)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:110 ");
           lcd.setCursor(9,0);
          lcd.print(" Rs:220 ");
          datas = "Bala_C-ID_8573_Unit:110_Rs:220";
              lcd.setCursor(0,1);
            digitalWrite(4,HIGH);
        }
        else if(a>300 && a<400)
        {
          
          lcd.setCursor(0,0);
          lcd.print("Unit:120 ");
          lcd.setCursor(9,0);
          lcd.print(" Rs:240 ");
          
          datas = "Bala_C-ID_8573_Unit:120_Rs:240" ;
         
          digitalWrite(4,HIGH);
        }
        else if(a>400 && a<500)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:130 ");
          lcd.setCursor(9,0);
          lcd.print(" Rs:260 ");
          datas = "Bala_C-ID_8573_Unit:130_Rs:260" ;
          digitalWrite(4,HIGH);
        }
        else if(a>500 && a<600)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:140 ");
          lcd.setCursor(9,0);
          lcd.print(" Rs:280 ");
          datas = "Bala_C-ID_8573_Unit:140_Rs:280" ;
          digitalWrite(4,HIGH);
        }
        else if(a>600 && a<700)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:150 ");
           lcd.setCursor(9,0);
          lcd.print(" Rs:300 ");
          datas = "Bala_C-ID_8573_Unit:150_Rs:300" ;
         digitalWrite(4,HIGH);
          }
        else if(a>700 && a<800)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:160 ");
          lcd.setCursor(9,0);
          lcd.print(" Rs:320 ");
           datas = "Bala_C-ID_8573_Unit:160_Rs:320" ;
          digitalWrite(4,HIGH);
        }
        else if(a>800 && a<900)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:170 ");
          lcd.setCursor(9,0);
          lcd.print(" Rs:340 ");
           datas = "Bala_C-ID_8573_Unit:170_Rs:340" ;
         digitalWrite(4,HIGH);
          
        }
        else if(a>900)
        {
          lcd.setCursor(0,0);
          lcd.print("Unit:180");
          lcd.setCursor(9,0);
          lcd.print(" Rs:360 ");
          datas = "Bala_C-ID_8573_Unit:180_Rs:360";
         
          delay(2000);
          digitalWrite(4,LOW);
          gsm("Due date end power cut");
          delay(1000);
         }
   



      web_data = "Meter_"+datas+"_Power_Theft_"+Power_Data+"_"+grid_Data;
      webdata_len = web_data.length();
      String send_data  = String(webdata_len)+"_"+web_data;
      Serial.print(send_data);
      delay(3000);

}



void gsm(String a) 
{
   
 
     mySerial.print("AT");
     mySerial.write(0X0D);
     mySerial.write(0X0A);
     delay(500);

     mySerial.print("AT+CMGF=1");
  
     mySerial.write(0X0D);
     mySerial.write(0X0A);
     delay(500);


     mySerial.print("AT+CMGS=\"");
     mySerial.print("9790630523");
     mySerial.println("\"");

     
     mySerial.write(0X0D);
     mySerial.write(0X0A);
     delay(500);

  
     mySerial.print(a);
     mySerial.write(0X0A);
     delay(500);


     mySerial.write(0x1A);
     mySerial.write(0X0A); 
     delay(500);     
}
