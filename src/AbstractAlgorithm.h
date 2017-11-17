#ifndef _ABSTRACTALGORITHM_H_
#define _ABSTRACTALGORITHM_H_

class AbstractAlgorithm
{
public:
	AbstractAlgorithm();
	~AbstractAlgorithm();

	unsigned int getCRC32Value(const void* buffer, const int size);
	unsigned int getCRC32Value(const char* filename);
	void getMD5Value(unsigned int result[4], const void* buffer, const int size);
	void getMD5Value(unsigned int result[4], const char* filename);
	void getSHA1Value(unsigned int result[5], const void* buffer, const int size);
	void getSHA1Value(unsigned int result[5], const char* filename);
	void getSHA256Value(unsigned int result[8], const void* buffer, const int size);
	void getSHA256Value(unsigned int result[8], const char* filename);
private:
	void initCRC32Table();

	unsigned int m_CRC32[256];
};

#endif