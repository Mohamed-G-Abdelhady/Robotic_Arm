void  control_4()
{
 kp = 25.5;
 kd = 0.5;
 ki = 0; 
                                      
//angle4 control
if(set_angle4 >  160)set_angle4=  160;
if(set_angle4 < -160)set_angle4 = -160;
d4 = 0.0*d4 + 1.0*set_angle4;

    error_angle4 = (d4  - angle4 );     //error calcualation
    u1_angle4 = kp * error_angle4 ;            //p action
                                             //integral angle4
   angle4_integral = angle4_integral + (error_angle4 * dt) ;            //numerical integration
       
    limit_iangle4 = 90 ;                                               //saturation 
    if      (abs(angle4_integral)*ki <= limit_iangle4)      { u2_angle4 = angle4_integral*ki ;}        
    else if (    angle4_integral *ki > limit_iangle4 )      {u2_angle4 = limit_iangle4 ;   angle4_integral=limit_iangle4/ki;}                                                                             
    else                                                  {u2_angle4 = - limit_iangle4 ; angle4_integral= - limit_iangle4/ki;} 
     //end of integral angle4

  
    pwm_4 =  u1_angle4  + u2_angle4 - kd* derivative4 ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(pwm_4 <= -255) pwm_4 = -255;
    if(pwm_4 >=  255) pwm_4 =  255;
  
}
