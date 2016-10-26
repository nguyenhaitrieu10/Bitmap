#include "BmpHeader.h"


BmpHeader::BmpHeader()
{
	fileSize = 0;
}

void BmpHeader::readBmpHeader(FILE *f)
{
	if (f == NULL)
		return;

	fseek(f, 0, 0L);
	fread(this, sizeof(BmpHeader), 1, f);
}

void BmpHeader::writeBmpHeader(FILE *f)
{
	if (f == NULL)
		return;

	fwrite(this, sizeof(BmpHeader), 1, f);
}

void BmpHeader::printBmpHeader()
{
	printf("*** BMP Header ***\n");
	printf("- File Size  : %d byte(s)\n", this->fileSize);
	printf("- Reserved1  : %d\n", this->reserved1);
	printf("- Reserved2  : %d\n", this->reserved2);
	printf("- Data Offset: %d byte(s)\n", this->dataOffset);
}

uint32_t BmpHeader::getDataOffset()
{
	return this->dataOffset;
}

void BmpHeader::setFileSize(uint32_t newSize)
{
	this->fileSize = newSize;
}

unsigned char* BmpHeader::getBmpSignature()
{
	return signature.data;
}