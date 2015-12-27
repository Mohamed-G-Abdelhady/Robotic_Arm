void  control_3()
{
 kp = 6.0;
 kd = 0.5;
 ki = 2.0; 
                                      
//angle3 control

if(set_angle3 >  -10)set_angle3=  -10;
if(set_angle3 < -160)set_angle3 = -160;
d3 = 0.9*d3 + 0.1*set_angle3;

    error_angle3 = (d3  - angle3 );     //error calcualation
    if(abs(error_angle3) <3) error_angle3 = 0;
    u1_angle3 = kp * error_angle3 ;            //p action
                                             //integral angle3
   if(error_angle3 > 20) error_angle3 = 20;
   if(error_angle3 <-20) error_angle3 =-20;
   angle3_integral = angle3_integral + (error_angle3 * dt) ;            //numerical integration
       
    limit_iangle3 = 100 ;                                               //saturation 
    if      (abs(angle3_integral)*ki <= limit_iangle3)      { u2_angle3 = angle3_integral*ki ;}        
    else if (    angle3_integral *ki > limit_iangle3 )      {u2_angle3 = limit_iangle3 ;   angle3_integral=limit_iangle3/ki;}                                                                             
    else                                                  {u2_angle3 = - limit_iangle3 ; angle3_integral= - limit_iangle3/ki;} 
     //end of integral angle3
    pwm_3 = -1*( u1_angle3  + u2_angle3 - kd * derivative3);  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(pwm_3 <= -255) pwm_3 = -255;
    if(pwm_3 >=  255) pwm_3 =  255;
  
}
