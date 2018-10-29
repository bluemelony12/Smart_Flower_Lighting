#include <SoftwareSerial.h>
#include <Servo.h>
#include "DHT.h"

int DHT_Pin = 12;
float DHT_temp, DHT_humi;
DHT dht(DHT_Pin,DHT11);      //온습도 센서

Servo servo;  

int CDS_Pin = A1;
int CDS_value;              //조도센서

int LED_R_Pin = 11;
int LED_G_Pin = 10;
int LED_B_Pin = 9;
int LED_BT = 0;           // LED 출력  모드 체크
int Red_Value = 0;
int Green_Value = 0;   
int Blue_Value = 0;       
int led_change = 10;      // led 센서 변화률
int led_default = 12;     // led 출력함수 호출

int BT_TX = 8;                    //블루투스 TX
int BT_RX = 7;                    //블루투스 RX
String BTstring = "";             //블루투스 입력값      
SoftwareSerial BTserial(BT_TX,BT_RX);  //블루투스 시작

void setup() {
 
  Serial.begin(9600);  
  BTserial.begin(9600);
  
}

//---------------------------------------------------------------------------------------------    

void view(){              // 현 상황 체크 Serial 통신
  Serial.print("Red_Value : ");
  Serial.print(Red_Value);
  Serial.print(" / Green_Value : ");
  Serial.print(Green_Value);
  Serial.print(" / Blue_Value : ");
  Serial.println(Blue_Value);
    
  Serial.print("CDS_value : ");
  Serial.println(CDS_value);
    
  Serial.print("Temp : ");
  Serial.print(DHT_temp);   
  Serial.print("^C / humi : ");
  Serial.print(DHT_humi);   
  Serial.println("%");
  Serial.println("");
}

void LED_off(){          // ALL LED OFF         
  Red_Value = 0;
  Green_Value = 0;
  Blue_Value = 0;
  LED_BT = led_default;
}
void LED_R_on(){         // Only RED LED  On         
  Red_Value = 250;
  Green_Value = 0;
  Blue_Value = 0;
  LED_BT = led_default;
}
void LED_G_on(){         // Only GREEN LED On    
  Red_Value = 0;
  Green_Value = 250;
  Blue_Value = 0;
  LED_BT = led_default;
}
void LED_B_on(){         // Only BLUE LED ON         
  Red_Value = 0;
  Green_Value = 0;
  Blue_Value = 250;
  LED_BT = led_default;
}
void LED_RED_UP(int rise){    // Red LED Value Increase
  if(Red_Value < 250){
    Red_Value  += rise;
  }
  LED_BT = led_default;
}
void LED_RED_DOWN(int fall){   // Red LED Value Decrease
  if(Red_Value > 0){
    Red_Value  -= fall;
  }
  LED_BT = led_default;
}
void LED_GREEN_UP(int rise){    // Green LED Value Increase
  if(Green_Value < 250){
    Green_Value  += rise;
  }
  LED_BT = led_default;
}
void LED_GREEN_DOWN(int fall){  // Green LED Value Decrease
  if(Green_Value > 0){
    Green_Value  -= fall;
  }
  LED_BT = led_default;
}
void LED_BLUE_UP(int rise){   // Blue LED Value Increase
  if(Blue_Value < 250){
    Blue_Value  += rise;
  }
  LED_BT = led_default;
}
void LED_BLUE_DOWN(int fall){  // Blue LED Value Decrease
  if(Blue_Value > 0){
    Blue_Value  -= fall;
  }
  LED_BT = led_default;
}

void LED_default(){               // Output LED Value 
  analogWrite(LED_R_Pin,Red_Value);
  analogWrite(LED_G_Pin,Green_Value);
  analogWrite(LED_B_Pin,Blue_Value);
}

void LED_Auto(){                 // Set Auto LED and Output LED
   
  int Red_Value_s = Red_Value;
  int Green_Value_s = Green_Value;
  int Blue_Value_s = Blue_Value;
  
  int aa = map(CDS_value,60,600,100,1);        ////////////////////// CDS 조절
  float bb = aa*0.01;
  
  
  analogWrite(LED_R_Pin,Red_Value_s * bb);
  analogWrite(LED_G_Pin,Green_Value_s * bb);
  analogWrite(LED_B_Pin,Blue_Value_s * bb);
}



               
//-----------------------------------------------------------------------------------------------------
void loop() {
  CDS_value = analogRead(CDS_Pin);
  DHT_humi = dht.readHumidity();
  DHT_temp = dht.readTemperature();

  /*Serial.print("CDS_value : ");
  Serial.println(CDS_value);
  delay(200);*/
  
  while(BTserial.available()){
    char data = (char)BTserial.read();
    BTstring += data;
    delay(10);
  }
  
  if(!BTstring.equals("")){
    if(BTstring.equals("LEDoff")) LED_BT = 0;
    if(BTstring.equals("ledron")) LED_BT = 1;
    if(BTstring.equals("ledgon")) LED_BT = 2;
    if(BTstring.equals("ledbon")) LED_BT = 3;
    if(BTstring.equals("ledrup")) LED_BT = 4;
    if(BTstring.equals("ledrdown")) LED_BT = 5;
    if(BTstring.equals("ledgup")) LED_BT = 6;
    if(BTstring.equals("ledgdown")) LED_BT = 7;
    if(BTstring.equals("ledbup")) LED_BT = 8;
    if(BTstring.equals("ledbdown")) LED_BT = 9;
    if(BTstring.equals("leda")) LED_BT = 10;
    if(BTstring.equals("ledaoff")) LED_BT = 11;
  
    if(LED_BT == 0){
      LED_off();
    }
    if(LED_BT == 1){
      LED_R_on();
    }
    if(LED_BT == 2){
      LED_G_on();
    }
    if(LED_BT == 3){
      LED_B_on();
    }
    if(LED_BT == 4){
      LED_RED_UP(led_change);
    }
    if(LED_BT == 5){
      LED_RED_DOWN(led_change);
    }
    if(LED_BT == 6){
      LED_GREEN_UP(led_change);
    }
    if(LED_BT == 7){
      LED_GREEN_DOWN(led_change);
    }
    if(LED_BT == 8){
      LED_BLUE_UP(led_change);
    }
    if(LED_BT == 9){
      LED_BLUE_DOWN(led_change);
    }
    if(LED_BT == 11){
      LED_default();
    }
    if(LED_BT == 12){
      LED_default();
      view();
    }
    
  BTstring = "";
  }

  if(LED_BT == 10){
      LED_Auto();
  }
         

}
