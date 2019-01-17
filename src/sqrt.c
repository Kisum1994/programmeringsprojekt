// =====================================================================
//	  Look-Up Tables
//		sqrt: sqrt(x)
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#include "sqrt.h"
// -----------------------------------------------------------------------
// sqrt: a 512 long LUT of 32bit values in 16.16 format
// sqrt(x)
const signed int sqrt[512]=
{
	0x00010000,0x00008000,0x00005555,0x00004000,0x00003333,0x00002AAB,0x00002492,0x00002000,
	0x00001C72,0x0000199A,0x00001746,0x00001555,0x000013B1,0x00001249,0x00001111,0x00001000,
	0x00000F0F,0x00000E39,0x00000D79,0x00000CCD,0x00000C31,0x00000BA3,0x00000B21,0x00000AAB,
	0x00000A3D,0x000009D9,0x0000097B,0x00000925,0x000008D4,0x00000889,0x00000842,0x00000800,
	0x000007C2,0x00000788,0x00000750,0x0000071C,0x000006EB,0x000006BD,0x00000690,0x00000666,
	0x0000063E,0x00000618,0x000005F4,0x000005D1,0x000005B0,0x00000591,0x00000572,0x00000555,
	0x00000539,0x0000051F,0x00000505,0x000004EC,0x000004D5,0x000004BE,0x000004A8,0x00000492,
	0x0000047E,0x0000046A,0x00000457,0x00000444,0x00000432,0x00000421,0x00000410,0x00000400,

	0x000003F0,0x000003E1,0x000003D2,0x000003C4,0x000003B6,0x000003A8,0x0000039B,0x0000038E,
	0x00000382,0x00000376,0x0000036A,0x0000035E,0x00000353,0x00000348,0x0000033E,0x00000333,
	0x00000329,0x0000031F,0x00000316,0x0000030C,0x00000303,0x000002FA,0x000002F1,0x000002E9,
	0x000002E0,0x000002D8,0x000002D0,0x000002C8,0x000002C1,0x000002B9,0x000002B2,0x000002AB,
	0x000002A4,0x0000029D,0x00000296,0x0000028F,0x00000289,0x00000283,0x0000027C,0x00000276,
	0x00000270,0x0000026A,0x00000264,0x0000025F,0x00000259,0x00000254,0x0000024E,0x00000249,
	0x00000244,0x0000023F,0x0000023A,0x00000235,0x00000230,0x0000022B,0x00000227,0x00000222,
	0x0000021E,0x00000219,0x00000215,0x00000211,0x0000020C,0x00000208,0x00000204,0x00000200,

	0x000001FC,0x000001F8,0x000001F4,0x000001F0,0x000001ED,0x000001E9,0x000001E5,0x000001E2,
	0x000001DE,0x000001DB,0x000001D7,0x000001D4,0x000001D1,0x000001CE,0x000001CA,0x000001C7,
	0x000001C4,0x000001C1,0x000001BE,0x000001BB,0x000001B8,0x000001B5,0x000001B2,0x000001AF,
	0x000001AC,0x000001AA,0x000001A7,0x000001A4,0x000001A1,0x0000019F,0x0000019C,0x0000019A,
	0x00000197,0x00000195,0x00000192,0x00000190,0x0000018D,0x0000018B,0x00000188,0x00000186,
	0x00000184,0x00000182,0x0000017F,0x0000017D,0x0000017B,0x00000179,0x00000176,0x00000174,
	0x00000172,0x00000170,0x0000016E,0x0000016C,0x0000016A,0x00000168,0x00000166,0x00000164,
	0x00000162,0x00000160,0x0000015E,0x0000015D,0x0000015B,0x00000159,0x00000157,0x00000155,

	0x00000154,0x00000152,0x00000150,0x0000014E,0x0000014D,0x0000014B,0x00000149,0x00000148,
	0x00000146,0x00000144,0x00000143,0x00000141,0x00000140,0x0000013E,0x0000013D,0x0000013B,
	0x0000013A,0x00000138,0x00000137,0x00000135,0x00000134,0x00000132,0x00000131,0x0000012F,
	0x0000012E,0x0000012D,0x0000012B,0x0000012A,0x00000129,0x00000127,0x00000126,0x00000125,
	0x00000123,0x00000122,0x00000121,0x0000011F,0x0000011E,0x0000011D,0x0000011C,0x0000011A,
	0x00000119,0x00000118,0x00000117,0x00000116,0x00000115,0x00000113,0x00000112,0x00000111,
	0x00000110,0x0000010F,0x0000010E,0x0000010D,0x0000010B,0x0000010A,0x00000109,0x00000108,
	0x00000107,0x00000106,0x00000105,0x00000104,0x00000103,0x00000102,0x00000101,0x00000100,

	0x000000FF,0x000000FE,0x000000FD,0x000000FC,0x000000FB,0x000000FA,0x000000F9,0x000000F8,
	0x000000F7,0x000000F6,0x000000F5,0x000000F5,0x000000F4,0x000000F3,0x000000F2,0x000000F1,
	0x000000F0,0x000000EF,0x000000EE,0x000000ED,0x000000ED,0x000000EC,0x000000EB,0x000000EA,
	0x000000E9,0x000000E8,0x000000E8,0x000000E7,0x000000E6,0x000000E5,0x000000E4,0x000000E4,
	0x000000E3,0x000000E2,0x000000E1,0x000000E0,0x000000E0,0x000000DF,0x000000DE,0x000000DD,
	0x000000DD,0x000000DC,0x000000DB,0x000000DA,0x000000DA,0x000000D9,0x000000D8,0x000000D8,
	0x000000D7,0x000000D6,0x000000D5,0x000000D5,0x000000D4,0x000000D3,0x000000D3,0x000000D2,
	0x000000D1,0x000000D1,0x000000D0,0x000000CF,0x000000CF,0x000000CE,0x000000CD,0x000000CD,

	0x000000CC,0x000000CC,0x000000CB,0x000000CA,0x000000CA,0x000000C9,0x000000C8,0x000000C8,
	0x000000C7,0x000000C7,0x000000C6,0x000000C5,0x000000C5,0x000000C4,0x000000C4,0x000000C3,
	0x000000C2,0x000000C2,0x000000C1,0x000000C1,0x000000C0,0x000000C0,0x000000BF,0x000000BF,
	0x000000BE,0x000000BD,0x000000BD,0x000000BC,0x000000BC,0x000000BB,0x000000BB,0x000000BA,
	0x000000BA,0x000000B9,0x000000B9,0x000000B8,0x000000B8,0x000000B7,0x000000B7,0x000000B6,
	0x000000B6,0x000000B5,0x000000B5,0x000000B4,0x000000B4,0x000000B3,0x000000B3,0x000000B2,
	0x000000B2,0x000000B1,0x000000B1,0x000000B0,0x000000B0,0x000000AF,0x000000AF,0x000000AE,
	0x000000AE,0x000000AD,0x000000AD,0x000000AC,0x000000AC,0x000000AC,0x000000AB,0x000000AB,

	0x000000AA,0x000000AA,0x000000A9,0x000000A9,0x000000A8,0x000000A8,0x000000A8,0x000000A7,
	0x000000A7,0x000000A6,0x000000A6,0x000000A5,0x000000A5,0x000000A5,0x000000A4,0x000000A4,
	0x000000A3,0x000000A3,0x000000A3,0x000000A2,0x000000A2,0x000000A1,0x000000A1,0x000000A1,
	0x000000A0,0x000000A0,0x0000009F,0x0000009F,0x0000009F,0x0000009E,0x0000009E,0x0000009E,
	0x0000009D,0x0000009D,0x0000009C,0x0000009C,0x0000009C,0x0000009B,0x0000009B,0x0000009B,
	0x0000009A,0x0000009A,0x00000099,0x00000099,0x00000099,0x00000098,0x00000098,0x00000098,
	0x00000097,0x00000097,0x00000097,0x00000096,0x00000096,0x00000096,0x00000095,0x00000095,
	0x00000095,0x00000094,0x00000094,0x00000094,0x00000093,0x00000093,0x00000093,0x00000092,

	0x00000092,0x00000092,0x00000091,0x00000091,0x00000091,0x00000090,0x00000090,0x00000090,
	0x0000008F,0x0000008F,0x0000008F,0x0000008E,0x0000008E,0x0000008E,0x0000008E,0x0000008D,
	0x0000008D,0x0000008D,0x0000008C,0x0000008C,0x0000008C,0x0000008B,0x0000008B,0x0000008B,
	0x0000008B,0x0000008A,0x0000008A,0x0000008A,0x00000089,0x00000089,0x00000089,0x00000089,
	0x00000088,0x00000088,0x00000088,0x00000087,0x00000087,0x00000087,0x00000087,0x00000086,
	0x00000086,0x00000086,0x00000085,0x00000085,0x00000085,0x00000085,0x00000084,0x00000084,
	0x00000084,0x00000084,0x00000083,0x00000083,0x00000083,0x00000083,0x00000082,0x00000082,
	0x00000082,0x00000082,0x00000081,0x00000081,0x00000081,0x00000081,0x00000080,0x00000080,
};

