#pragma once
#include <cstdint>
#include <fstream>

struct BmpSignature
{
	unsigned char data[2];
};

#pragma pack(1)
class BmpHeader
{
private:
	BmpSignature signature;
	uint32_t fileSize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t dataOffset;
public:
	BmpHeader();
	void readBmpHeader(FILE *fin);
	void writeBmpHeader(FILE *fout);
	void printBmpHeader();
	uint32_t getDataOffset();
	void setFileSize(uint32_t newSize);
	unsigned char* getBmpSignature();
};


