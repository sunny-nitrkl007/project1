/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2022
*
* GENERATED :
*       2022-03-17T18:12:07-05:00 by non_bucket_cpm
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist_962_14A_LOG.h"

void mass_and_dist_962_14A_LOG(double tilt_force, double lift_force, double tilt_cyl_ext, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_962_14A_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = 3074.1999999999998*x0;
    double x2 = cos(arm_ang);
    double x3 = 3074.1999999999998*x2;
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
    double x26 = 993.0*x2;
    double x27 = 1600.0*x17;
    double x28 = 1600.0*x19;
    double x29 = -x27 - x28;
    double x30 = -3816*x0 - x26 + x29;
    double x31 = 3816*x2;
    double x32 = 993.0*x0;
    double x33 = x23 - x24;
    double x34 = x32 + x33;
    double x35 = -x31 + x34;
    double x36 = pow(BC_len, 2);
    double x37 = pow(x0, 2);
    double x38 = 29053359278.487995*x37;
    double x39 = 1908*x2;
    double x40 = 496.5*x0;
    double x41 = -x40;
    double x42 = x15 + x41;
    double x43 = x39 + x42;
    double x44 = 9450705.6399999987*x37;
    double x45 = pow(x2, 2);
    double x46 = 9450705.6399999987*x45;
    double x47 = pow(x43, 2);
    double x48 = 1908*x0;
    double x49 = 496.5*x2;
    double x50 = x18 + x20;
    double x51 = x49 + x50;
    double x52 = x48 + x51;
    double x53 = pow(x52, 2);
    double x54 = x0*x52;
    double x55 = 18901411.279999997*x2;
    double x56 = 6148.3999999999996*x54;
    double x57 = -1166.1999999999998*x0 + x51;
    double x58 = 1705.2*BC_len;
    double x59 = x2*x43;
    double x60 = 6148.3999999999996*x59;
    double x61 = x44 + x46;
    double x62 = x47 + x53;
    double x63 = -x56 - x60 + x61 + x62;
    double x64 = -x36 + x58 + x63 - 726926.76000000001;
    double x65 = x36 - x44 - x46;
    double x66 = -x47 - x53 + x56 + x58 + x60 + x65 + 726926.76000000001;
    double x67 = sqrt(x64*x66);
    double x68 = x57*x67;
    double x69 = 360919136.34000003*x0 + 581541408.0*x10 - 581541408.0*x13 + 29053359278.487995*pow(x2, 3) + x2*x38 + 847741987.51200008*x2 - x3*x36 - x3*x47 + x3*x53 + x36*x43 + pow(x43, 3) + x43*x44 - x43*x46 + x43*x53 - x43*x56 - x54*x55 + x68;
    double x70 = 18901411.279999997*x37;
    double x71 = 18901411.279999997*x45;
    double x72 = 2*x47 + 2*x53 - 12296.799999999999*x54 - 12296.799999999999*x59 + x70 + x71;
    double x73 = x69/pow(x72, 2);
    double x74 = 1.0/x72;
    double x75 = -2400.0*x17 - 2400.0*x19;
    double x76 = x25*x52;
    double x77 = x29*x43;
    double x78 = 6148.3999999999996*x16;
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
    double x89 = 581541408.0*x17 + 581541408.0*x19;
    double x90 = x15*x67 - x16*x55 + x21*x36 + x21*x44 - x21*x46 + x21*x53 - x21*x56 + x3*x76 - x3*x77 + x43*x76 - x43*x78 + x47*x75 + x88*(x64*(x79 + x80 + (1.0/2.0)*x83 + (1.0/2.0)*x87) + x66*((1.0/2.0)*x76 + (1.0/2.0)*x77 - x79 - x80)) + x89;
    double x91 = x73*(12296.799999999999*x16 + 12296.799999999999*x22 + x25*x30 + x29*x35) + x74*x90;
    double x92 = -x3;
    double x93 = x69*x74;
    double x94 = x92 + x93;
    double x95 = x62 + x65 - 726926.76000000001;
    double x96 = 1166.1999999999998*x2;
    double x97 = x85 + x96;
    double x98 = x63*x95 + x69*x97;
    double x99 = -2332.3999999999996*x0 + x26 + x27 + x28;
    double x100 = 1.0/x99;
    double x101 = 1.0/x63;
    double x102 = x100*x101;
    double x103 = x102*x98;
    double x104 = 1.0/(pow(x94, 2) + pow(-x1 + x103, 2));
    double x105 = -x103;
    double x106 = x104*(x1 + x105);
    double x107 = x101*x98/pow(x99, 2);
    double x108 = 6148.3999999999996*x22;
    double x109 = x100*x98/pow(x63, 2);
    double x110 = x76 + x77;
    double x111 = x102*(x110*x63 + x50*x69 + x90*x97 + x95*(-x108 + x110 - x78)) + x107*x33 + x109*(x108 + x78 + x83 + x87);
    double x112 = x104*x94;
    double x113 = x106*x91 + x111*x112;
    double x114 = 1.0/x61;
    double x115 = x25 + x31 - x32;
    double x116 = x115*x52;
    double x117 = x30*x43;
    double x118 = x3*x82;
    double x119 = x3*x52;
    double x120 = x115*x82;
    double x121 = x30*x86;
    double x122 = -29053359278.487995*pow(x0, 3) - 29053359278.487984*x0*x45 + 18901411.279999997*x0*x59 - 847741987.51200008*x0 + x1*x36 - x1*x47 - x1*x53 + x116*x3 + x116*x43 - x117*x3 + 360919136.34000003*x2 + x36*x82 + x44*x82 - x46*x82 + x47*(-5724*x0 - 1489.5*x2 + x75) - x52*x60 + x52*x70 - x52*x71 + x53*x82 - x56*x82 + x67*(x42 - x96) + x88*(x64*(x118 + x119 + (1.0/2.0)*x120 + (1.0/2.0)*x121) + x66*((1.0/2.0)*x116 + (1.0/2.0)*x117 - x118 - x119)) + x89;
    double x123 = 12296.799999999999*x2;
    double x124 = x122*x74 + x73*(x115*x30 + x123*x52 + x123*x82 + x30*x35);
    double x125 = x106*(x1 + x124);
    double x126 = x116 + x117;
    double x127 = 6148.3999999999996*x2;
    double x128 = x127*x82;
    double x129 = x127*x52;
    double x130 = x102*(x122*x97 + x126*x63 + x57*x69 + x95*(x126 - x128 - x129)) + x107*(2332.3999999999996*x2 + x34) + x109*(x120 + x121 + x128 + x129);
    double x131 = x112*(x130 + x92);
    double x132 = -x114*x44 - x114*x46 + x125 + x131 + 1;
    double x133 = 117.2*x10;
    double x134 = 664.70000000000005*x17;
    double x135 = 664.70000000000005*x19;
    double x136 = 117.2*x13;
    double x137 = -x133 + x134 + x135 + x136;
    double x138 = x133 - x134 - x135 - x136 + x48 + x49 + 115;
    double x139 = 664.70000000000005*x10 - 664.70000000000005*x13 + 117.2*x17 + 117.2*x19;
    double x140 = x139 + x39 + x41;
    double x141 = x140 - 325;
    double x142 = pow(x138, 2) + pow(x141, 2);
    double x143 = 1.0/x142;
    double x144 = x137 + x81;
    double x145 = x143*(x144 - 115);
    double x146 = x141*x143;
    double x147 = x137*x145 + x139*x146;
    double x148 = pow(x142, -1.0/2.0);
    double x149 = 167600*x148;
    double x150 = imu_x*x138;
    double x151 = imu_y*x141;
    double x152 = -511*x149*x150 + 511*x149*x151;
    double x153 = 97600*x148;
    double x154 = 513*x150*x153 - 513*x151*x153;
    double x155 = x86 + x93;
    double x156 = x103 + x82;
    double x157 = 1.0/(pow(x155, 2) + pow(x156, 2));
    double x158 = x157*(x105 + x52);
    double x159 = x155*x157;
    double x160 = pow(x15, 2);
    double x161 = 1.0/(x160 + pow(x50, 2));
    double x162 = -x160*x161 - x161*pow(x21, 2) + 1;
    double x163 = -atan2(x156, x155) + atan2(x50, x15);
    double x164 = sin(x163);
    double x165 = cos(x163);
    double x166 = x12*x165 + x164*x9;
    double x167 = x12*x164 - x165*x9;
    double x168 = 34406673.0*imu_x*(-x0*x166 + x167*x2) + 34406673.0*imu_y*(x0*x167 + x166*x2);
    double x169 = imu_x*x0;
    double x170 = imu_y*x2;
    double x171 = -19240*x169 + 19240*x170;
    double x172 = 19240*x113;
    double x173 = imu_y*x93;
    double x174 = imu_x*x103;
    double x175 = -x10 + x13;
    double x176 = x17 + x19;
    double x177 = -x17 - x19;
    double x178 = tilt_force*x148;
    double x179 = 117.2*x178;
    double x180 = 664.70000000000005*x178;
    double x181 = 21249576.0*imu_x*x175 + 25831673.999999993*imu_x*x177 + 25831673.999999993*imu_y*x175 + 21249576.0*imu_y*x176 - x138*x175*x180 + x138*x176*x179 + x141*x175*x179 - x141*x177*x180;
    double x182 = -3074.1999999999998*x113*x171 + x147*x152 + x147*x154 + x168*(x158*(x50 + x91) + x159*(x111 + x84) + x162) + x172*x173 - x172*x174 + x181;
    double x183 = 15.6*x0;
    double x184 = 662*x2;
    double x185 = x183 + x184;
    double x186 = x185 + 405;
    double x187 = 662*x0;
    double x188 = 15.6*x2;
    double x189 = x187 - x188 + 1335;
    double x190 = pow(x186, 2) + pow(x189, 2);
    double x191 = pow(x190, -1.0/2.0);
    double x192 = 204800*x191;
    double x193 = imu_x*x189;
    double x194 = imu_y*x186;
    double x195 = -x187 + x188;
    double x196 = 1.0/x190;
    double x197 = x185*x186*x196 + x195*x196*(x195 - 1335);
    double x198 = x140*x146 + x144*x145;
    double x199 = 136000*x191;
    double x200 = x141*x178;
    double x201 = lift_force*x191;
    double x202 = x186*x201;
    double x203 = x189*x201;
    double x204 = x138*x178;
    double x205 = 19240*x132;
    double x206 = -x113*x8*(-534617179.0*imu_x*x2 - 534617179.0*imu_y*x0 + x152*x198 + x154*x198 + x168*(x158*(x124 + x52) + x159*(x130 + x86) + x162) - 3512102338.3999996*x169 + 3512102338.3999996*x170 + x171*(x114*x38 + 29053359278.487995*x114*x45 - 3074.1999999999998*x125 - 3074.1999999999998*x131) + x173*x205 - x174*x205 + x181 + x183*x203 + x184*x203 - x187*x202 + x188*x202 + 463*x197*(-x192*x193 + x192*x194) + 565*x197*(x193*x199 - x194*x199) - x200*x48 - x200*x49 + x204*x39 - x204*x40) + x132*x182*x8;
    double mass_result = x206/(x113*x4*x8);
    double dist_result = -x182*x4/x206;

    *return_mass = mass_result;
    *return_dist = dist_result;
}

