/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2022
*
* GENERATED :
*       2022-03-17T18:51:22-05:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_950_14A_HL.h"

void mass_and_dist_950_14A_HL(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_950_14A_HL(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 3351.5*x0;
    double x2 = cos(arm_ang);
    double x3 = 3351.5*x2;
    double x4 = -imu_x*x1 + imu_y*x3;
    double x5 = pow(imu_x, 2);
    double x6 = pow(imu_y, 2);
    double x7 = pow(x5 + x6, -1.0/2.0);
    double x8 = -x5*x7 - x6*x7;
    double x9 = sin(lever_ang);
    double x10 = x0*x9;
    double x11 = 800.0*x10;
    double x12 = cos(lever_ang);
    double x13 = x12*x2;
    double x14 = 800.0*x13;
    double x15 = -x11 + x14;
    double x16 = x0*x15;
    double x17 = x0*x12;
    double x18 = 800.0*x17;
    double x19 = x2*x9;
    double x20 = 800.0*x19;
    double x21 = -x18 - x20;
    double x22 = x2*x21;
    double x23 = 1600.0*x10;
    double x24 = 1600.0*x13;
    double x25 = -x23 + x24;
    double x26 = 985.39999999999998*x2;
    double x27 = 1600.0*x17;
    double x28 = 1600.0*x19;
    double x29 = -x27 - x28;
    double x30 = -4246*x0 - x26 + x29;
    double x31 = 4246*x2;
    double x32 = 985.39999999999998*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 37645898865.875*x37;
    double x39 = 2123*x2;
    double x40 = 492.69999999999999*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 11232552.25*x37;
    double x45 = pow(x2, 2);
    double x46 = 11232552.25*x45;
    double x47 = pow(x43, 2);
    double x48 = 2123*x0;
    double x49 = 492.69999999999999*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 22465104.5*x2;
    double x56 = 6703.0*x54;
    double x57 = -1228.5*x0 + x51;
    double x58 = 1831.4000000000001*BC_len;
    double x59 = x2*x43;
    double x60 = 6703.0*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 838506.49000000011;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 838506.49000000011;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 413132147.62300003*x0 + 670805192.00000012*x10 - 670805192.00000012*x13 + 37645898865.875*pow(x2, 3) + x2*x38 + 1030105222.9649999*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 22465104.5*x37;
    double x71 = 22465104.5*x45;
    double x72 = 2*x47 + 2*x53 - 13406.0*x54 - 13406.0*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2400.0*x17 - 2400.0*x19;
    double x76 = x25*x52;
    double x77 = x29*x43;
    double x78 = 6703.0*x16;
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
    double x89 = 670805192.00000012*x17 + 670805192.00000012*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x77 + x43*x76 - x43*x78 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x77 - x79 - x80)) + x89;
    double x91 = x73*(13406.0*x16 + 13406.0*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 838506.49000000011;
    double x96 = 1228.5*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -2457.0*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 6703.0*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x77;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x78)) + x107*x33 + x109*(x108 + x78 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = 37645898865.875*x45;
    double x116 = x25 + x31 - x32;
    double x117 = x116*x52;
    double x118 = x30*x43;
    double x119 = x3*x82;
    double x120 = x3*x52;
    double x121 = x116*x82;
    double x122 = x30*x86;
    double x123 = -37645898865.875*pow(x0, 3) - x0*x115 + 22465104.5*x0*x59 - 1030105222.9649999*x0 + x1*x36 - x1*x47 - x1*x53 + x117*x3 + x117*x43 - x118*x3 + 413132147.62300003*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-6369*x0 - 1478.0999999999999*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x119 + x120 + (1.0/2.0)*x121 + (1.0/2.0)*x122) + x66*((1.0/2.0)*x117 + (1.0/2.0)*x118 - x119 - x120)) + x89;
    double x124 = 13406.0*x2;
    double x125 = x123*x74 + x73*(x116*x30 + x124*x52 + x124*x82 + x30*x35);
    double x126 = x106*(x1 + x125);
    double x127 = x117 + x118;
    double x128 = 6703.0*x2;
    double x129 = x128*x82;
    double x130 = x128*x52;
    double x131 = x102*(x123*x97 + x127*x63 + x57*x69 + x95*(x127 - x129 - x130)) + x107*(2457.0*x2 + x34) + x109*(x121 + x122 + x129 + x130);
    double x132 = x112*(x131 + x92);
    double x133 = -x114*x44 - x114*x46 + x126 + x132 + 1;
    double x134 = 117.2*x10;
    double x135 = 664.70000000000005*x17;
    double x136 = 664.70000000000005*x19;
    double x137 = 117.2*x13;
    double x138 = -x134 + x135 + x136 + x137;
    double x139 = x134 - x135 - x136 - x137 + x48 + x49 + 115;
    double x140 = 664.70000000000005*x10 - 664.70000000000005*x13 + 117.2*x17 + 117.2*x19;
    double x141 = x140 + x39 + x41;
    double x142 = x141 - 325;
    double x143 = pow(x139, 2) + pow(x142, 2);
    double x144 = 1.0/x143;
    double x145 = x138 + x81;
    double x146 = x144*(x145 - 115);
    double x147 = x142*x144;
    double x148 = x138*x146 + x140*x147;
    double x149 = pow(x143, -1.0/2.0);
    double x150 = 133260*x149;
    double x151 = imu_x*x139;
    double x152 = imu_y*x142;
    double x153 = -530.48000000000002*x150*x151 + 530.48000000000002*x150*x152;
    double x154 = 91740*x149;
    double x155 = 576.79999999999995*x151*x154 - 576.79999999999995*x152*x154;
    double x156 = x86 + x93;
    double x157 = x103 + x82;
    double x158 = 1.0/(pow(x156, 2) + pow(x157, 2));
    double x159 = x158*(x105 + x52);
    double x160 = x156*x158;
    double x161 = pow(x15, 2);
    double x162 = 1.0/(x161 + pow(x50, 2));
    double x163 = -x161*x162 - x162*pow(x21, 2) + 1;
    double x164 = -atan2(x157, x156) + atan2(x50, x15);
    double x165 = sin(x164);
    double x166 = cos(x164);
    double x167 = x12*x166 + x165*x9;
    double x168 = x12*x165 - x166*x9;
    double x169 = 37795517.5*imu_x*(-x0*x167 + x168*x2) + 37795517.5*imu_y*(x0*x168 + x167*x2);
    double x170 = imu_x*x0;
    double x171 = imu_y*x2;
    double x172 = -19240*x170 + 19240*x171;
    double x173 = 19240*x113;
    double x174 = imu_y*x93;
    double x175 = imu_x*x103;
    double x176 = -x10 + x13;
    double x177 = x17 + x19;
    double x178 = -x17 - x19;
    double x179 = tilt_force*x149;
    double x180 = 117.2*x179;
    double x181 = 664.70000000000005*x179;
    double x182 = 20562784.0*imu_x*x176 + 31198815.999999993*imu_x*x178 + 31198815.999999993*imu_y*x176 + 20562784.0*imu_y*x177 - x139*x176*x181 + x139*x177*x180 + x142*x176*x180 - x142*x178*x181;
    double x183 = -3351.5*x113*x172 + x148*x153 + x148*x155 + x169*(x159*(x50 + x91) + x160*(x111 + x84) + x163) + x173*x174 - x173*x175 + x182;
    double x184 = 56.100000000000001*x0;
    double x185 = 665*x2;
    double x186 = x184 + x185;
    double x187 = x186 + 405;
    double x188 = 665*x0;
    double x189 = 56.100000000000001*x2;
    double x190 = x188 - x189 + 1335;
    double x191 = pow(x187, 2) + pow(x190, 2);
    double x192 = pow(x191, -1.0/2.0);
    double x193 = 165000*x192;
    double x194 = imu_x*x190;
    double x195 = imu_y*x187;
    double x196 = -x188 + x189;
    double x197 = 1.0/x191;
    double x198 = x186*x187*x197 + x196*x197*(x196 - 1335);
    double x199 = 128600*x192;
    double x200 = x141*x147 + x145*x146;
    double x201 = x142*x179;
    double x202 = lift_force*x192;
    double x203 = x187*x202;
    double x204 = x190*x202;
    double x205 = x139*x179;
    double x206 = 19240*x133;
    double x207 = -x113*x8*(-512252393.0*imu_x*x2 - 512252393.0*imu_y*x0 + x153*x200 + x155*x200 + x169*(x159*(x125 + x52) + x160*(x131 + x86) + x163) - 3979977968.0*x170 + 3979977968.0*x171 + x172*(x114*x115 + x114*x38 - 3351.5*x126 - 3351.5*x132) + x174*x206 - x175*x206 + x182 + x184*x204 + x185*x204 - x188*x203 + x189*x203 + 439*x198*(-x193*x194 + x193*x195) + 554*x198*(x194*x199 - x195*x199) - x201*x48 - x201*x49 + x205*x39 - x205*x40) + x133*x183*x8;
    double mass_result = x207/(x113*x4*x8);
    double dist_result = -x183*x4/x207;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_950_14A_HL(
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
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_950_14A_HL(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 2123*x0;
    double x8 = 492.69999999999999*x1;
    double x9 = -x8;
    double x10 = 3351.5*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 3351.5*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 492.69999999999999*x0;
    double x16 = -x15;
    double x17 = 2123*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 - 198506.49000000011;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -1228.5*x1 + x16 - x6;
    double x30 = x28 - 13386.490000000224;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 2943626.4900000002;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(1228.5*x0 + x4 + x9);
    double x34 = -97804147.623000026*x0 - 243865222.96499968*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 - 198506.49000000011*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 985.39999999999998*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 2457.0*x0 + x37 + x38;
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
    double x61 = 985.39999999999998*x0;
    double x62 = 4246*x1;
    double x63 = x61 - x62;
    double x64 = 4246*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 + 198506.49000000011*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(1970.8*x0 - 8492*x1) - x6*(-8492*x0 - 1970.8*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 114530.5*x74;
    double x76 = 202549.50000000003*x74;
    double tilt_sensitivity = (1468902.54*x49*x74 - 78682.089999999997*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(808545.0*x0 - 1266629.0*x1 - 157364.17999999999*x49 - 2937805.0800000001*x50 - 405099.00000000006*x51 - 229061.0*x52 - 229061.0*x53 + 405099.00000000006*x54 + 5324294.2199999997, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_950_14A_HL(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 808545.0*x0;
    double x3 = 1266629.0*x1;
    double x4 = 492.69999999999999*x0;
    double x5 = 2123*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 2123*x0;
    double x9 = 492.69999999999999*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 118850;
    double x15 = pow(tilt_cyl_ext + 1471, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1349.9065597292283*tilt_cyl_ext;
    double x19 = 428675092.91100001*x0 - 1126493852.3900003*x1 + 230*x10*x6 + x11*x6 + 325*x11 + x15*x6 - 325*x15 + pow(x6, 3) - 325*x7 + sqrt((x13 - x15 + x18 + 1649000.6193616949)*(-x11 + x15 + x18 - x2 + x3 - x7 + 2322424.4793616948))*(x17 - 115) + 186683877.25000003;
    double lever_ang = -atan2(3351.5*x0, 3351.5*x1) + atan2(x17 + (x14*(x12 + x15 - 574411.93000000017) + x19*(x16 + 325))/(x14*(4246*x0 + 985.39999999999998*x1 + 230)), x16 + x19/(1617090.0*x0 - 2533258.0*x1 + 2*x11 + 2*x7 + 237700)) + 2.9670663585413815;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_950_14A_HL(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_950_14A_HL(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 11232552.25*x6;
    double x8 = pow(x0, 2);
    double x9 = 11232552.25*x8;
    double x10 = 492.69999999999999*x0;
    double x11 = x0*x4;
    double x12 = 800.0*x11;
    double x13 = x1*x2;
    double x14 = 800.0*x13;
    double x15 = 2123*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 6703.0*x16;
    double x18 = 492.69999999999999*x1 + 800.0*x3 + 800.0*x5;
    double x19 = 2123*x0 + x18;
    double x20 = x0*x19;
    double x21 = 6703.0*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 3351.5*x1;
    double x29 = 1831.4000000000001*BC_len;
    double x30 = 413132147.62300003*x0 + 37645898865.875*pow(x1, 3) - 22465104.5*x1*x20 + 37645898865.875*x1*x8 + 1030105222.9649999*x1 + 670805192.00000012*x11 - 670805192.00000012*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 838506.49000000011)*(x17 + x21 - x22 - x23 + x27 + x29 + 838506.49000000011))*(-1228.5*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-3351.5*x0 + (x25*(x24 + x27 - 838506.49000000011) + x30*(1228.5*x1 + x10 + x12 - x14))/(x25*(-2457.0*x0 + 985.39999999999998*x1 + 1600.0*x3 + 1600.0*x5)), -x28 + x30/(-13406.0*x16 - 13406.0*x20 + 2*x22 + 2*x23 + 22465104.5*x6 + 22465104.5*x8));

    return bucket_ang;
}
