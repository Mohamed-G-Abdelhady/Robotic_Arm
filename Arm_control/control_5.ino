void  control_5()
{
 kp = 25.5;
 kd = 0.5;
 ki = 0; 
                                      
//angle5 control
if(set_angle5 >  720)set_angle5=  720;
if(set_angle5 < -720)set_angle5 = -720;
d5 = 0.0*d5 + 1.0*set_angle5;

    error_angle5 = (d5  - angle5 );     //error calcualation
    u1_angle5 = kp * error_angle5 ;            //p action
                                             //integral angle5
   angle5_integral = angle5_integral + (error_angle5 * dt) ;            //numerical integration
       
    limit_iangle5 = 90 ;                                               //saturation 
    if      (abs(angle5_integral)*ki <= limit_iangle5)      { u2_angle5 = angle5_integral*ki ;}        
    else if (    angle5_integral *ki > limit_iangle5 )      {u2_angle5 = limit_iangle5 ;   angle5_integral=limit_iangle5/ki;}                                                                             
    else                                                  {u2_angle5 = - limit_iangle5 ; angle5_integral= - limit_iangle5/ki;} 
     //end of integral angle5

  
    pwm_5 =  u1_angle5  + u2_angle5 - kd* derivative5 ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(pwm_5 <= -255) pwm_5 = -255;
    if(pwm_5 >=  255) pwm_5 =  255;
  
}
