void forward_kinematics()
{

y = L_1 *sin(D2R*angle2) + L_2 *sin(D2R*(angle2 + angle3)) + L_3 *sin(D2R*(angle2 + angle3 + angle4));
x = L_1 *cos(D2R*angle2) + L_2 *cos(D2R*(angle2 + angle3)) + L_3* cos(D2R*(angle2 + angle3 + angle4));
phi = angle2 + angle3 + angle4;
phi_Z = angle1;
phi_G = angle5;
}
