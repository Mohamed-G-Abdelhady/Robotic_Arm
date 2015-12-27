/*
- Aerospace Deprtment
- Cairo University
- 5 D.O.F ARM control that takes part in ERC - European rover chalenge 2014
- Algorithm of control: resolved motion control (instantenous + forward kinematics)
- Developped By: Mohamed Gamal Abdelhady 
- Mail         : Aero.abdelhady@Gmail.com
- 19 ,august 2014
*/


//sample time 
float dt = 0.039 ;
float new_time , old_time = 0;
// encoders definitions
#include <Encoder.h>
Encoder enc1(43, 45);
Encoder enc2(39, 41);
Encoder enc3(35, 37);
Encoder enc4(27, 29);
Encoder enc5(31, 33);
Encoder enc6(23, 25);


float angle1 = 0 , angle2 = 0 , angle3 = 0 , angle4 = 0 , angle5 = 0 ;
float angle1_old = 0 , angle2_old = 0 , angle3_old = 0 , angle4_old = 0 , angle5_old = 0 ;
float derivative1 = 0 , derivative2 = 0, derivative3 = 0 , derivative4 = 0, derivative5 = 0   ;

//control inner loop definitions 
float pwm_1 = 0 , pwm_2 = 0 , pwm_3 = 0 , pwm_4 = 0 , pwm_5 = 0  ;

//control
float kp , kd , ki; 
 float error_angle5 , set_angle5 = 0 , u1_angle5 , angle5_integral = 0 , limit_iangle5 , u2_angle5 ,d5 = 0 ; 
 float error_angle4 , set_angle4 = 0 , u1_angle4 , angle4_integral = 0 , limit_iangle4 , u2_angle4 ,d4 = 0 ; 
 float error_angle3 , set_angle3 = 0 , u1_angle3 , angle3_integral = 0 , limit_iangle3 , u2_angle3 ,d3 = 0 ;   
 float error_angle2 , set_angle2 = 0 , u1_angle2 , angle2_integral = 0 , limit_iangle2 , u2_angle2 ,d2 = 0;   
 float error_angle1 , set_angle1 = 0 , u1_angle1 , angle1_integral = 0 , limit_iangle1 , u2_angle1 ,d1 = 0;    

//forward kinematics 
float L_1 = 48.5 , L_2 = 32.5 , L_3 = 20.0; 
float  x = 31.0, y = -31.0 , phi = 0.0 ,  phi_Z = 0.0 , phi_G = 0.0 ;

//invrese jacobien

float set_x_old = 30.0 , set_x = 30.0 , set_y_old = 0.0 , set_y = 0.0 , set_phi = -90.0 , set_phi_Z = 0.0 , set_phi_G = 0.0 ;
float delta_angle2 , delta_angle3 , delta_angle4 , delta_x , delta_y , delta_phi;
const float D2R = M_PI / 180.0;

void setup()
{

  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT); 
  pinMode(26,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(32,OUTPUT);



Serial.begin(9600);  
 
}

long postion1  = -999;
long postion2  = -999;
long postion3  = -999;
long postion4  = -999;
long postion5  = -999;


void loop()
{
  
  //joystick
  if(Serial.available()>0)
  {
  int off = Serial.read();
   
  if(off=='1')set_x = set_x+5;
  if(off=='2')set_x = set_x-5;
 
  if(off=='4')set_y = set_y+5;
  if(off=='5')set_y = set_y-5;
  
  if(off=='7')set_phi = set_phi+5;
  if(off=='8')set_phi= set_phi-5;

  
  }
  //end of joystick
  
  
new_time = millis();
dt = (new_time - old_time)/1000.0;
old_time = new_time;

// angles and derivatives calculations
long new1 , new2 , new3 , new4 , new5 ;
new1 = enc1.read();
new2 = enc2.read();
new3 = enc3.read();
new4 = enc4.read();
new5 = enc5.read();
//new6 = enc6.read();

 if (new1 != postion1)  {postion1 = new1; angle1 = new1 / 304.0;         }  {derivative1 = (angle1 - angle1_old) / dt; angle1_old = angle1; }
 if (new2 != postion2)  {postion2 = new2; angle2 = new2 / 672.0;         }  {derivative2 = (angle2 - angle2_old) / dt; angle2_old = angle2;}
 if (new3 != postion3)  {postion3 = new3; angle3 =  (new3 / 4.0) -  90;}    {derivative3 =(angle3 - angle3_old) / dt; angle3_old = angle3;}
// if (new3 != postion3)  {postion3 = new3; angle3 = -(new3 / 473.0) -  90 - angle2;}  {derivative3 = (angle3 - angle3_old) / dt; angle3_old = angle3;}
 if (new4 != postion4)  {postion4 = new4; angle4 = new4 / 556.0; }          {derivative4 = (angle4 - angle4_old) / dt; angle4_old = angle4; }
 if (new5 != postion5)  {postion5 = new5; angle5 = new5 / 556.0; }          {derivative5 = (angle5 - angle5_old) / dt; angle5_old = angle5; }

// end of angles and derivatives calculations
 
//outer loop

forward_kinematics(); // input angles ---- output states (x  y phi  phi_Z phi_G)
jacobien_inverse();   // input (x  y phi  phi_Z phi_G) and (set_x  set_y set_phi  set_phi_Z  set_phi_G) output (set_angle5 set_angle4 set_angle3 set_angle2 set_angle1)



//control inner loop +-a

control_1();
control_2();
control_3();
control_4();
control_5();


pwm_1 = pwm_2 = pwm_3 = pwm_5 = pwm_4 = 0;
  
    motora(12,13,26,28,pwm_1);
    motora(3,2,22,24,pwm_2); 
    motora(11,10,32,30,pwm_3);
    motorb(6 , 7 , pwm_4);
    motorb(4 , 5 , pwm_5);
    
  
   Serial.print('\t'); Serial.print(set_angle1);
   Serial.print('\t'); Serial.print(set_angle2); 
   Serial.print('\t'); Serial.print(set_angle3);  
   Serial.print('\t'); Serial.print(set_angle4);
   Serial.print('\t'); Serial.print(set_angle5); hu
   Serial.print('\t'); Serial.print(set_x);
   Serial.print('\t'); Serial.print(set_y);
      Serial.print('\t'); Serial.print(set_phi );


   
    Serial.println();


}





void motora(int RPWM, int LPWM, int R, int L, float pwm)
{
  if(pwm>0){
    digitalWrite(R, 1);
    digitalWrite(L, 0);
    analogWrite(RPWM, pwm);
    analogWrite(LPWM, 0);
  }
  else if(pwm<0)
  {
    digitalWrite(R, 0);
    digitalWrite(L, 1);
    analogWrite(RPWM, 0);
    analogWrite(LPWM, abs(pwm));
  }
  else
  {
    digitalWrite(R, 0);
    digitalWrite(L, 0);
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
  }
}



void motorb(int pwm_pin , int dir_pin , float pwm)
{
if(pwm > 0) 
{
  digitalWrite(dir_pin,1);
  analogWrite(pwm_pin, pwm);
}
else if(pwm < 0) 
{
  digitalWrite(dir_pin,0);
  analogWrite(pwm_pin, abs(pwm));
}
else
{
digitalWrite(dir_pin , 0);
analogWrite(pwm_pin , 0);
}


}
