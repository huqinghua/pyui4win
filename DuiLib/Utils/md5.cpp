 // Free for all implementation of the MD5 hash algorithm

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#include "StdAfx.h"
#include "MD5.h"

/* Padding */
static BYTE MD5_PADDING[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* MD5_F, MD5_G and MD5_H are basic MD5 functions: selection, majority, parity */
#define MD5_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define MD5_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define MD5_I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#ifndef ROTATE_LEFT
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#endif

/* MD5_FF, MD5_GG, MD5_HH, and MD5_II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define MD5_FF(a, b, c, d, x, s, ac) {(a) += MD5_F ((b), (c), (d)) + (x) + (DWORD)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define MD5_GG(a, b, c, d, x, s, ac) {(a) += MD5_G ((b), (c), (d)) + (x) + (DWORD)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define MD5_HH(a, b, c, d, x, s, ac) {(a) += MD5_H ((b), (c), (d)) + (x) + (DWORD)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define MD5_II(a, b, c, d, x, s, ac) {(a) += MD5_I ((b), (c), (d)) + (x) + (DWORD)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }

/* Constants for transformation */
#define MD5_S11 7  /* Round 1 */
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21 5  /* Round 2 */
#define MD5_S22 9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31 4  /* Round 3 */
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41 6  /* Round 4 */
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

/* Basic MD5 step. MD5_Transform buf based on in */
static void MD5_Transform(DWORD *buf, DWORD *in)
{
	DWORD a = buf[0], b = buf[1], c = buf[2], d = buf[3];

	/* Round 1 */
	MD5_FF ( a, b, c, d, in[ 0], MD5_S11, (DWORD) 3614090360u); /* 1 */
	MD5_FF ( d, a, b, c, in[ 1], MD5_S12, (DWORD) 3905402710u); /* 2 */
	MD5_FF ( c, d, a, b, in[ 2], MD5_S13, (DWORD)  606105819u); /* 3 */
	MD5_FF ( b, c, d, a, in[ 3], MD5_S14, (DWORD) 3250441966u); /* 4 */
	MD5_FF ( a, b, c, d, in[ 4], MD5_S11, (DWORD) 4118548399u); /* 5 */
	MD5_FF ( d, a, b, c, in[ 5], MD5_S12, (DWORD) 1200080426u); /* 6 */
	MD5_FF ( c, d, a, b, in[ 6], MD5_S13, (DWORD) 2821735955u); /* 7 */
	MD5_FF ( b, c, d, a, in[ 7], MD5_S14, (DWORD) 4249261313u); /* 8 */
	MD5_FF ( a, b, c, d, in[ 8], MD5_S11, (DWORD) 1770035416u); /* 9 */
	MD5_FF ( d, a, b, c, in[ 9], MD5_S12, (DWORD) 2336552879u); /* 10 */
	MD5_FF ( c, d, a, b, in[10], MD5_S13, (DWORD) 4294925233u); /* 11 */
	MD5_FF ( b, c, d, a, in[11], MD5_S14, (DWORD) 2304563134u); /* 12 */
	MD5_FF ( a, b, c, d, in[12], MD5_S11, (DWORD) 1804603682u); /* 13 */
	MD5_FF ( d, a, b, c, in[13], MD5_S12, (DWORD) 4254626195u); /* 14 */
	MD5_FF ( c, d, a, b, in[14], MD5_S13, (DWORD) 2792965006u); /* 15 */
	MD5_FF ( b, c, d, a, in[15], MD5_S14, (DWORD) 1236535329u); /* 16 */

	/* Round 2 */
	MD5_GG ( a, b, c, d, in[ 1], MD5_S21, (DWORD) 4129170786u); /* 17 */
	MD5_GG ( d, a, b, c, in[ 6], MD5_S22, (DWORD) 3225465664u); /* 18 */
	MD5_GG ( c, d, a, b, in[11], MD5_S23, (DWORD)  643717713u); /* 19 */
	MD5_GG ( b, c, d, a, in[ 0], MD5_S24, (DWORD) 3921069994u); /* 20 */
	MD5_GG ( a, b, c, d, in[ 5], MD5_S21, (DWORD) 3593408605u); /* 21 */
	MD5_GG ( d, a, b, c, in[10], MD5_S22, (DWORD)   38016083u); /* 22 */
	MD5_GG ( c, d, a, b, in[15], MD5_S23, (DWORD) 3634488961u); /* 23 */
	MD5_GG ( b, c, d, a, in[ 4], MD5_S24, (DWORD) 3889429448u); /* 24 */
	MD5_GG ( a, b, c, d, in[ 9], MD5_S21, (DWORD)  568446438u); /* 25 */
	MD5_GG ( d, a, b, c, in[14], MD5_S22, (DWORD) 3275163606u); /* 26 */
	MD5_GG ( c, d, a, b, in[ 3], MD5_S23, (DWORD) 4107603335u); /* 27 */
	MD5_GG ( b, c, d, a, in[ 8], MD5_S24, (DWORD) 1163531501u); /* 28 */
	MD5_GG ( a, b, c, d, in[13], MD5_S21, (DWORD) 2850285829u); /* 29 */
	MD5_GG ( d, a, b, c, in[ 2], MD5_S22, (DWORD) 4243563512u); /* 30 */
	MD5_GG ( c, d, a, b, in[ 7], MD5_S23, (DWORD) 1735328473u); /* 31 */
	MD5_GG ( b, c, d, a, in[12], MD5_S24, (DWORD) 2368359562u); /* 32 */

	/* Round 3 */
	MD5_HH ( a, b, c, d, in[ 5], MD5_S31, (DWORD) 4294588738u); /* 33 */
	MD5_HH ( d, a, b, c, in[ 8], MD5_S32, (DWORD) 2272392833u); /* 34 */
	MD5_HH ( c, d, a, b, in[11], MD5_S33, (DWORD) 1839030562u); /* 35 */
	MD5_HH ( b, c, d, a, in[14], MD5_S34, (DWORD) 4259657740u); /* 36 */
	MD5_HH ( a, b, c, d, in[ 1], MD5_S31, (DWORD) 2763975236u); /* 37 */
	MD5_HH ( d, a, b, c, in[ 4], MD5_S32, (DWORD) 1272893353u); /* 38 */
	MD5_HH ( c, d, a, b, in[ 7], MD5_S33, (DWORD) 4139469664u); /* 39 */
	MD5_HH ( b, c, d, a, in[10], MD5_S34, (DWORD) 3200236656u); /* 40 */
	MD5_HH ( a, b, c, d, in[13], MD5_S31, (DWORD)  681279174u); /* 41 */
	MD5_HH ( d, a, b, c, in[ 0], MD5_S32, (DWORD) 3936430074u); /* 42 */
	MD5_HH ( c, d, a, b, in[ 3], MD5_S33, (DWORD) 3572445317u); /* 43 */
	MD5_HH ( b, c, d, a, in[ 6], MD5_S34, (DWORD)   76029189u); /* 44 */
	MD5_HH ( a, b, c, d, in[ 9], MD5_S31, (DWORD) 3654602809u); /* 45 */
	MD5_HH ( d, a, b, c, in[12], MD5_S32, (DWORD) 3873151461u); /* 46 */
	MD5_HH ( c, d, a, b, in[15], MD5_S33, (DWORD)  530742520u); /* 47 */
	MD5_HH ( b, c, d, a, in[ 2], MD5_S34, (DWORD) 3299628645u); /* 48 */

	/* Round 4 */
	MD5_II ( a, b, c, d, in[ 0], MD5_S41, (DWORD) 4096336452u); /* 49 */
	MD5_II ( d, a, b, c, in[ 7], MD5_S42, (DWORD) 1126891415u); /* 50 */
	MD5_II ( c, d, a, b, in[14], MD5_S43, (DWORD) 2878612391u); /* 51 */
	MD5_II ( b, c, d, a, in[ 5], MD5_S44, (DWORD) 4237533241u); /* 52 */
	MD5_II ( a, b, c, d, in[12], MD5_S41, (DWORD) 1700485571u); /* 53 */
	MD5_II ( d, a, b, c, in[ 3], MD5_S42, (DWORD) 2399980690u); /* 54 */
	MD5_II ( c, d, a, b, in[10], MD5_S43, (DWORD) 4293915773u); /* 55 */
	MD5_II ( b, c, d, a, in[ 1], MD5_S44, (DWORD) 2240044497u); /* 56 */
	MD5_II ( a, b, c, d, in[ 8], MD5_S41, (DWORD) 1873313359u); /* 57 */
	MD5_II ( d, a, b, c, in[15], MD5_S42, (DWORD) 4264355552u); /* 58 */
	MD5_II ( c, d, a, b, in[ 6], MD5_S43, (DWORD) 2734768916u); /* 59 */
	MD5_II ( b, c, d, a, in[13], MD5_S44, (DWORD) 1309151649u); /* 60 */
	MD5_II ( a, b, c, d, in[ 4], MD5_S41, (DWORD) 4149444226u); /* 61 */
	MD5_II ( d, a, b, c, in[11], MD5_S42, (DWORD) 3174756917u); /* 62 */
	MD5_II ( c, d, a, b, in[ 2], MD5_S43, (DWORD)  718787259u); /* 63 */
	MD5_II ( b, c, d, a, in[ 9], MD5_S44, (DWORD) 3951481745u); /* 64 */

	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}

// Set pseudoRandomNumber to zero for RFC MD5 implementation
void MD5Init (MD5_CTX *mdContext, DWORD pseudoRandomNumber)
{
	mdContext->i[0] = mdContext->i[1] = (DWORD)0;

	/* Load magic initialization constants */
	mdContext->buf[0] = (DWORD)0x67452301 + (pseudoRandomNumber * 11);
	mdContext->buf[1] = (DWORD)0xefcdab89 + (pseudoRandomNumber * 71);
	mdContext->buf[2] = (DWORD)0x98badcfe + (pseudoRandomNumber * 37);
	mdContext->buf[3] = (DWORD)0x10325476 + (pseudoRandomNumber * 97);
}

void MD5Update(MD5_CTX *mdContext, BYTE *inBuf, DWORD inLen)
{
	DWORD in[16];
	int mdi = 0;
	DWORD i = 0, ii = 0;

	/* Compute number of bytes mod 64 */
	mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((mdContext->i[0] + ((DWORD)inLen << 3)) < mdContext->i[0])
		mdContext->i[1]++;
	mdContext->i[0] += ((DWORD)inLen << 3);
	mdContext->i[1] += ((DWORD)inLen >> 29);

	while (inLen--)
	{
		/* Add new character to buffer, increment mdi */
		mdContext->in[mdi++] = *inBuf++;

		/* Transform if necessary */
		if (mdi == 0x40)
		{
			for (i = 0, ii = 0; i < 16; i++, ii += 4)
				in[i] = (((DWORD)mdContext->in[ii+3]) << 24) |
					(((DWORD)mdContext->in[ii+2]) << 16) |
					(((DWORD)mdContext->in[ii+1]) << 8) |
					((DWORD)mdContext->in[ii]);

			MD5_Transform(mdContext->buf, in);
			mdi = 0;
		}
	}
}

void MD5Final(MD5_CTX *mdContext)
{
	DWORD in[16];
	int mdi = 0;
	DWORD i = 0, ii = 0, padLen = 0;

	/* Save number of bits */
	in[14] = mdContext->i[0];
	in[15] = mdContext->i[1];

	/* Compute number of bytes mod 64 */
	mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

	/* Pad out to 56 mod 64 */
	padLen = (mdi < 56) ? (56 - mdi) : (120 - mdi);
	MD5Update (mdContext, MD5_PADDING, padLen);

	/* Append length in bits and transform */
	for (i = 0, ii = 0; i < 14; i++, ii += 4)
		in[i] = (((DWORD)mdContext->in[ii+3]) << 24) |
			(((DWORD)mdContext->in[ii+2]) << 16) |
			(((DWORD)mdContext->in[ii+1]) <<  8) |
			((DWORD)mdContext->in[ii]);
	MD5_Transform (mdContext->buf, in);

	/* Store buffer in digest */
	for (i = 0, ii = 0; i < 4; i++, ii += 4)
	{
		mdContext->digest[ii]   = (BYTE)( mdContext->buf[i]        & 0xFF);
		mdContext->digest[ii+1] = (BYTE)((mdContext->buf[i] >>  8) & 0xFF);
		mdContext->digest[ii+2] = (BYTE)((mdContext->buf[i] >> 16) & 0xFF);
		mdContext->digest[ii+3] = (BYTE)((mdContext->buf[i] >> 24) & 0xFF);
	}
}

void MD5Hash(char* str, BYTE hash[16])
{
	MD5_CTX md5;
	
	MD5Init(&md5, 0);
	MD5Update(&md5, (BYTE*)str, strlen(str));
	MD5Final(&md5);
	memcpy(hash, md5.digest, 16);
}