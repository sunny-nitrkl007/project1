/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2022
*
* GENERATED :
*       2022-03-17T18:59:35-05:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_950_14A_Z_LOG.h"

void mass_and_dist_950_14A_Z_LOG(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_950_14A_Z_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 2795*x0;
    double x2 = cos(arm_ang);
    double x3 = 2795*x2;
    double x4 = -imu_x*x1 + imu_y*x3;
    double x5 = pow(imu_x, 2);
    double x6 = pow(imu_y, 2);
    double x7 = pow(x5 + x6, -1.0/2.0);
    double x8 = -x5*x7 - x6*x7;
    double x9 = sin(lever_ang);
    double x10 = x0*x9;
    double x11 = 766.79999999999995*x10;
    double x12 = cos(lever_ang);
    double x13 = x12*x2;
    double x14 = 766.79999999999995*x13;
    double x15 = -x11 + x14;
    double x16 = x0*x15;
    double x17 = x0*x12;
    double x18 = 766.79999999999995*x17;
    double x19 = x2*x9;
    double x20 = 766.79999999999995*x19;
    double x21 = -x18 - x20;
    double x22 = x2*x21;
    double x23 = 1533.5999999999999*x10;
    double x24 = 1533.5999999999999*x13;
    double x25 = -x23 + x24;
    double x26 = 1216*x2;
    double x27 = 1533.5999999999999*x17;
    double x28 = 1533.5999999999999*x19;
    double x29 = -x27 - x28;
    double x30 = -3618*x0 - x26 + x29;
    double x31 = 3618*x2;
    double x32 = 1216*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 21834609875*x37;
    double x39 = 1809*x2;
    double x40 = 608*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 7812025*x37;
    double x45 = pow(x2, 2);
    double x46 = 7812025*x45;
    double x47 = pow(x43, 2);
    double x48 = 1809*x0;
    double x49 = 608*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 15624050*x2;
    double x56 = 5590*x54;
    double x57 = -986*x0 + x51;
    double x58 = 1572*BC_len;
    double x59 = x2*x43;
    double x60 = 5590*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 617796;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 617796;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 375619968*x0 + 473725972.79999995*x10 - 473725972.79999995*x13 + 21834609875*pow(x2, 3) + x2*x38 + 609146856*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 15624050*x37;
    double x71 = 15624050*x45;
    double x72 = 2*x47 + 2*x53 - 11180*x54 - 11180*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2300.3999999999996*x17 - 2300.3999999999996*x19;
    double x76 = x25*x52;
    double x77 = 5590*x16;
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
    double x89 = 473725972.79999995*x17 + 473725972.79999995*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x78 + x43*x76 - x43*x77 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x78 - x79 - x80)) + x89;
    double x91 = x73*(11180*x16 + 11180*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 617796;
    double x96 = 986*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -1972*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 5590*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x78;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x77)) + x107*x33 + x109*(x108 + x77 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = 21834609875*x45;
    double x116 = x25 + x31 - x32;
    double x117 = x116*x52;
    double x118 = x30*x43;
    double x119 = x3*x82;
    double x120 = x3*x52;
    double x121 = x116*x82;
    double x122 = x30*x86;
    double x123 = -21834609875*pow(x0, 3) - x0*x115 + 15624050*x0*x59 - 609146856*x0 + x1*x36 - x1*x47 - x1*x53 + x117*x3 + x117*x43 - x118*x3 + 375619968*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-5427*x0 - 1824*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x119 + x120 + (1.0/2.0)*x121 + (1.0/2.0)*x122) + x66*((1.0/2.0)*x117 + (1.0/2.0)*x118 - x119 - x120)) + x89;
    double x124 = 11180*x2;
    double x125 = x123*x74 + x73*(x116*x30 + x124*x52 + x124*x82 + x30*x35);
    double x126 = x106*(x1 + x125);
    double x127 = x117 + x118;
    double x128 = 5590*x2;
    double x129 = x128*x82;
    double x130 = x128*x52;
    double x131 = x102*(x123*x97 + x127*x63 + x57*x69 + x95*(x127 - x129 - x130)) + x107*(1972*x2 + x34) + x109*(x121 + x122 + x129 + x130);
    double x132 = x112*(x131 + x92);
    double x133 = -x114*x44 - x114*x46 + x126 + x132 + 1;
    double x134 = imu_x*x0;
    double x135 = imu_y*x2;
    double x136 = -9627*x134 + 9627*x135;
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
    double x150 = 21064800*imu_x*(-x0*x148 + x149*x2) + 21064800*imu_y*(x0*x149 + x148*x2);
    double x151 = 218.40000000000001*x10;
    double x152 = 522.89999999999998*x17;
    double x153 = 522.89999999999998*x19;
    double x154 = 218.40000000000001*x13;
    double x155 = -x151 + x152 + x153 + x154;
    double x156 = x151 - x152 - x153 - x154 + x48 + x49 + 8.2999999999999545;
    double x157 = 522.89999999999998*x10 - 522.89999999999998*x13 + 218.40000000000001*x17 + 218.40000000000001*x19;
    double x158 = x157 + x39 + x41;
    double x159 = x158 - 368;
    double x160 = pow(x156, 2) + pow(x159, 2);
    double x161 = 1.0/x160;
    double x162 = x155 + x81;
    double x163 = x161*(x162 - 8.2999999999999545);
    double x164 = x159*x161;
    double x165 = x155*x163 + x157*x164;
    double x166 = pow(x160, -1.0/2.0);
    double x167 = 76000*x166;
    double x168 = imu_x*x156;
    double x169 = imu_y*x159;
    double x170 = 571*x167*x168 - 571*x167*x169;
    double x171 = 171500*x166;
    double x172 = -593.77999999999997*x168*x171 + 593.77999999999997*x169*x171;
    double x173 = 9627*x113;
    double x174 = imu_y*x93;
    double x175 = imu_x*x103;
    double x176 = -x10 + x13;
    double x177 = x17 + x19;
    double x178 = -x17 - x19;
    double x179 = tilt_force*x166;
    double x180 = 218.40000000000001*x179;
    double x181 = 522.89999999999998*x179;
    double x182 = 27341136.0*imu_x*x176 + 27872658.0*imu_x*x178 + 27872658.0*imu_y*x176 + 27341136.0*imu_y*x177 - x156*x176*x181 + x156*x177*x180 + x159*x176*x180 - x159*x178*x181;
    double x183 = -2795*x113*x136 + x150*(x140*(x50 + x91) + x141*(x111 + x84) + x144) + x165*x170 + x165*x172 + x173*x174 - x173*x175 + x182;
    double x184 = 105*x0;
    double x185 = 1601*x2;
    double x186 = -x184 + x185;
    double x187 = x186 + 81.399999999999977;
    double x188 = 1601*x0;
    double x189 = 105*x2;
    double x190 = x188 + x189 + 669.60000000000002;
    double x191 = pow(x187, 2) + pow(x190, 2);
    double x192 = pow(x191, -1.0/2.0);
    double x193 = 145600*x192;
    double x194 = imu_x*x190;
    double x195 = imu_y*x187;
    double x196 = -x188 - x189;
    double x197 = 1.0/x191;
    double x198 = x186*x187*x197 + x196*x197*(x196 - 669.60000000000002);
    double x199 = x158*x164 + x162*x163;
    double x200 = 137200*x192;
    double x201 = x159*x179;
    double x202 = lift_force*x192;
    double x203 = x187*x202;
    double x204 = x156*x179;
    double x205 = x190*x202;
    double x206 = 9627*x133;
    double x207 = -x113*x8*(-554043870.0*imu_x*x2 - 554043870.0*imu_y*x0 - 2614667804.0*x134 + 2614667804.0*x135 + x136*(x114*x115 + x114*x38 - 2795*x126 - 2795*x132) + x150*(x140*(x125 + x52) + x141*(x131 + x86) + x144) + x170*x199 + x172*x199 + x174*x206 - x175*x206 + x182 - x184*x205 + x185*x205 - x188*x203 - x189*x203 + 533*x198*(-x193*x194 + x193*x195) + 583*x198*(x194*x200 - x195*x200) - x201*x48 - x201*x49 + x204*x39 - x204*x40) + x133*x183*x8;
    double mass_result = x207/(x113*x4*x8);
    double dist_result = -x183*x4/x207;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_950_14A_Z_LOG(
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
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_950_14A_Z_LOG(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 1809*x0;
    double x8 = 608*x1;
    double x9 = -x8;
    double x10 = 2795*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 2795*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 608*x0;
    double x16 = -x15;
    double x17 = 1809*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 - 29813.760000000126;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -986*x1 + x16 - x6;
    double x30 = x28 - 368.63999999989755;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 2411187.8399999999;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(986*x0 + x4 + x9);
    double x34 = -18126766.080000103*x0 - 29396367.360000014*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 - 29813.760000000126*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 1216*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 1972*x0 + x37 + x38;
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
    double x61 = 1216*x0;
    double x62 = 3618*x1;
    double x63 = x61 - x62;
    double x64 = 3618*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 + 29813.760000000126*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(2432*x0 - 7236*x1) - x6*(-7236*x0 - 2432*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 84711.269999999975*x74;
    double x76 = 190614.47999999998*x74;
    double tilt_sensitivity = (1078713.3*x49*x74 + 77162.400000000023*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(477517.39999999985*x0 - 1321331.2*x1 + 154324.80000000005*x49 - 2157426.6000000001*x50 - 381228.95999999996*x51 - 169422.53999999995*x52 - 169422.53999999995*x53 + 381228.95999999996*x54 + 4098760.8600000003, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_950_14A_Z_LOG(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 477517.39999999985*x0;
    double x3 = 1321331.2*x1;
    double x4 = 608*x0;
    double x5 = 1809*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 1809*x0;
    double x9 = 608*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 135492.88999999998;
    double x15 = pow(tilt_cyl_ext + 1188, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1133.3542605911005*tilt_cyl_ext;
    double x19 = 288589491.83999991*x0 - 822054696.31999993*x1 + 16.599999999999909*x10*x6 + x11*x6 + 368*x11 + x15*x6 - 368*x15 + pow(x6, 3) - 368*x7 + sqrt((x13 - x15 + x18 + 1160794.7815822272)*(-x11 + x15 + x18 - x2 + x3 - x7 + 1532054.9415822271))*(x17 - 8.2999999999999545) + 168034636.47999999;
    double lever_ang = -atan2(2795*x0, 2795*x1) + atan2(x17 + (x14*(x12 + x15 - 456615.85999999999) + x19*(x16 + 368))/(x14*(3618*x0 + 1216*x1 + 16.599999999999909)), x16 + x19/(955034.7999999997*x0 - 2642662.3999999999*x1 + 2*x11 + 2*x7 + 270985.77999999997)) + 2.7459463459571198;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_950_14A_Z_LOG(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_950_14A_Z_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 7812025*x6;
    double x8 = pow(x0, 2);
    double x9 = 7812025*x8;
    double x10 = 608*x0;
    double x11 = x0*x4;
    double x12 = 766.79999999999995*x11;
    double x13 = x1*x2;
    double x14 = 766.79999999999995*x13;
    double x15 = 1809*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 5590*x16;
    double x18 = 608*x1 + 766.79999999999995*x3 + 766.79999999999995*x5;
    double x19 = 1809*x0 + x18;
    double x20 = x0*x19;
    double x21 = 5590*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 2795*x1;
    double x29 = 1572*BC_len;
    double x30 = 375619968*x0 + 21834609875*pow(x1, 3) - 15624050*x1*x20 + 21834609875*x1*x8 + 609146856*x1 + 473725972.79999995*x11 - 473725972.79999995*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 617796)*(x17 + x21 - x22 - x23 + x27 + x29 + 617796))*(-986*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-2795*x0 + (x25*(x24 + x27 - 617796) + x30*(986*x1 + x10 + x12 - x14))/(x25*(-1972*x0 + 1216*x1 + 1533.5999999999999*x3 + 1533.5999999999999*x5)), -x28 + x30/(-11180*x16 - 11180*x20 + 2*x22 + 2*x23 + 15624050*x6 + 15624050*x8));

    return bucket_ang;
}
