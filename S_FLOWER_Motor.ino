#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1,servo2,servo3,servo4,servo5,servo6;

int motor_moving_c = 0;
int motor_moving_pos;


int BT_TX = 12;                    //블루투스 TX
int BT_RX = 13;                    //블루투스 RX
String BTstring = "";             //블루투스 입력값      
SoftwareSerial BTserial(BT_TX,BT_RX);

void setup() {
  Serial.begin(9600);  
  BTserial.begin(9600);
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  servo6.attach(11);

}

void motor_spin_A(int pos){
  servo1.write(pos);
  servo2.write(pos);
  servo3.write(pos);
  servo4.write(pos);
  servo5.write(pos);
  servo6.write(pos);
}

void loop() {
  while(BTserial.available()){
    char data = (char)BTserial.read();
    BTstring += data;
    delay(10);
  }

    if(!BTstring.equals("")){
      /*if(BTstring.equals("mt90")){
        motor_spin_A(20);
        motor_moving_c = 0;
      }*/
      if(BTstring.equals("mt50")){
        motor_spin_A(35);
        motor_moving_c = 0;
      }
      if(BTstring.equals("mt10")){ 
        motor_spin_A(80);
        motor_moving_c = 0;
      }
      if(BTstring.equals("mtauto")){
        motor_moving_c = 1;
        servo1.write(20);
        delay(200);
        servo3.write(20);
        delay(200);
        servo2.write(20);
        delay(200);
        servo5.write(20);
        delay(200);
        servo4.write(20);
        delay(200);
        servo6.write(20);
        delay(200);

        /*servo6.write(80);
        delay(200);
        servo4.write(80);
        delay(200);
        servo5.write(80);
        delay(200);
        servo2.write(80);
        delay(200);
        servo3.write(80);
        delay(200);
        servo1.write(80);
        delay(200);*/
        
      }
        BTstring = "";
    }    }
    

    /*if(motor_moving_c > 0){
      for(motor_moving_pos=0;motor_moving_pos<=80;motor_moving_pos++){
        servo1.write(motor_moving_pos);
        servo2.write(motor_moving_pos);
        servo3.write(motor_moving_pos);
        servo4.write(motor_moving_pos);
        servo5.write(motor_moving_pos);
        servo6.write(motor_moving_pos);
      }
      for(motor_moving_pos=80;motor_moving_pos>=0;motor_moving_pos--){
        servo1.write(motor_moving_pos);
        servo2.write(motor_moving_pos);
        servo3.write(motor_moving_pos);
        servo4.write(motor_moving_pos);
        servo5.write(motor_moving_pos);
        servo6.write(motor_moving_pos);
      }
    }*/

  
