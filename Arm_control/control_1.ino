void  control_1()
{
 kp = 5.0;
 kd = 0.25;
 ki = 3.5; 
                                      
//angle1 control
if(set_angle1 >  180)set_angle1=  180;
if(set_angle1 < -180)set_angle1 = -180;
d1 = 0.9*d1 + 0.1*set_angle1;

    error_angle1 = (d1  - angle1 );     //error calcualation
    u1_angle1 = kp * error_angle1 ;            //p action
                                             //integral angle1
   if(error_angle1 > 10) error_angle2 = 10;
   if(error_angle1 <-10) error_angle2 =-10;
   angle1_integral = angle1_integral + (error_angle1 * dt) ;            //numerical integration
       
    limit_iangle1 = 90 ;                                               //saturation 
    if      (abs(angle1_integral)*ki <= limit_iangle1)      { u2_angle1 = angle1_integral*ki ;}        
    else if (    angle1_integral *ki > limit_iangle1 )      {u2_angle1 = limit_iangle1 ;   angle1_integral=limit_iangle1/ki;}                                                                             
    else                                                    {u2_angle1 = - limit_iangle1 ; angle1_integral= - limit_iangle1/ki;} 
     //end of integral angle1

  
    pwm_1 =  u1_angle1  + u2_angle1 - kd* derivative1 ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(pwm_1 <= -255) pwm_1 = -255;
    if(pwm_1 >=  255) pwm_1 =  255;
  
}
