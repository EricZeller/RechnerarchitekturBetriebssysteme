#ifndef KEYS_H
#define KEYS_H

/* Notendauern in 1/96 */
#define DUR_16th_tri    4   /* 16tel-Triole */
#define DUR_16th        6	/* 16tel-Note */
#define DUR_8th_tri     8   /* 8-tel-Note mit Punkt */
#define DUR_16th_dot    9   /* 16tel-Note mit Punkt */
#define DUR_8th        12   /* 8-tel-Note */
#define DUR_4th_tri    16   /* 4-tel-Triole */
#define DUR_8th_dot    18   /* 8-tel-Note mit Punkt*/
#define DUR_4th        24   /* 4-tel-Note */
#define DUR_half_tri   32   /* Halbetriole */
#define DUR_4th_dot    36   /* 4-tel-Note mit Punkt */
#define DUR_half       48   /* halbe Note */
#define DUR_half_dot   72   /* halbe Note mit Punkt */
#define DUR_whole      96   /* ganze Note */
#define DUR_whole_dot 144   /* ganze Note mit Punkt */

/* Notennummern */

/* Pausen-Marker */
#define PAUSE 	0

/* Basis-Nummern */
#define KEY_C    0
#define KEY_Cis  1
#define KEY_D    2
#define KEY_Dis  3
#define KEY_E    4
#define KEY_F    5
#define KEY_Fis  6
#define KEY_G    7
#define KEY_Gis  8
#define KEY_A    9
#define KEY_Ais 10
#define KEY_B   11


/* Hilfsmakro für Oktaven-Umrechnung */
#define KEY(base, octave)  ((base)+12*(octave)+12)

/* Oktave 0 */
#define KEY_A0      KEY(KEY_A,   0)
#define KEY_Ais0    KEY(KEY_Ais, 0)
#define KEY_Bb0     KEY_Ais0
#define KEY_B0      KEY(KEY_B,   0)

/* Oktave 1 */
#define KEY_C1      KEY(KEY_C,   1)
#define KEY_Cis1    KEY(KEY_Cis, 1)
#define KEY_Db1     KEY_Cis1
#define KEY_D1      KEY(KEY_D,   1)
#define KEY_Dis1    KEY(KEY_Dis, 1)
#define KEY_Eb1     KEY_Dis1
#define KEY_E1      KEY(KEY_E,   1)
#define KEY_F1      KEY(KEY_F,   1)
#define KEY_Fis1    KEY(KEY_Fis, 1)
#define KEY_Gb1     KEY_Fis1
#define KEY_G1      KEY(KEY_G,   1)
#define KEY_Gis1    KEY(KEY_Gis, 1)
#define KEY_Ab1     KEY_Gis1
#define KEY_A1      KEY(KEY_A,   1)
#define KEY_Ais1    KEY(KEY_Ais, 1)
#define KEY_Bb1     KEY_Ais1
#define KEY_B1      KEY(KEY_B,   1)

/* Oktave 2 */
#define KEY_C2      KEY(KEY_C,   2)
#define KEY_Cis2    KEY(KEY_Cis, 2)
#define KEY_Db2     KEY_Cis2
#define KEY_D2      KEY(KEY_D,   2)
#define KEY_Dis2    KEY(KEY_Dis, 2)
#define KEY_Eb2     KEY_Dis2
#define KEY_E2      KEY(KEY_E,   2)
#define KEY_F2      KEY(KEY_F,   2)
#define KEY_Fis2    KEY(KEY_Fis, 2)
#define KEY_Gb2     KEY_Fis2
#define KEY_G2      KEY(KEY_G,   2)
#define KEY_Gis2    KEY(KEY_Gis, 2)
#define KEY_Ab2     KEY_Gis2
#define KEY_A2      KEY(KEY_A,   2)
#define KEY_Ais2    KEY(KEY_Ais, 2)
#define KEY_Bb2     KEY_Ais2
#define KEY_B2      KEY(KEY_B,   2)

/* Oktave 3 */
#define KEY_C3      KEY(KEY_C,   3)
#define KEY_Cis3    KEY(KEY_Cis, 3)
#define KEY_Db3     KEY_Cis3
#define KEY_D3      KEY(KEY_D,   3)
#define KEY_Dis3    KEY(KEY_Dis, 3)
#define KEY_Eb3     KEY_Dis3
#define KEY_E3      KEY(KEY_E,   3)
#define KEY_F3      KEY(KEY_F,   3)
#define KEY_Fis3    KEY(KEY_Fis, 3)
#define KEY_Gb3     KEY_Fis3
#define KEY_G3      KEY(KEY_G,   3)
#define KEY_Gis3    KEY(KEY_Gis, 3)
#define KEY_Ab3     KEY_Gis3
#define KEY_A3      KEY(KEY_A,   3)
#define KEY_Ais3    KEY(KEY_Ais, 3)
#define KEY_Bb3     KEY_Ais3
#define KEY_B3      KEY(KEY_B,   3)

