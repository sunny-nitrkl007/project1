/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2021
*
* GENERATED :
*       2021-02-22T19:00:30-06:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_972_14A_SL.h"

void mass_and_dist_972_14A_SL(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_972_14A_SL(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 2936*x0;
    double x2 = cos(arm_ang);
    double x3 = 2936*x2;
    double x4 = -imu_x*x1 + imu_y*x3;
    double x5 = pow(imu_x, 2);
    double x6 = pow(imu_y, 2);
    double x7 = pow(x5 + x6, -1.0/2.0);
    double x8 = -x5*x7 - x6*x7;
    double x9 = sin(lever_ang);
    double x10 = x0*x9;
    double x11 = 959.0*x10;
    double x12 = cos(lever_ang);
    double x13 = x12*x2;
    double x14 = 959.0*x13;
    double x15 = -x11 + x14;
    double x16 = x0*x15;
    double x17 = x0*x12;
    double x18 = 959.0*x17;
    double x19 = x2*x9;
    double x20 = 959.0*x19;
    double x21 = -x18 - x20;
    double x22 = x2*x21;
    double x23 = 1918.0*x10;
    double x24 = 1918.0*x13;
    double x25 = -x23 + x24;
    double x26 = 1240*x2;
    double x27 = 1918.0*x17;
    double x28 = 1918.0*x19;
    double x29 = -x27 - x28;
    double x30 = -3586*x0 - x26 + x29;
    double x31 = 3586*x2;
    double x32 = 1240*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 25308601856*x37;
    double x39 = 1793*x2;
    double x40 = 620*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 8620096*x37;
    double x45 = pow(x2, 2);
    double x46 = 8620096*x45;
    double x47 = pow(x43, 2);
    double x48 = 1793*x0;
    double x49 = 620*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 17240192*x2;
    double x56 = 5872*x54;
    double x57 = -1143*x0 + x51;
    double x58 = 1416.8*BC_len;
    double x59 = x2*x43;
    double x60 = 5872*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 501830.55999999994;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 501830.55999999994;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 311134947.19999999*x0 + 481255507.03999996*x10 - 481255507.03999996*x13 + 25308601856*pow(x2, 3) + x2*x38 + 573592330.07999992*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 17240192*x37;
    double x71 = 17240192*x45;
    double x72 = 2*x47 + 2*x53 - 11744*x54 - 11744*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2877.0*x17 - 2877.0*x19;
    double x76 = x25*x52;
    double x77 = 5872*x16;
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
    double x89 = 481255507.03999996*x17 + 481255507.03999996*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x78 + x43*x76 - x43*x77 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x78 - x79 - x80)) + x89;
    double x91 = x73*(11744*x16 + 11744*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 501830.55999999994;
    double x96 = 1143*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -2286*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 5872*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x78;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x77)) + x107*x33 + x109*(x108 + x77 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = 25308601856*x45;
    double x116 = x25 + x31 - x32;
    double x117 = x116*x52;
    double x118 = x30*x43;
    double x119 = x3*x82;
    double x120 = x3*x52;
    double x121 = x116*x82;
    double x122 = x30*x86;
    double x123 = -25308601856*pow(x0, 3) - x0*x115 + 17240192*x0*x59 - 573592330.07999992*x0 + x1*x36 - x1*x47 - x1*x53 + x117*x3 + x117*x43 - x118*x3 + 311134947.19999999*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-5379*x0 - 1860*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x119 + x120 + (1.0/2.0)*x121 + (1.0/2.0)*x122) + x66*((1.0/2.0)*x117 + (1.0/2.0)*x118 - x119 - x120)) + x89;
    double x124 = 11744*x2;
    double x125 = x123*x74 + x73*(x116*x30 + x124*x52 + x124*x82 + x30*x35);
    double x126 = x106*(x1 + x125);
    double x127 = x117 + x118;
    double x128 = 5872*x2;
    double x129 = x128*x82;
    double x130 = x128*x52;
    double x131 = x102*(x123*x97 + x127*x63 + x57*x69 + x95*(x127 - x129 - x130)) + x107*(2286*x2 + x34) + x109*(x121 + x122 + x129 + x130);
    double x132 = x112*(x131 + x92);
    double x133 = -x114*x44 - x114*x46 + x126 + x132 + 1;
    double x134 = imu_x*x0;
    double x135 = imu_y*x2;
    double x136 = -13350*x134 + 13350*x135;
    double x137 = 222.40000000000001*x10;
    double x138 = 696.39999999999998*x17;
    double x139 = 696.39999999999998*x19;
    double x140 = 222.40000000000001*x13;
    double x141 = -x137 + x138 + x139 + x140;
    double x142 = x137 - x138 - x139 - x140 + x48 + x49 - 43.200000000000045;
    double x143 = 696.39999999999998*x10 - 696.39999999999998*x13 + 222.40000000000001*x17 + 222.40000000000001*x19;
    double x144 = x143 + x39 + x41;
    double x145 = x144 - 378.70000000000005;
    double x146 = pow(x142, 2) + pow(x145, 2);
    double x147 = 1.0/x146;
    double x148 = x141 + x81;
    double x149 = x147*(x148 + 43.200000000000045);
    double x150 = x145*x147;
    double x151 = x141*x149 + x143*x150;
    double x152 = pow(x146, -1.0/2.0);
    double x153 = 198800*x152;
    double x154 = imu_x*x142;
    double x155 = imu_y*x145;
    double x156 = -532.64999999999998*x153*x154 + 532.64999999999998*x153*x155;
    double x157 = x86 + x93;
    double x158 = x103 + x82;
    double x159 = 1.0/(pow(x157, 2) + pow(x158, 2));
    double x160 = x159*(x105 + x52);
    double x161 = x157*x159;
    double x162 = pow(x15, 2);
    double x163 = 1.0/(x162 + pow(x50, 2));
    double x164 = -x162*x163 - x163*pow(x21, 2) + 1;
    double x165 = -atan2(x158, x157) + atan2(x50, x15);
    double x166 = sin(x165);
    double x167 = cos(x165);
    double x168 = x12*x167 + x166*x9;
    double x169 = x12*x166 - x167*x9;
    double x170 = 22063118.0*imu_x*(-x0*x168 + x169*x2) + 22063118.0*imu_y*(x0*x169 + x168*x2);
    double x171 = 80570*x152;
    double x172 = 481.83999999999997*x154*x171 - 481.83999999999997*x155*x171;
    double x173 = 13350*x113;
    double x174 = imu_y*x93;
    double x175 = imu_x*x103;
    double x176 = -x10 + x13;
    double x177 = x17 + x19;
    double x178 = -x17 - x19;
    double x179 = tilt_force*x152;
    double x180 = 222.40000000000001*x179;
    double x181 = 696.39999999999998*x179;
    double x182 = 33771312.0*imu_x*x176 + 59281708.0*imu_x*x178 + 59281708.0*imu_y*x176 + 33771312.0*imu_y*x177 - x142*x176*x181 + x142*x177*x180 + x145*x176*x180 - x145*x178*x181;
    double x183 = -2936*x113*x136 + x151*x156 + x151*x172 + x170*(x160*(x50 + x91) + x161*(x111 + x84) + x164) + x173*x174 - x173*x175 + x182;
    double x184 = 31.800000000000001*x0;
    double x185 = 1659.7*x2;
    double x186 = -x184 + x185;
    double x187 = x186 + 131.39999999999998;
    double x188 = 1659.7*x0;
    double x189 = 31.800000000000001*x2;
    double x190 = x188 + x189 + 683;
    double x191 = pow(x187, 2) + pow(x190, 2);
    double x192 = pow(x191, -1.0/2.0);
    double x193 = 162040*x192;
    double x194 = imu_x*x190;
    double x195 = imu_y*x187;
    double x196 = -x188 - x189;
    double x197 = 1.0/x191;
    double x198 = x186*x187*x197 + x196*x197*(x196 - 683);
    double x199 = x144*x150 + x148*x149;
    double x200 = 596200*x192;
    double x201 = x145*x179;
    double x202 = x142*x179;
    double x203 = 13350*x133;
    double x204 = lift_force*x192;
    double x205 = x190*x204;
    double x206 = x187*x204;
    double x207 = -x113*x8*(-701297461.20000005*imu_x*x2 - 701297461.20000005*imu_y*x0 - 3599573985.8000002*x134 + 3599573985.8000002*x135 + x136*(x114*x115 + x114*x38 - 2936*x126 - 2936*x132) + x156*x199 + x170*(x160*(x125 + x52) + x161*(x131 + x86) + x164) + x172*x199 + x174*x203 - x175*x203 + x182 - x184*x205 + x185*x205 - x188*x206 - x189*x206 + 649.80999999999995*x198*(x193*x194 - x193*x195) + 681.84000000000003*x198*(-x194*x200 + x195*x200) - x201*x48 - x201*x49 + x202*x39 - x202*x40) + x133*x183*x8;
    double mass_result = x207/(x113*x4*x8);
    double dist_result = -x183*x4/x207;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_972_14A_SL(
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
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_972_14A_SL(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 1793*x0;
    double x8 = 620*x1;
    double x9 = -x8;
    double x10 = 2936*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 2936*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 620*x0;
    double x16 = -x15;
    double x17 = 1793*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 + 417850.44000000006;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -1143*x1 + x16 - x6;
    double x30 = x28 - 62800.360000000102;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 2780222.7599999998;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(1143*x0 + x4 + x9);
    double x34 = 259067272.80000001*x0 + 477603052.92000008*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 + 417850.44000000006*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 1240*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 2286*x0 + x37 + x38;
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
    double x61 = 1240*x0;
    double x62 = 3586*x1;
    double x63 = x61 - x62;
    double x64 = 3586*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 - 417850.44000000006*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(2480*x0 - 7172*x1) - x6*(-7172*x0 - 2480*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 54138.399999999987*x74;
    double x76 = 273334.36000000004*x74;
    double tilt_sensitivity = (1386533.2*x49*x74 - 33004.799999999988*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(314672.79999999993*x0 - 1411586.2000000002*x1 - 66009.599999999977*x49 - 2773066.3999999999*x50 - 546668.72000000009*x51 - 108276.79999999997*x52 - 108276.79999999997*x53 + 546668.72000000009*x54 + 4278963.6500000004, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_972_14A_SL(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 314672.79999999993*x0;
    double x3 = 1411586.2000000002*x1;
    double x4 = 620*x0;
    double x5 = 1793*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 1793*x0;
    double x9 = 620*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 145279.93000000002;
    double x15 = pow(tilt_cyl_ext + 1080, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1462.1008446752228*tilt_cyl_ext;
    double x19 = 360442559.15999991*x0 - 1232322232.4099998*x1 - 86.400000000000091*x10*x6 + x11*x6 + 378.70000000000005*x11 + x15*x6 - 378.70000000000005*x15 + pow(x6, 3) - 378.70000000000005*x7 + sqrt((x13 - x15 + x18 + 1189914.1222492405)*(-x11 + x15 + x18 - x2 + x3 - x7 + 1968223.7022492406))*(x17 + 43.200000000000045) + 257407937.95500004;
    double lever_ang = -atan2(2936*x0, 2936*x1) + atan2(x17 + (x14*(x12 + x15 - 679714.65000000002) + x19*(x16 + 378.70000000000005))/(x14*(3586*x0 + 1240*x1 - 86.400000000000091)), x16 + x19/(629345.59999999986*x0 - 2823172.4000000004*x1 + 2*x11 + 2*x7 + 290559.86000000004)) + 2.8324733706240677;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_972_14A_SL(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_972_14A_SL(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 8620096*x6;
    double x8 = pow(x0, 2);
    double x9 = 8620096*x8;
    double x10 = 620*x0;
    double x11 = x0*x4;
    double x12 = 959.0*x11;
    double x13 = x1*x2;
    double x14 = 959.0*x13;
    double x15 = 1793*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 5872*x16;
    double x18 = 620*x1 + 959.0*x3 + 959.0*x5;
    double x19 = 1793*x0 + x18;
    double x20 = x0*x19;
    double x21 = 5872*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 2936*x1;
    double x29 = 1416.8*BC_len;
    double x30 = 311134947.19999999*x0 + 25308601856*pow(x1, 3) - 17240192*x1*x20 + 25308601856*x1*x8 + 573592330.07999992*x1 + 481255507.03999996*x11 - 481255507.03999996*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 501830.55999999994)*(x17 + x21 - x22 - x23 + x27 + x29 + 501830.55999999994))*(-1143*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-2936*x0 + (x25*(x24 + x27 - 501830.55999999994) + x30*(1143*x1 + x10 + x12 - x14))/(x25*(-2286*x0 + 1240*x1 + 1918.0*x3 + 1918.0*x5)), -x28 + x30/(-11744*x16 - 11744*x20 + 2*x22 + 2*x23 + 17240192*x6 + 17240192*x8));

    return bucket_ang;
}
