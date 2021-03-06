#ifndef D_FIR_COEFF_H
#define D_FIR_COEFF_H

#include <stdint.h>
typedef int16_t q15_t;

#define FIR_NUM_TAPS (32)
//#define RESAMPLE_NUM_TAPS (128)

//NOTE:  0x800 (2046) = 0x10000 / 2 / 16
#define FIR_BUFFER_SIZE (0x800)
#define FIR_STATE_SIZE  (0x40)
#define FIR_GAINBITS    (5)    /* 0 ~ 6 */


q15_t fir_coeff[FIR_NUM_TAPS] = {
#if 0
            // original coeff
            -204,   -42,   328,   144,  -687,  -430,  1301,  1060, -2162,
           -2298,  3208,  4691, -4150, -9707,  3106, 22273, 22273,  3106,
           -9707, -4150,  4691,  3208, -2298, -2162,  1060,  1301,  -430,
            -687,   144,   328,   -42,  -204
#else
    #if 0
            // bw*1.5
             -414,    384,    -26,   -730,   1457,  -1183,   -755,   3523,
            -4611,   1579,   5072, -10479,   7881,   5033, -19714,  16931,
            16931, -19714,   5033,   7881, -10479,   5072,   1579,  -4611,
             3523,   -755,  -1183,   1457,   -730,    -26,    384,   -414
    #else
        #if 0
             // bw*1.5, flat
             -55,    62,   -26,   -77,   210,  -242,    31,   409,  -801,
             698,   174, -1569,  2597, -1942, -2137, 19028, 19028, -2137,
           -1942,  2597, -1569,   174,   698,  -801,   409,    31,  -242,
             210,   -77,   -26,    62,   -55
        #else
            #if 1
             // bw=156kHz, flat
             -59,    -5,    96,    24,  -208,   -82,   411,   213,  -732,
            -480,  1240,  1027, -2176, -2424,  5158, 14351, 14351,  5158,
           -2424, -2176,  1027,  1240,  -480,  -732,   213,   411,   -82,
            -208,    24,    96,    -5,   -59
            #else
            // fc=120kHz
              10,   -60,   -73,    51,   213,    96,  -341,  -502,   175,
            1061,   640, -1323, -2434,   289,  6566, 11984, 11984,  6566,
             289, -2434, -1323,   640,  1061,   175,  -502,  -341,    96,
             213,    51,   -73,   -60,    10
            #endif
        #endif
    #endif
#endif
};


/*
// two arrays of FIR coefficients
q15_t resample_fir_coeff[2][RESAMPLE_NUM_TAPS] = {
#if 0
		// designed by firwin(15e3)
{   	   0,   -1,   -3,   -5,   -7,   -8,   -9,   -9,   -8,   -6,   -3,
           0,    5,   10,   16,   21,   24,   26,   25,   21,   14,    3,
          -8,  -22,  -36,  -49,  -58,  -63,  -63,  -55,  -40,  -19,    7,
          37,   68,   96,  120,  134,  137,  126,  101,   61,    9,  -51,
        -117, -181, -238, -280, -300, -294, -256, -184,  -77,   61,  229,
         419,  622,  829, 1028, 1209, 1362, 1478, 1551, 1576, 1551, 1478,
        1362, 1209, 1028,  829,  622,  419,  229,   61,  -77, -184, -256,
        -294, -300, -280, -238, -181, -117,  -51,    9,   61,  101,  126,
         137,  134,  120,   96,   68,   37,    7,  -19,  -40,  -55,  -63,
         -63,  -58,  -49,  -36,  -22,   -8,    3,   14,   21,   25,   26,
          24,   21,   16,   10,    5,    0,   -3,   -6,   -8,   -9,   -9,
          -8,   -7,   -5,   -3,   -1,    0,    0},
{		   1,    0,   -2,   -4,   -6,   -7,   -9,   -9,   -9,   -7,   -5,
          -1,    2,    8,   13,   19,   23,   26,   26,   23,   18,    9,
          -2,  -15,  -29,  -43,  -54,  -61,  -64,  -60,  -48,  -30,   -6,
          21,   52,   82,  109,  128,  137,  133,  115,   83,   37,  -20,
         -84, -149, -211, -261, -293, -301, -279, -224, -135,  -11,  142,
         322,  520,  726,  930, 1122, 1290, 1425, 1521, 1569, 1569, 1521,
        1425, 1290, 1122,  930,  726,  520,  322,  142,  -11, -135, -224,
        -279, -301, -293, -261, -211, -149,  -84,  -20,   37,   83,  115,
         133,  137,  128,  109,   82,   52,   21,   -6,  -30,  -48,  -60,
         -64,  -61,  -54,  -43,  -29,  -15,   -2,    9,   18,   23,   26,
          26,   23,   19,   13,    8,    2,   -1,   -5,   -7,   -9,   -9,
          -9,   -7,   -6,   -4,   -2,    0,    1}
#else
          // designed by remez [0,12e3,18.8e3,312e3]
          {  58,   30,   16,    8,    2,   -3,   -9,  -15,  -19,  -23,  -24,
                   -23,  -18,  -11,   -1,   10,   22,   33,   42,   48,   48,   43,
                    32,   16,   -4,  -26,  -49,  -69,  -84,  -90,  -88,  -75,  -52,
                   -20,   17,   59,   99,  133,  157,  166,  158,  131,   85,   24,
                   -48, -127, -203, -268, -314, -332, -316, -261, -164,  -26,  147,
                   350,  573,  805, 1031, 1239, 1416, 1552, 1637, 1665, 1637, 1552,
                  1416, 1239, 1031,  805,  573,  350,  147,  -26, -164, -261, -316,
                  -332, -314, -268, -203, -127,  -48,   24,   85,  131,  158,  166,
                   157,  133,   99,   59,   17,  -20,  -52,  -75,  -88,  -90,  -84,
                   -69,  -49,  -26,   -4,   16,   32,   43,   48,   48,   42,   33,
                    22,   10,   -1,  -11,  -18,  -23,  -24,  -23,  -19,  -15,   -9,
                    -3,    2,    8,   16,   30,   58},
           { -85,   42,   22,   12,    5,    0,   -6,  -12,  -17,  -21,  -24,
                   -24,  -21,  -15,   -6,    4,   16,   28,   38,   45,   49,   46,
                    38,   24,    6,  -15,  -38,  -59,  -77,  -88,  -90,  -83,  -65,
                   -37,   -2,   38,   79,  117,  146,  163,  164,  147,  110,   56,
                   -11,  -87, -166, -238, -294, -327, -329, -293, -217, -100,   56,
                   245,  460,  689,  919, 1138, 1332, 1490, 1601, 1658, 1658, 1601,
                  1490, 1332, 1138,  919,  689,  460,  245,   56, -100, -217, -293,
                  -329, -327, -294, -238, -166,  -87,  -11,   56,  110,  147,  164,
                   163,  146,  117,   79,   38,   -2,  -37,  -65,  -83,  -90,  -88,
                   -77,  -59,  -38,  -15,    6,   24,   38,   46,   49,   45,   38,
                    28,   16,    4,   -6,  -15,  -21,  -24,  -24,  -21,  -17,  -12,
                    -6,    0,    5,   12,   22,   42,  -85}
#endif
};
*/


#endif

