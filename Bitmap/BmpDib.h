#pragma once
#include "BmpHeader.h"
#include "RGB.h"
#pragma pack(1)
class BmpDib
{
private:
	uint32_t dibSize;
	int32_t	 imageWidth;
	int32_t  imageHeight;
	uint16_t colorPlaneCount;
	uint16_t pixelSize;
	uint32_t compressMethod;
	uint32_t bitmapByteCount;
	int32_t  horizontalResolution;
	int32_t  verticalResolution;
	uint32_t colorCount;
	uint32_t importantColorCount;
public:
	BmpDib();
	void readBmpDib(FILE *f);
	void writeBmpDib(FILE *f);
	void printBmpDib();
	int32_t getImageWidth() const;
	int32_t getImageHeight() const;
	char countPadding();
	void setNewSize(uint32_t width, uint32_t height);
	~BmpDib();
};