void tilt_sens_to_bucket_ang_962_14A_LOG(
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
    double bucket_ang = bucket_ang_from_tilt_cyl_ext_962_14A_LOG(
        tilt_cyl_ext, arm_ang, BC_len, hook_ang
    );
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = bucket_ang + hook_ang;
    double x3 = sin(x2);
    double x4 = BC_len*x3;
    double x5 = cos(x2);
    double x6 = BC_len*x5;
    double x7 = 1908*x0;
    double x8 = 496.5*x1;
    double x9 = -x8;
    double x10 = 3074.1999999999998*x1 + x6;
    double x11 = pow(x10, 2);
    double x12 = 3074.1999999999998*x0 + x4;
    double x13 = pow(x12, 2);
    double x14 = x11 + x13;
    double x15 = 496.5*x0;
    double x16 = -x15;
    double x17 = 1908*x1;
    double x18 = x16 + x17;
    double x19 = pow(x18, 2);
    double x20 = x7 + x8;
    double x21 = pow(x20, 2);
    double x22 = -x19 - x21;
    double x23 = x14 + x22 - 86926.760000000009;
    double x24 = x10*x18;
    double x25 = 2*x24;
    double x26 = x12*x20;
    double x27 = 2*x26;
    double x28 = x14 + x19 + x21 - x25 - x27;
    double x29 = -1166.1999999999998*x1 + x16 - x6;
    double x30 = x28 - 2766.7600000000093;
    double x31 = -x11 - x13 + x22 + x25 + x27 + 2731086.7599999998;
    double x32 = sqrt(x30*x31);
    double x33 = x32*(1166.1999999999998*x0 + x4 + x9);
    double x34 = -43159136.340000033*x0 - 101373987.51200008*x1 + pow(x10, 3) + x10*x13 - x10*x19 + x10*x21 - x10*x27 - x11*x18 + x13*x18 + pow(x18, 3) + x18*x21 - x18*x27 + x33 - 86926.760000000009*x6;
    double x35 = x23*x28 + x29*x34;
    double x36 = 993.0*x1;
    double x37 = -x36;
    double x38 = 2*x4;
    double x39 = 2332.3999999999996*x0 + x37 + x38;
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
    double x61 = 993.0*x0;
    double x62 = 3816*x1;
    double x63 = x61 - x62;
    double x64 = 3816*x0;
    double x65 = x37 - x64;
    double x66 = x6*x65;
    double x67 = 2*x60;
    double x68 = x10*x38;
    double x69 = -x67 + x68;
    double x70 = x4*x63;
    double x71 = x67 - x68;
    double x72 = x66 - x70 + x71;
    double x73 = x10*x66 + x10*x67 - 3*x11*x4 - x12*x4*x65 - x13*x4 + x18*x67 + x19*x4 + x20*x6*x63 - x21*x4 + x24*x38 + x32*x6 + 86926.760000000009*x4 + x33*((1.0/2.0)*x30*(-x4*(-x61 + x62) + x6*(x36 + x64) + x69) + (1.0/2.0)*x31*x72)/(x30*x31);
    double x74 = x47*x59*(-2*x35*x41*x6/pow(x39, 2) + x42*(x23*x72 + x28*x71 + x29*x73 + x34*x4) + x35*x40*(-x66 + x69 + x70)/pow(x28, 2)) - x56*x58 - x57*x58 + x59*(x20 - x43)*(x34*(4*x10*x4 + x4*(1986.0*x0 - 7632*x1) - x6*(-7632*x0 - 1986.0*x1) - 4*x60)/pow(x45, 2) + x46*x73) + 1;
    double x75 = 114530.5*x74;
    double x76 = 202549.50000000003*x74;
    double tilt_sensitivity = (1326437.4000000001*x49*x74 - 106405.95000000004*x50*x74 + x51*x75 - x52*x76 - x53*x76 - x54*x75)*pow(761565.0*x0 - 1126005.0*x1 - 212811.90000000008*x49 - 2652874.8000000003*x50 - 405099.00000000006*x51 - 229061.0*x52 - 229061.0*x53 + 405099.00000000006*x54 + 4461388.1799999997, -0.5);

    *return_tilt_sens_to_bucket_ang = tilt_sensitivity;
}

