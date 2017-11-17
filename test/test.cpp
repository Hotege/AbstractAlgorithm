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
	for (int i = 0; i < 5; i++)
		printf("%08X ", sha1[i]);
	printf("\n");
	unsigned int sha256[8] = { 0 };
	aa.getSHA256Value(sha256, (unsigned char*)string, strlen(string));
	printf("SHA256 value of \"%s\": ", string);
	for (int i = 0; i < 8; i++)
		printf("%08X ", sha256[i]);
	printf("\n");
	return 0;
}
