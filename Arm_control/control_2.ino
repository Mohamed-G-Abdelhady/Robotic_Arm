void  control_2()
{
 kp = 15.0;
 kd = 5.0;
 ki = 10.0; 
                                      
//angle2 control
if(set_angle2 >  50)set_angle2=  50;
if(set_angle2 < -70)set_angle2 = -70;
d2 = 0.9*d2 + 0.1*set_angle2;

    error_angle2 = (d2  - angle2 );     //error calcualation
    u1_angle2 = kp * error_angle2 ;            //p action
                                             //integral angle2
   if(error_angle2 > 20) error_angle2 = 20;
   if(error_angle2 <-20) error_angle2 =-20;
   angle2_integral = angle2_integral + (error_angle2 * dt) ;            //numerical integration
    limit_iangle2 = 100 ;                                               //saturation 
    if      (abs(angle2_integral)*ki <= limit_iangle2)      { u2_angle2 = angle2_integral*ki ;}        
    else if (    angle2_integral *ki > limit_iangle2 )      {u2_angle2 = limit_iangle2 ;   angle2_integral=limit_iangle2/ki;}                                                                             
    else                                                  {u2_angle2 = - limit_iangle2 ; angle2_integral= - limit_iangle2/ki;} 
     //end of integral angle2

  
    pwm_2 =  u1_angle2  + u2_angle2 - kd* derivative2 ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(pwm_2 <= -255) pwm_2 = -255;
    if(pwm_2 >=  255) pwm_2 =  255;
  
}
