/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2021
*
* GENERATED :
*       2021-02-22T19:45:40-06:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_980_14A_LOG.h"

void mass_and_dist_980_14A_LOG(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_980_14A_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 3240*x0;
    double x2 = cos(arm_ang);
    double x3 = 3240*x2;
    double x4 = -imu_x*x1 + imu_y*x3;
    double x5 = pow(imu_x, 2);
    double x6 = pow(imu_y, 2);
    double x7 = pow(x5 + x6, -1.0/2.0);
    double x8 = -x5*x7 - x6*x7;
    double x9 = sin(lever_ang);
    double x10 = x0*x9;
    double x11 = 940.70000000000005*x10;
    double x12 = cos(lever_ang);
    double x13 = x12*x2;
    double x14 = 940.70000000000005*x13;
    double x15 = -x11 + x14;
    double x16 = x0*x15;
    double x17 = x0*x12;
    double x18 = 940.70000000000005*x17;
    double x19 = x2*x9;
    double x20 = 940.70000000000005*x19;
    double x21 = -x18 - x20;
    double x22 = x2*x21;
    double x23 = 1881.4000000000001*x10;
    double x24 = 1881.4000000000001*x13;
    double x25 = -x23 + x24;
    double x26 = 1160*x2;
    double x27 = 1881.4000000000001*x17;
    double x28 = 1881.4000000000001*x19;
    double x29 = -x27 - x28;
    double x30 = -4224*x0 - x26 + x29;
    double x31 = 4224*x2;
    double x32 = 1160*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 34012224000*x37;
    double x39 = 2112*x2;
    double x40 = 580*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 10497600*x37;
    double x45 = pow(x2, 2);
    double x46 = 10497600*x45;
    double x47 = pow(x43, 2);
    double x48 = 2112*x0;
    double x49 = 580*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 20995200*x2;
    double x56 = 6480*x54;
    double x57 = -1128*x0 + x51;
    double x58 = 1378*BC_len;
    double x59 = x2*x43;
    double x60 = 6480*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 474721;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 474721;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 275338180*x0 + 446570044.70000005*x10 - 446570044.70000005*x13 + 34012224000*pow(x2, 3) + x2*x38 + 535485288*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 20995200*x37;
    double x71 = 20995200*x45;
    double x72 = 2*x47 + 2*x53 - 12960*x54 - 12960*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2822.1000000000004*x17 - 2822.1000000000004*x19;
    double x76 = x25*x52;
    double x77 = 6480*x16;
    double x78 = x29*x43;
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
    double x89 = 446570044.70000005*x17 + 446570044.70000005*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x78 + x43*x76 - x43*x77 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x78 - x79 - x80)) + x89;
    double x91 = x73*(12960*x16 + 12960*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 474721;
    double x96 = 1128*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -2256*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 6480*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x78;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x77)) + x107*x33 + x109*(x108 + x77 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = 34012224000*x45;
    double x116 = x25 + x31 - x32;
    double x117 = x116*x52;
    double x118 = x30*x43;
    double x119 = x3*x82;
    double x120 = x3*x52;
    double x121 = x116*x82;
    double x122 = x30*x86;
    double x123 = -34012224000*pow(x0, 3) - x0*x115 + 20995200*x0*x59 - 535485288*x0 + x1*x36 - x1*x47 - x1*x53 + x117*x3 + x117*x43 - x118*x3 + 275338180*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-6336*x0 - 1740*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x119 + x120 + (1.0/2.0)*x121 + (1.0/2.0)*x122) + x66*((1.0/2.0)*x117 + (1.0/2.0)*x118 - x119 - x120)) + x89;
    double x124 = 12960*x2;
    double x125 = x123*x74 + x73*(x116*x30 + x124*x52 + x124*x82 + x30*x35);
    double x126 = x106*(x1 + x125);
    double x127 = x117 + x118;
    double x128 = 6480*x2;
    double x129 = x128*x82;
    double x130 = x128*x52;
    double x131 = x102*(x123*x97 + x127*x63 + x57*x69 + x95*(x127 - x129 - x130)) + x107*(2256*x2 + x34) + x109*(x121 + x122 + x129 + x130);
    double x132 = x112*(x131 + x92);
    double x133 = -x114*x44 - x114*x46 + x126 + x132 + 1;
    double x134 = imu_x*x0;
    double x135 = imu_y*x2;
    double x136 = -20120*x134 + 20120*x135;
    double x137 = x86 + x93;
    double x138 = x103 + x82;
    double x139 = 1.0/(pow(x137, 2) + pow(x138, 2));
    double x140 = x139*(x105 + x52);
    double x141 = x137*x139;
    double x142 = pow(x15, 2);
    double x143 = 1.0/(x142 + pow(x50, 2));
    double x144 = -x142*x143 - x143*pow(x21, 2) + 1;
    double x145 = -atan2(x138, x137) + atan2(x50, x15);
    double x146 = sin(x145);
    double x147 = cos(x145);
    double x148 = x12*x147 + x146*x9;
    double x149 = x12*x146 - x147*x9;
    double x150 = 39390130.0*imu_x*(-x0*x148 + x149*x2) + 39390130.0*imu_y*(x0*x149 + x148*x2);
    double x151 = 205.0*x10;
    double x152 = 653.20000000000005*x17;
    double x153 = 653.20000000000005*x19;
    double x154 = 205.0*x13;
    double x155 = -x151 + x152 + x153 + x154;
    double x156 = x151 - x152 - x153 - x154 + x48 + x49 - 18.200000000000045;
    double x157 = 653.20000000000005*x10 - 653.20000000000005*x13 + 205.0*x17 + 205.0*x19;
    double x158 = x157 + x39 + x41;
    double x159 = x158 - 450;
    double x160 = pow(x156, 2) + pow(x159, 2);
    double x161 = 1.0/x160;
    double x162 = x155 + x81;
    double x163 = x161*(x162 + 18.200000000000045);
    double x164 = x159*x161;
    double x165 = x155*x163 + x157*x164;
    double x166 = pow(x160, -1.0/2.0);
    double x167 = 176800*x166;
    double x168 = imu_x*x156;
    double x169 = imu_y*x159;
    double x170 = 479.5*x167*x168 - 479.5*x167*x169;
    double x171 = 264200*x166;
    double x172 = -528.89999999999998*x168*x171 + 528.89999999999998*x169*x171;
    double x173 = 20120*x113;
    double x174 = imu_y*x93;
    double x175 = imu_x*x103;
    double x176 = -x10 + x13;
    double x177 = x17 + x19;
    double x178 = -x17 - x19;
    double x179 = tilt_force*x166;
    double x180 = 205.0*x179;
    double x181 = 653.20000000000005*x179;
    double x182 = 63493900.0*imu_x*x176 + 38786757.999999985*imu_x*x178 + 38786757.999999985*imu_y*x176 + 63493900.0*imu_y*x177 - x156*x176*x181 + x156*x177*x180 + x159*x176*x180 - x159*x178*x181;
    double x183 = -3240*x113*x136 + x150*(x140*(x50 + x91) + x141*(x111 + x84) + x144) + x165*x170 + x165*x172 + x173*x174 - x173*x175 + x182;
    double x184 = x158*x164 + x162*x163;
    double x185 = 116*x0;
    double x186 = 726*x2;
    double x187 = x185 + x186;
    double x188 = x187 + 590;
    double x189 = 726*x0;
    double x190 = 116*x2;
    double x191 = x189 - x190 + 1622;
    double x192 = pow(x188, 2) + pow(x191, 2);
    double x193 = pow(x192, -1.0/2.0);
    double x194 = 332800*x193;
    double x195 = imu_x*x191;
    double x196 = imu_y*x188;
    double x197 = -x189 + x190;
    double x198 = 1.0/x192;
    double x199 = x187*x188*x198 + x197*x198*(x197 - 1622);
    double x200 = 195800*x193;
    double x201 = x159*x179;
    double x202 = lift_force*x193;
    double x203 = x188*x202;
    double x204 = x156*x179;
    double x205 = x191*x202;
    double x206 = 20120*x133;
    double x207 = -x113*x8*(-972626160*imu_x*x2 - 972626160*imu_y*x0 - 5901569000*x134 + 5901569000*x135 + x136*(x114*x115 + x114*x38 - 3240*x126 - 3240*x132) + x150*(x140*(x125 + x52) + x141*(x131 + x86) + x144) + x170*x184 + x172*x184 + x174*x206 - x175*x206 + x182 + x185*x205 + x186*x205 - x189*x203 + x190*x203 + 673.79999999999995*x199*(-x194*x195 + x194*x196) + 667.60000000000002*x199*(x195*x200 - x196*x200) - x201*x48 - x201*x49 + x204*x39 - x204*x40) + x133*x183*x8;
    double mass_result = x207/(x113*x4*x8);
    double dist_result = -x183*x4/x207;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_980_14A_LOG(
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
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_980_14A_LOG(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 2112*x0;
    double x8 = 580*x1;
    double x9 = -x8;
    double x10 = 3240*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 3240*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 580*x0;
    double x16 = -x15;
    double x17 = 2112*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 + 410195.49000000011;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -1128*x1 + x16 - x6;
    double x30 = x28 - 63352.89000000013;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 2655922.0900000003;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(1128*x0 + x4 + x9);
    double x34 = 237913384.20000005*x0 + 462700512.72000027*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 + 410195.49000000011*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 1160*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 2256*x0 + x37 + x38;
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
    double x61 = 1160*x0;
    double x62 = 4224*x1;
    double x63 = x61 - x62;
    double x64 = 4224*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 - 410195.49000000011*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(2320*x0 - 8448*x1) - x6*(-8448*x0 - 2320*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 80361.759999999966*x74;
    double x76 = 297671.0*x74;
    double tilt_sensitivity = (1498458.4000000001*x49*x74 + 54104.0*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(445123.19999999984*x0 - 1921912.0*x1 + 108208.0*x49 - 2996916.8000000003*x50 - 595342.0*x51 - 160723.51999999993*x52 - 160723.51999999993*x53 + 595342.0*x54 + 5468470.4800000004, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_980_14A_LOG(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 445123.19999999984*x0;
    double x3 = 1921912.0*x1;
    double x4 = 580*x0;
    double x5 = 2112*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 2112*x0;
    double x9 = 580*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 202831.23999999999;
    double x15 = pow(tilt_cyl_ext + 1193, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1369.2264093275444*tilt_cyl_ext;
    double x19 = 354506560.0*x0 - 1426365168.0*x1 - 36.400000000000091*x10*x6 + x11*x6 + 450*x11 + x15*x6 - 450*x15 + pow(x6, 3) - 450*x7 + sqrt((x13 - x15 + x18 + 1367623.1063277605)*(-x11 + x15 + x18 - x2 + x3 - x7 + 1899351.1063277605))*(x17 + 18.200000000000045) + 302186916.0;
    double lever_ang = -atan2(3240*x0, 3240*x1) + atan2(x17 + (x14*(x12 + x15 - 671526.47999999998) + x19*(x16 + 450))/(x14*(4224*x0 + 1160*x1 - 36.400000000000091)), x16 + x19/(890246.39999999967*x0 - 3843824.0*x1 + 2*x11 + 2*x7 + 405662.47999999998)) + 2.8374878698199093;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_980_14A_LOG(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_980_14A_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 10497600*x6;
    double x8 = pow(x0, 2);
    double x9 = 10497600*x8;
    double x10 = 580*x0;
    double x11 = x0*x4;
    double x12 = 940.70000000000005*x11;
    double x13 = x1*x2;
    double x14 = 940.70000000000005*x13;
    double x15 = 2112*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 6480*x16;
    double x18 = 580*x1 + 940.70000000000005*x3 + 940.70000000000005*x5;
    double x19 = 2112*x0 + x18;
    double x20 = x0*x19;
    double x21 = 6480*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 3240*x1;
    double x29 = 1378*BC_len;
    double x30 = 275338180*x0 + 34012224000*pow(x1, 3) - 20995200*x1*x20 + 34012224000*x1*x8 + 535485288*x1 + 446570044.70000005*x11 - 446570044.70000005*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 474721)*(x17 + x21 - x22 - x23 + x27 + x29 + 474721))*(-1128*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-3240*x0 + (x25*(x24 + x27 - 474721) + x30*(1128*x1 + x10 + x12 - x14))/(x25*(-2256*x0 + 1160*x1 + 1881.4000000000001*x3 + 1881.4000000000001*x5)), -x28 + x30/(-12960*x16 - 12960*x20 + 2*x22 + 2*x23 + 20995200*x6 + 20995200*x8));

    return bucket_ang;
}
