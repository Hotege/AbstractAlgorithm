#include <stdio.h>
#include <memory.h>
#include "AbstractAlgorithm.h"

#define ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define F(x, y, z) (((x) & (y)) | ((~(x)) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~(z))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~(z))))
#define FF(a, b, c, d, M, s, ti) (a = (b) + ROTATE(a + F(b, c, d) + M + ti, s))
#define GG(a, b, c, d, M, s, ti) (a = (b) + ROTATE(a + G(b, c, d) + M + ti, s))
#define HH(a, b, c, d, M, s, ti) (a = (b) + ROTATE(a + H(b, c, d) + M + ti, s))
#define II(a, b, c, d, M, s, ti) (a = (b) + ROTATE(a + I(b, c, d) + M + ti, s))
#define FT(b, c, d, t) (((t) >= 0 && (t) < 20) ? (((b) & (c)) | ((~(b)) & (d))) : (((t) >= 40 && (t) < 60) ? (((b) & (c)) | ((b) & (d)) | ((c) & (d))) : ((b) ^ (c) ^ (d))))

AbstractAlgorithm::AbstractAlgorithm()
{

}

AbstractAlgorithm::~AbstractAlgorithm()
{
	
}

unsigned int AbstractAlgorithm::getCRC32Value(const void* buffer, const int size)
{
	unsigned int ret = 0xFFFFFFFF;
	initCRC32Table();
	for (int i = 0; i < size; i++)
		ret = m_CRC32[(ret & 0xFF) ^ ((unsigned char*)buffer)[i]] ^ (ret >> 8);
	ret = ~ret;
	return ret;
}

unsigned int AbstractAlgorithm::getCRC32Value(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* buffer = new unsigned char[size];
	fread(buffer, sizeof(unsigned char), size, file);
	fclose(file);
	unsigned int ret = getCRC32Value(buffer, size);
	delete[] buffer;
	buffer = NULL;
	return ret;
}

void AbstractAlgorithm::getMD5Value(unsigned int result[4], const void* buffer, const int size)
{
	// alloc buffer
	int rest = (size << 3) & 511;
	int new_size = size;
	if (rest <= 448)
		new_size = ((size >> 6) + 1) << 6;
	else
		new_size = ((size >> 6) + 2) << 6;
	long long bits_size = size << 3;
	unsigned char* new_buffer = new unsigned char[new_size];
	memcpy(new_buffer, buffer, sizeof(unsigned char) * size);
	new_buffer[size] = 0x80;
	memcpy(new_buffer + (new_size - 8), &bits_size, sizeof(long long));

	unsigned int A = 0x67452301, B = 0xEFCDAB89, C = 0x98BADCFE, D = 0x10325476;
	unsigned int a = A, b = B, c = C, d = D;

	for (int i = 0; i < (new_size >> 6); i++)
	{
		unsigned int M[16];
		memcpy(M, &new_buffer[i], sizeof(unsigned int) << 4);

		a = A; b = B; c = C; d = D;
		//传说中的对M[j]的第一轮循环
		FF(a,b,c,d,M[0],7,0xd76aa478);
		FF(d,a,b,c,M[1],12,0xe8c7b756);
		FF(c,d,a,b,M[2],17,0x242070db);
		FF(b,c,d,a,M[3],22,0xc1bdceee);
		FF(a,b,c,d,M[4],7,0xf57c0faf);
		FF(d,a,b,c,M[5],12,0x4787c62a);
		FF(c,d,a,b,M[6],17,0xa8304613);
		FF(b,c,d,a,M[7],22,0xfd469501);
		FF(a,b,c,d,M[8],7,0x698098d8);
		FF(d,a,b,c,M[9],12,0x8b44f7af);
		FF(c,d,a,b,M[10],17,0xffff5bb1);
		FF(b,c,d,a,M[11],22,0x895cd7be);
		FF(a,b,c,d,M[12],7,0x6b901122);
		FF(d,a,b,c,M[13],12,0xfd987193);
		FF(c,d,a,b,M[14],17,0xa679438e);
		FF(b,c,d,a,M[15],22,0x49b40821);

		//传说中对M[j]的第二轮循环
		GG(a,b,c,d,M[1],5,0xf61e2562);
		GG(d,a,b,c,M[6],9,0xc040b340);
		GG(c,d,a,b,M[11],14,0x265e5a51);
		GG(b,c,d,a,M[0],20,0xe9b6c7aa);
		GG(a,b,c,d,M[5],5,0xd62f105d);
		GG(d,a,b,c,M[10],9,0x02441453);
		GG(c,d,a,b,M[15],14,0xd8a1e681);
		GG(b,c,d,a,M[4],20,0xe7d3fbc8);
		GG(a,b,c,d,M[9],5,0x21e1cde6);
		GG(d,a,b,c,M[14],9,0xc33707d6);
		GG(c,d,a,b,M[3],14,0xf4d50d87);
		GG(b,c,d,a,M[8],20,0x455a14ed);
		GG(a,b,c,d,M[13],5,0xa9e3e905);
		GG(d,a,b,c,M[2],9,0xfcefa3f8);
		GG(c,d,a,b,M[7],14,0x676f02d9);
		GG(b,c,d,a,M[12],20,0x8d2a4c8a);

		//传说中对M[j]的第三轮循环
		HH(a,b,c,d,M[5],4,0xfffa3942);
		HH(d,a,b,c,M[8],11,0x8771f681);
		HH(c,d,a,b,M[11],16,0x6d9d6122);
		HH(b,c,d,a,M[14],23,0xfde5380c);
		HH(a,b,c,d,M[1],4,0xa4beea44);
		HH(d,a,b,c,M[4],11,0x4bdecfa9);
		HH(c,d,a,b,M[7],16,0xf6bb4b60);
		HH(b,c,d,a,M[10],23,0xbebfbc70);
		HH(a,b,c,d,M[13],4,0x289b7ec6);
		HH(d,a,b,c,M[0],11,0xeaa127fa);
		HH(c,d,a,b,M[3],16,0xd4ef3085);
		HH(b,c,d,a,M[6],23,0x04881d05);
		HH(a,b,c,d,M[9],4,0xd9d4d039);
		HH(d,a,b,c,M[12],11,0xe6db99e5);
		HH(c,d,a,b,M[15],16,0x1fa27cf8);
		HH(b,c,d,a,M[2],23,0xc4ac5665);

		//传说中对M[j]的第四轮循环
		II(a,b,c,d,M[0],6,0xf4292244);
		II(d,a,b,c,M[7],10,0x432aff97);
		II(c,d,a,b,M[14],15,0xab9423a7);
		II(b,c,d,a,M[5],21,0xfc93a039);
		II(a,b,c,d,M[12],6,0x655b59c3);
		II(d,a,b,c,M[3],10,0x8f0ccc92);
		II(c,d,a,b,M[10],15,0xffeff47d);
		II(b,c,d,a,M[1],21,0x85845dd1);
		II(a,b,c,d,M[8],6,0x6fa87e4f);
		II(d,a,b,c,M[15],10,0xfe2ce6e0);
		II(c,d,a,b,M[6],15,0xa3014314);
		II(b,c,d,a,M[13],21,0x4e0811a1);
		II(a,b,c,d,M[4],6,0xf7537e82);
		II(d,a,b,c,M[11],10,0xbd3af235);
		II(c,d,a,b,M[2],15,0x2ad7d2bb);
		II(b,c,d,a,M[9],21,0xeb86d391);

		A += a;
		B += b;
		C += c;
		D += d;
	}

	result[0] = A; result[1] = B; result[2] = C; result[3] = D;

	delete[] new_buffer;
	new_buffer = NULL;
}

