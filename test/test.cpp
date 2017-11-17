#include <stdio.h>
#include <string.h>
#include "AbstractAlgorithm.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Parameters error!\n");
		return 0;
	}
	char* string = argv[1];
	printf("Abstract algorithm begins.\n");
	AbstractAlgorithm aa;
	printf("CRC32 value of \"%s\":  %08X\n", string, aa.getCRC32Value((unsigned char*)string, strlen(string)));
	printf("MD5 value of \"%s\":    ", string);
	unsigned int md5[4] = { 0 };
	aa.getMD5Value(md5, (unsigned char*)string, strlen(string));
	unsigned char md5_byte[16] = { 0 };
	memcpy(md5_byte, md5, sizeof(unsigned int) * 4);
	for (int i = 0; i < 16; i++)
		printf("%02X ", md5_byte[i]);
	printf("\n");
	printf("SHA1 value of \"%s\":   ", string);
	unsigned int sha1[5] = { 0 };
	aa.getSHA1Value(sha1, (unsigned char*)string, strlen(string));
	unsigned char sha1_byte[20] = { 0 };
	memcpy(sha1_byte, sha1, sizeof(unsigned int) * 5);
	for (int i = 0; i < 20; i+=4)
	{
		unsigned char t = sha1_byte[i]; sha1_byte[i] = sha1_byte[i + 3]; sha1_byte[i + 3] = t;
		t = sha1_byte[i + 1]; sha1_byte[i + 1] = sha1_byte[i + 2]; sha1_byte[i + 2] = t;
	}
	for (int i = 0; i < 20; i++)
		printf("%02X ", sha1_byte[i]);
	printf("\n");
	return 0;
}