/* Oktave 4 */
#define KEY_C4      KEY(KEY_C,   4)
#define KEY_Cis4    KEY(KEY_Cis, 4)
#define KEY_Db4     KEY_Cis4
#define KEY_D4      KEY(KEY_D,   4)
#define KEY_Dis4    KEY(KEY_Dis, 4)
#define KEY_Eb4     KEY_Dis4
#define KEY_E4      KEY(KEY_E,   4)
#define KEY_F4      KEY(KEY_F,   4)
#define KEY_Fis4    KEY(KEY_Fis, 4)
#define KEY_Gb4     KEY_Fis4
#define KEY_G4      KEY(KEY_G,   4)
#define KEY_Gis4    KEY(KEY_Gis, 4)
#define KEY_Ab4     KEY_Gis4
#define KEY_A4      KEY(KEY_A,   4)
#define KEY_Ais4    KEY(KEY_Ais, 4)
#define KEY_Bb4     KEY_Ais4
#define KEY_B4      KEY(KEY_B,   4)

/* Oktave 5 */
#define KEY_C5      KEY(KEY_C,   5)
#define KEY_Cis5    KEY(KEY_Cis, 5)
#define KEY_Db5     KEY_Cis5
#define KEY_D5      KEY(KEY_D,   5)
#define KEY_Dis5    KEY(KEY_Dis, 5)
#define KEY_Eb5     KEY_Dis5
#define KEY_E5      KEY(KEY_E,   5)
#define KEY_F5      KEY(KEY_F,   5)
#define KEY_Fis5    KEY(KEY_Fis, 5)
#define KEY_Gb5     KEY_Fis5
#define KEY_G5      KEY(KEY_G,   5)
#define KEY_Gis5    KEY(KEY_Gis, 5)
#define KEY_Ab5     KEY_Gis5
#define KEY_A5      KEY(KEY_A,   5)
#define KEY_Ais5    KEY(KEY_Ais, 5)
#define KEY_Bb5     KEY_Ais5
#define KEY_B5      KEY(KEY_B,   5)

/* Oktave 6 */
#define KEY_C6      KEY(KEY_C,   6)
#define KEY_Cis6    KEY(KEY_Cis, 6)
#define KEY_Db6     KEY_Cis6
#define KEY_D6      KEY(KEY_D,   6)
#define KEY_Dis6    KEY(KEY_Dis, 6)
#define KEY_Eb6     KEY_Dis6
#define KEY_E6      KEY(KEY_E,   6)
#define KEY_F6      KEY(KEY_F,   6)
#define KEY_Fis6    KEY(KEY_Fis, 6)
#define KEY_Gb6     KEY_Fis6
#define KEY_G6      KEY(KEY_G,   6)
#define KEY_Gis6    KEY(KEY_Gis, 6)
#define KEY_Ab6     KEY_Gis6
#define KEY_A6      KEY(KEY_A,   6)
#define KEY_Ais6    KEY(KEY_Ais, 6)
#define KEY_Bb6     KEY_Ais6
#define KEY_B6      KEY(KEY_B,   6)

/* Oktave 7 */
#define KEY_C7      KEY(KEY_C,   7)
#define KEY_Cis7    KEY(KEY_Cis, 7)
#define KEY_Db7     KEY_Cis7
#define KEY_D7      KEY(KEY_D,   7)
#define KEY_Dis7    KEY(KEY_Dis, 7)
#define KEY_Eb7     KEY_Dis7
#define KEY_E7      KEY(KEY_E,   7)
#define KEY_F7      KEY(KEY_F,   7)
#define KEY_Fis7    KEY(KEY_Fis, 7)
#define KEY_Gb7     KEY_Fis7
#define KEY_G7      KEY(KEY_G,   7)
#define KEY_Gis7    KEY(KEY_Gis, 7)
#define KEY_Ab7     KEY_Gis7
#define KEY_A7      KEY(KEY_A,   7)
#define KEY_Ais7    KEY(KEY_Ais, 7)
#define KEY_Bb7     KEY_Ais7
#define KEY_B7      KEY(KEY_B,   7)

/* Oktave 8 */
#define KEY_C8      KEY(KEY_C,   8)


#endif /* KEYS_H */
