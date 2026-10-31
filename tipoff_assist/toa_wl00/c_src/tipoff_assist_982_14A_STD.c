/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2020
*
* GENERATED :
*       2020-10-26T11:43:03-05:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_982_14A_STD.h"

void mass_and_dist_982_14A_STD(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_982_14A_STD(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 3561.5*x0;
    double x2 = cos(arm_ang);
    double x3 = 3561.5*x2;
    double x4 = -imu_x*x1 + imu_y*x3;
    double x5 = pow(imu_x, 2);
    double x6 = pow(imu_y, 2);
    double x7 = pow(x5 + x6, -1.0/2.0);
    double x8 = -x5*x7 - x6*x7;
    double x9 = sin(lever_ang);
    double x10 = x0*x9;
    double x11 = 910.0*x10;
    double x12 = cos(lever_ang);
    double x13 = x12*x2;
    double x14 = 910.0*x13;
    double x15 = -x11 + x14;
    double x16 = x0*x15;
    double x17 = x0*x12;
    double x18 = 910.0*x17;
    double x19 = x2*x9;
    double x20 = 910.0*x19;
    double x21 = -x18 - x20;
    double x22 = x2*x21;
    double x23 = 1820.0*x10;
    double x24 = 1820.0*x13;
    double x25 = -x23 + x24;
    double x26 = 1162.2*x2;
    double x27 = 1820.0*x17;
    double x28 = 1820.0*x19;
    double x29 = -x27 - x28;
    double x30 = -4390.1999999999998*x0 - x26 + x29;
    double x31 = 4390.1999999999998*x2;
    double x32 = 1162.2*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 45175071233.375*x37;
    double x39 = 2195.0999999999999*x2;
    double x40 = 581.10000000000002*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 12684282.25*x37;
    double x45 = pow(x2, 2);
    double x46 = 12684282.25*x45;
    double x47 = pow(x43, 2);
    double x48 = 2195.0999999999999*x0;
    double x49 = 581.10000000000002*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 25368564.5*x2;
    double x56 = 7123.0*x54;
    double x57 = -1366.4000000000001*x0 + x51;
    double x58 = 2031.0*BC_len;
    double x59 = x2*x43;
    double x60 = 7123.0*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 1031240.25;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 1031240.25;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 599253709.27499998*x0 + 938428627.5*x10 - 938428627.5*x13 + 45175071233.375*pow(x2, 3) + x2*x38 + 1409086677.5999999*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 25368564.5*x37;
    double x71 = 25368564.5*x45;
    double x72 = 2*x47 + 2*x53 - 14246.0*x54 - 14246.0*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2730.0*x17 - 2730.0*x19;
    double x76 = x25*x52;
    double x77 = x29*x43;
    double x78 = 7123.0*x16;
    double x79 = x1*x15;
    double x80 = x21*x3;
    double x81 = -x48 - x49;
    double x82 = x21 + x81;
    double x83 = x25*x82;
    double x84 = x11 - x14;
    double x85 = x40 + x84;
    double x86 = -x39 + x85;
    double x87 = x29*x86;
    double x88 = x68/(x64*x66);
    double x89 = 938428627.5*x17 + 938428627.5*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x77 + x43*x76 - x43*x78 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x77 - x79 - x80)) + x89;
    double x91 = x73*(14246.0*x16 + 14246.0*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 1031240.25;
    double x96 = 1366.4000000000001*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -2732.8000000000002*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 7123.0*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x77;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x78)) + x107*x33 + x109*(x108 + x78 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = 45175071233.375*x45;
    double x116 = x25 + x31 - x32;
    double x117 = x116*x52;
    double x118 = x30*x43;
    double x119 = x3*x82;
    double x120 = x3*x52;
    double x121 = x116*x82;
    double x122 = x30*x86;
    double x123 = -45175071233.375*pow(x0, 3) - x0*x115 + 25368564.5*x0*x59 - 1409086677.5999999*x0 + x1*x36 - x1*x47 - x1*x53 + x117*x3 + x117*x43 - x118*x3 + 599253709.27499998*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-6585.2999999999993*x0 - 1743.3000000000002*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x119 + x120 + (1.0/2.0)*x121 + (1.0/2.0)*x122) + x66*((1.0/2.0)*x117 + (1.0/2.0)*x118 - x119 - x120)) + x89;
    double x124 = 14246.0*x2;
    double x125 = x123*x74 + x73*(x116*x30 + x124*x52 + x124*x82 + x30*x35);
    double x126 = x106*(x1 + x125);
    double x127 = x117 + x118;
    double x128 = 7123.0*x2;
    double x129 = x128*x52;
    double x130 = x128*x82;
    double x131 = x102*(x123*x97 + x127*x63 + x57*x69 + x95*(x127 - x129 - x130)) + x107*(2732.8000000000002*x2 + x34) + x109*(x121 + x122 + x129 + x130);
    double x132 = x112*(x131 + x92);
    double x133 = -x114*x44 - x114*x46 + x126 + x132 + 1;
    double x134 = 144.90000000000001*x10;
    double x135 = 798.5*x17;
    double x136 = 798.5*x19;
    double x137 = 144.90000000000001*x13;
    double x138 = -x134 + x135 + x136 + x137;
    double x139 = x134 - x135 - x136 - x137 + x48 + x49 - 12;
    double x140 = 798.5*x10 - 798.5*x13 + 144.90000000000001*x17 + 144.90000000000001*x19;
    double x141 = x140 + x39 + x41;
    double x142 = x141 - 471.20000000000005;
    double x143 = pow(x139, 2) + pow(x142, 2);
    double x144 = 1.0/x143;
    double x145 = x138 + x81;
    double x146 = x144*(x145 + 12);
    double x147 = x142*x144;
    double x148 = x138*x146 + x140*x147;
    double x149 = pow(x143, -1.0/2.0);
    double x150 = 169600*x149;
    double x151 = imu_x*x139;
    double x152 = imu_y*x142;
    double x153 = 508.5*x150*x151 - 508.5*x150*x152;
    double x154 = x86 + x93;
    double x155 = x103 + x82;
    double x156 = 1.0/(pow(x154, 2) + pow(x155, 2));
    double x157 = x156*(x105 + x52);
    double x158 = x154*x156;
    double x159 = pow(x15, 2);
    double x160 = 1.0/(x159 + pow(x50, 2));
    double x161 = -x159*x160 - x160*pow(x21, 2) + 1;
    double x162 = -atan2(x155, x154) + atan2(x50, x15);
    double x163 = sin(x162);
    double x164 = cos(x162);
    double x165 = x12*x164 + x163*x9;
    double x166 = x12*x163 - x164*x9;
    double x167 = 68571637.5*imu_x*(-x0*x165 + x166*x2) + 68571637.5*imu_y*(x0*x166 + x165*x2);
    double x168 = 206800*x149;
    double x169 = -576.89999999999998*x151*x168 + 576.89999999999998*x152*x168;
    double x170 = imu_x*x0;
    double x171 = imu_y*x2;
    double x172 = -20120*x170 + 20120*x171;
    double x173 = 20120*x113;
    double x174 = imu_y*x93;
    double x175 = imu_x*x103;
    double x176 = -x17 - x19;
    double x177 = -x10 + x13;
    double x178 = x17 + x19;
    double x179 = tilt_force*x149;
    double x180 = 144.90000000000001*x179;
    double x181 = 798.5*x179;
    double x182 = 11733350.0*imu_x*x176 + 20467230.0*imu_x*x177 + 11733350.0*imu_y*x177 + 20467230.0*imu_y*x178 - x139*x177*x181 + x139*x178*x180 - x142*x176*x181 + x142*x177*x180;
    double x183 = -3561.5*x113*x172 + x148*x153 + x148*x169 + x167*(x157*(x50 + x91) + x158*(x111 + x84) + x161) + x173*x174 - x173*x175 + x182;
    double x184 = x141*x147 + x145*x146;
    double x185 = 31.100000000000001*x0;
    double x186 = 820.39999999999998*x2;
    double x187 = x185 + x186;
    double x188 = x187 + 524.5;
    double x189 = 820.39999999999998*x0;
    double x190 = 31.100000000000001*x2;
    double x191 = x189 - x190 + 1584.4000000000001;
    double x192 = pow(x188, 2) + pow(x191, 2);
    double x193 = pow(x192, -1.0/2.0);
    double x194 = 240600*x193;
    double x195 = imu_x*x191;
    double x196 = imu_y*x188;
    double x197 = -x189 + x190;
    double x198 = 1.0/x192;
    double x199 = x187*x188*x198 + x197*x198*(x197 - 1584.4000000000001);
    double x200 = 402200*x193;
    double x201 = 20120*x133;
    double x202 = lift_force*x193;
    double x203 = x188*x202;
    double x204 = x191*x202;
    double x205 = x139*x179;
    double x206 = x142*x179;
    double x207 = -x113*x8*(-1180725591.8*imu_x*x2 - 1180725591.8*imu_y*x0 + x153*x184 + x167*(x157*(x125 + x52) + x158*(x131 + x86) + x161) + x169*x184 - 7374635146.7999992*x170 + 7374635146.7999992*x171 + x172*(x114*x115 + x114*x38 - 3561.5*x126 - 3561.5*x132) + x174*x201 - x175*x201 + x182 + x185*x204 + x186*x204 - x189*x203 + x190*x203 + 746.70000000000005*x199*(x194*x195 - x194*x196) + 668.39999999999998*x199*(-x195*x200 + x196*x200) + x205*x39 - x205*x40 - x206*x48 - x206*x49) + x133*x183*x8;
    double mass_result = x207/(x113*x4*x8);
    double dist_result = -x183*x4/x207;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_982_14A_STD(
    double tilt_cyl_ext, double arm_ang, double BC_len, double hook_ang,
    double *return_tilt_sens_to_bucket_ang
) {
    /*
    * The sensitivity expression in terms of bucket angle, but bucket angle
    * depends on BC length which the standard channel does not take into account,
    * so we calculate our own bucket angle that respects BC length here from tilt
    * extension.
    * Tilt extension -> lever angle -> bucket angle
    */
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_982_14A_STD(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 2195.0999999999999*x0;
    double x8 = 581.10000000000002*x1;
    double x9 = -x8;
    double x10 = 3561.5*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 3561.5*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 581.10000000000002*x0;
    double x16 = -x15;
    double x17 = 2195.0999999999999*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 - 203140.25;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -1366.4000000000001*x1 + x16 - x6;
    double x30 = x28 - 11130.25;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 3707550.25;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(1366.4000000000001*x0 + x4 + x9);
    double x34 = -118044799.27499998*x0 - 277570837.60000038*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 - 203140.25*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 1162.2*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 2732.8000000000002*x0 + x37 + x38;
    double x40 = 1.0/x39;
    double x41 = 1.0/x28;
    double x42 = x40*x41;
    double x43 = x35*x42;
    double x44 = x43 - x7 + x9;
    double x45 = 2*x11 + 2*x13 + 2*x19 + 2*x21 - 4*x24 - 4*x26;
    double x46 = 1.0/x45;
    double x47 = x15 - x17 + x34*x46;
    double x48 = -arm_ang + x2 - atan2(x4, x6) + atan2(x44, x47);
    double x49 = sin(x48);
    double x50 = cos(x48);
    double x51 = x0*x49;
    double x52 = x0*x50;
    double x53 = x1*x49;
    double x54 = x1*x50;
    double x55 = pow(BC_len, 2);
    double x56 = pow(x3, 2)*x55;
    double x57 = pow(x5, 2)*x55;
    double x58 = 1.0/(x56 + x57);
    double x59 = 1.0/(pow(x44, 2) + pow(x47, 2));
    double x60 = x12*x6;
    double x61 = 1162.2*x0;
    double x62 = 4390.1999999999998*x1;
    double x63 = x61 - x62;
    double x64 = 4390.1999999999998*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 + 203140.25*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(2324.4000000000001*x0 - 8780.3999999999996*x1) - x6*(-8780.3999999999996*x0 - 2324.4000000000001*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 58694.880000000005*x74;
    double x76 = 377992.0*x74;
    double tilt_sensitivity = (1836988.7399999998*x49*x74 - 145938.36000000004*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(494946.24000000011*x0 - 2082608.6400000001*x1 - 291876.72000000009*x49 - 3673977.4799999995*x50 - 755984.0*x51 - 117389.76000000001*x52 - 117389.76000000001*x53 + 755984.0*x54 + 6036912.9199999999, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_982_14A_STD(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 494946.24000000011*x0;
    double x3 = 2082608.6400000001*x1;
    double x4 = 581.10000000000002*x0;
    double x5 = 2195.0999999999999*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 2195.0999999999999*x0;
    double x9 = 581.10000000000002*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 222173.44000000003;
    double x15 = pow(tilt_cyl_ext + 1340, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1623.0813411533015*tilt_cyl_ext;
    double x19 = 486825131.19000006*x0 - 1939321313.5500002*x1 - 24*x10*x6 + x11*x6 + 471.20000000000005*x11 + x15*x6 - 471.20000000000005*x15 + pow(x6, 3) - 471.20000000000005*x7 + sqrt((x13 - x15 + x18 + 1738504.1771454243)*(-x11 + x15 + x18 - x2 + x3 - x7 + 2611353.817145424))*(x17 + 12) + 415019625.04000008;
    double lever_ang = -atan2(3561.5*x0, 3561.5*x1) + atan2(x17 + (x14*(x12 + x15 - 880771.70000000007) + x19*(x16 + 471.20000000000005))/(x14*(4390.1999999999998*x0 + 1162.2*x1 - 24)), x16 + x19/(989892.48000000021*x0 - 4165217.2800000003*x1 + 2*x11 + 2*x7 + 444346.88000000006)) + 2.962080815582925;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_982_14A_STD(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_982_14A_STD(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 12684282.25*x6;
    double x8 = pow(x0, 2);
    double x9 = 12684282.25*x8;
    double x10 = 581.10000000000002*x0;
    double x11 = x0*x4;
    double x12 = 910.0*x11;
    double x13 = x1*x2;
    double x14 = 910.0*x13;
    double x15 = 2195.0999999999999*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 7123.0*x16;
    double x18 = 581.10000000000002*x1 + 910.0*x3 + 910.0*x5;
    double x19 = 2195.0999999999999*x0 + x18;
    double x20 = x0*x19;
    double x21 = 7123.0*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 3561.5*x1;
    double x29 = 2031.0*BC_len;
    double x30 = 599253709.27499998*x0 + 45175071233.375*pow(x1, 3) - 25368564.5*x1*x20 + 45175071233.375*x1*x8 + 1409086677.5999999*x1 + 938428627.5*x11 - 938428627.5*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 1031240.25)*(x17 + x21 - x22 - x23 + x27 + x29 + 1031240.25))*(-1366.4000000000001*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-3561.5*x0 + (x25*(x24 + x27 - 1031240.25) + x30*(1366.4000000000001*x1 + x10 + x12 - x14))/(x25*(-2732.8000000000002*x0 + 1162.2*x1 + 1820.0*x3 + 1820.0*x5)), -x28 + x30/(-14246.0*x16 - 14246.0*x20 + 2*x22 + 2*x23 + 25368564.5*x6 + 25368564.5*x8));

    return bucket_ang;
}
