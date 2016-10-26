#include "BmpDib.h"

BmpDib::BmpDib()
{
	dibSize = 0; 
	imageWidth = 0;
	imageHeight = 0;
	colorPlaneCount = 0;
	pixelSize = 0;
	bitmapByteCount = 0;
	horizontalResolution = 0;
	verticalResolution = 0;
}

void BmpDib::readBmpDib(FILE *f)
{
	if (f == NULL)
		return;

	fseek(f, sizeof(BmpHeader), 0L);
	fread(this, sizeof(BmpDib), 1, f);
}

void BmpDib::writeBmpDib(FILE *f)
{
	if (f == NULL)
		return;

	fwrite(this, sizeof(BmpDib), 1, f);
}

void BmpDib::printBmpDib()
{
	printf("*** BMP Dib ***\n");
	printf("- DIB Size               : %d byte(s)\n", this->dibSize);
	printf("- Image Width            : %d\n", this->imageWidth);
	printf("- Image Height           : %d\n", this->imageHeight);
	printf("- Number of Color Planes : %d\n", this->colorPlaneCount);
	printf("- Pixel Size             : %d bit(s)\n", this->pixelSize);
	printf("- Compress Method        : %d\n", this->compressMethod);
	printf("- Bitmap Size            : %d byte(s)\n", this->bitmapByteCount);
	printf("- Horizontal Resolution  : %d\n", this->horizontalResolution);
	printf("- Vertical Resolution    : %d\n", this->verticalResolution);
	printf("- Number of Colors       : %d\n", this->colorCount);
	printf("- Number of Impt Colors  : %d\n", this->importantColorCount);
}

int32_t BmpDib::getImageWidth() const
{
	return this->imageWidth;
}

int32_t BmpDib::getImageHeight() const
{
	return this->imageHeight;
}

char BmpDib::countPadding()
{
	return (4 - (this->imageWidth * (this->pixelSize / 8) % 4)) % 4;
}

void BmpDib::setNewSize(uint32_t width, uint32_t height)
{
	this->imageWidth = width;
	this->imageHeight = height;
	char padding = this->countPadding();
	this->bitmapByteCount = height * (width * sizeof(RGB) + padding);
}

BmpDib::~BmpDib()
{
}