double lever_ang_from_tilt_cyl_ext_962_14A_LOG(double tilt_cyl_ext, double arm_ang) {
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = 761565.0*x0;
    double x3 = 1126005.0*x1;
    double x4 = 496.5*x0;
    double x5 = 1908*x1;
    double x6 = -x4 + x5;
    double x7 = pow(x6, 2);
    double x8 = 1908*x0;
    double x9 = 496.5*x1;
    double x10 = x8 + x9;
    double x11 = pow(x10, 2);
    double x12 = x11 + x7;
    double x13 = x12 + x2 - x3;
    double x14 = x13 + 118850;
    double x15 = pow(tilt_cyl_ext + 1300, 2);
    double x16 = x4 - x5;
    double x17 = -x8 - x9;
    double x18 = 1349.9065597292283*tilt_cyl_ext;
    double x19 = 414686098.24500006*x0 - 1008397987.4400002*x1 + 230*x10*x6 + x11*x6 + 325*x11 + x15*x6 - 325*x15 + pow(x6, 3) - 325*x7 + sqrt((x13 - x15 + x18 + 1418166.5976479966)*(-x11 + x15 + x18 - x2 + x3 - x7 + 2091590.457647997))*(x17 - 115) + 186683877.25000003;
    double lever_ang = -atan2(3074.1999999999998*x0, 3074.1999999999998*x1) + atan2(x17 + (x14*(x12 + x15 - 574411.93000000017) + x19*(x16 + 325))/(x14*(3816*x0 + 993.0*x1 + 230)), x16 + x19/(1523130.0*x0 - 2252010.0*x1 + 2*x11 + 2*x7 + 237700)) + 2.9670663585413815;

    return lever_ang;
}

