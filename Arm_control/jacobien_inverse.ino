void jacobien_inverse()
{

delta_x = set_x - x;
delta_y = set_y - y;
delta_phi = set_phi - phi;

 //singularity 

 if ( sqrt(set_x*set_x + set_y*set_y)  >=  sqrt( (L_3*L_3) + (L_1 + L_2)*(L_1 + L_2) + 2*L_3*(L_1 + L_2)*cos(angle4) ) - 10 )
     {
     delta_angle2 =  0 ;
     delta_angle3 = 0 ;
     delta_angle4 = delta_phi;
     
     set_x = set_x_old ;
     set_y = set_y_old;
     }
 else if ( sqrt(set_x*set_x + set_y*set_y) < sqrt( (L_3*L_3) + (L_1 - L_2)*(L_1 - L_2) - 2*L_3*(L_1 - L_2)*cos(angle4) ) + 10 )
   {
     delta_angle2 =  0 ;
     delta_angle3 = 0 ;
     delta_angle4 = delta_phi;
     
     set_x = set_x_old ;
     set_y = set_y_old;
   }

 else
    { 

delta_angle2 = ( -cos(D2R*(angle2 + angle3))/(L_1*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_x + ( -sin(D2R*(angle2 + angle3))/(L_1*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) )*delta_y + ( (L_3*cos(D2R*(angle2 + angle3 + angle4))*sin(D2R*(angle2 + angle3)) - L_3*sin(D2R*(angle2 + angle3 + angle4))*cos(D2R*(angle2 + angle3)))/(L_1*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) )*delta_phi*D2R;
delta_angle3 = ( (L_2*cos(D2R*(angle2 + angle3)) + L_1*cos(D2R*angle2))/(L_1*L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_x + ( (L_2*sin(D2R*(angle2 + angle3)) + L_1*sin(D2R*angle2))/(L_1*L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_y + ( -(L_1*L_3*cos(D2R*(angle2 + angle3 + angle4))*sin(D2R*angle2) - L_1*L_3*sin(D2R*(angle2 + angle3 + angle4))*cos(D2R*angle2) + L_2*L_3*cos(D2R*(angle2 + angle3 + angle4))*sin(D2R*(angle2 + angle3)) - L_2*L_3*sin(D2R*(angle2 + angle3 + angle4))*cos(D2R*(angle2 + angle3)))/(L_1*L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_1*L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_phi * D2R;
delta_angle4 = ( -cos(D2R*angle2)/(L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_x + ( -sin(D2R*angle2)/(L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_y  + ( (L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2) + L_3*cos(D2R*(angle2 + angle3 + angle4))*sin(D2R*angle2) - L_3*sin(D2R*(angle2 + angle3 + angle4))*cos(D2R*angle2))/(L_2*cos(D2R*(angle2 + angle3))*sin(D2R*angle2) - L_2*sin(D2R*(angle2 + angle3))*cos(D2R*angle2)) ) * delta_phi*D2R;
    }
set_angle1 = set_phi_Z;
set_angle2 = delta_angle2/D2R + angle2;
set_angle3 = delta_angle3/D2R + angle3;
set_angle4 = delta_angle4/D2R + angle4;
set_angle5 = set_phi_G;

set_x_old = set_x;
set_y_old = set_y;


}