void AbstractAlgorithm::getMD5Value(unsigned int result[4], const char* filename)
{
	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* buffer = new unsigned char[size];
	fread(buffer, sizeof(unsigned char), size, file);
	fclose(file);
	getMD5Value(result, buffer, size);
	delete[] buffer;
	buffer = NULL;
}

void AbstractAlgorithm::getSHA1Value(unsigned int result[5], const void* buffer, const int size)
{
	// alloc buffer
	int rest = (size << 3) & 511;
	int new_size = size;
	if (rest <= 448)
		new_size = ((size >> 6) + 1) << 6;
	else
		new_size = ((size >> 6) + 2) << 6;
	long long bits_size = size << 3;
	unsigned char* new_buffer = new unsigned char[new_size];
	memcpy(new_buffer, buffer, sizeof(unsigned char) * size);
	new_buffer[size] = 0x80;

	for (int i = 0; i < new_size; i+=4)
	{
		int t = new_buffer[i]; new_buffer[i] = new_buffer[i + 3]; new_buffer[i + 3] = t;
		t = new_buffer[i + 1]; new_buffer[i + 1] = new_buffer[i + 2]; new_buffer[i + 2] = t;
	}
	
	unsigned int bits_int[2] = { 0 };
	memcpy(bits_int, &bits_size, sizeof(long long));
	memcpy(new_buffer + new_size - 4, &bits_int[0], sizeof(unsigned int));
	memcpy(new_buffer + new_size - 8, &bits_int[1], sizeof(unsigned int));

	unsigned int* buffer_int = (unsigned int*)new_buffer;
	unsigned int W[80] = { 0 };
	unsigned int a = 0x67452301, b = 0xEFCDAB89, c = 0x98BADCFE, d = 0x10325476, e = 0xC3D2E1F0;
	const unsigned int K[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };

	for (int i = 0; i < new_size >> 2; i+=16)
	{
		unsigned int A = a, B = b, C = c, D = d, E = e;
		for (int j = 0; j < 80; j++)
		{
			if (j < 16)
				W[j] = buffer_int[i + j];
			else
				W[j] = ROTATE(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
			unsigned int t = ROTATE(a, 5) + FT(b, c, d, j) + e + W[j] + K[j / 20];
			e = d;
			d = c;
			c = ROTATE(b, 30);
			b = a;
			a = t;
		}
		a += A;
		b += B;
		c += C;
		d += D;
		e += E;
	}

	result[0] = a;
	result[1] = b;
	result[2] = c;
	result[3] = d;
	result[4] = e;

	delete[] new_buffer;
	new_buffer = NULL;
}

void AbstractAlgorithm::getSHA1Value(unsigned int result[5], const char* filename)
{
	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* buffer = new unsigned char[size];
	fread(buffer, sizeof(unsigned char), size, file);
	fclose(file);
	getSHA1Value(result, buffer, size);
	delete[] buffer;
	buffer = NULL;
}

void AbstractAlgorithm::initCRC32Table()
{
	unsigned int crc;
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			if (crc & 1)
				crc = (crc >> 1) ^ 0xEDB88320;
			else
				crc = crc >> 1;
		m_CRC32[i] = crc;
	}
}