double bucket_ang_from_tilt_cyl_ext_962_14A_LOG(double tilt_cyl_ext, double arm_ang,
                                    double BC_len, double hook_ang) {
    double lever_ang = lever_ang_from_tilt_cyl_ext_962_14A_LOG(tilt_cyl_ext, arm_ang);
    double x0 = sin(arm_ang);
    double x1 = cos(arm_ang);
    double x2 = cos(lever_ang);
    double x3 = x0*x2;
    double x4 = sin(lever_ang);
    double x5 = x1*x4;
    double x6 = pow(x1, 2);
    double x7 = 9450705.6399999987*x6;
    double x8 = pow(x0, 2);
    double x9 = 9450705.6399999987*x8;
    double x10 = 496.5*x0;
    double x11 = x0*x4;
    double x12 = 800.0*x11;
    double x13 = x1*x2;
    double x14 = 800.0*x13;
    double x15 = 1908*x1 - x10 - x12 + x14;
    double x16 = x1*x15;
    double x17 = 6148.3999999999996*x16;
    double x18 = 496.5*x1 + 800.0*x3 + 800.0*x5;
    double x19 = 1908*x0 + x18;
    double x20 = x0*x19;
    double x21 = 6148.3999999999996*x20;
    double x22 = pow(x15, 2);
    double x23 = pow(x19, 2);
    double x24 = x22 + x23;
    double x25 = -x17 - x21 + x24 + x7 + x9;
    double x26 = pow(BC_len, 2);
    double x27 = x26 - x7 - x9;
    double x28 = 3074.1999999999998*x1;
    double x29 = 1705.2*BC_len;
    double x30 = 360919136.34000003*x0 + 29053359278.487995*pow(x1, 3) - 18901411.279999997*x1*x20 + 29053359278.487995*x1*x8 + 847741987.51200008*x1 + 581541408.0*x11 - 581541408.0*x13 + pow(x15, 3) - x15*x21 + x15*x23 + x15*x26 - x15*x7 + x15*x9 - x22*x28 + x23*x28 - x26*x28 + sqrt((x25 - x26 + x29 - 726926.76000000001)*(x17 + x21 - x22 - x23 + x27 + x29 + 726926.76000000001))*(-1166.1999999999998*x0 + x18);
    double bucket_ang = -hook_ang + atan2(-3074.1999999999998*x0 + (x25*(x24 + x27 - 726926.76000000001) + x30*(1166.1999999999998*x1 + x10 + x12 - x14))/(x25*(-2332.3999999999996*x0 + 993.0*x1 + 1600.0*x3 + 1600.0*x5)), -x28 + x30/(-12296.799999999999*x16 - 12296.799999999999*x20 + 2*x22 + 2*x23 + 18901411.279999997*x6 + 18901411.279999997*x8));

    return bucket_ang;
}
