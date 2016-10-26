#pragma once
#include "RGB.h"
#include "BmpDib.h"
#include <Windows.h>

#pragma pack(1)
class PixelArray
{
private:
	RGB	 **pixels;
	uint32_t rowCount;
	uint32_t columnCount;
public:
	PixelArray();
	PixelArray(const PixelArray &source);
	
	void readBmpPixelArray(FILE *f, BmpHeader header, BmpDib dib);
	void writeBmpPixelArray(FILE *f, char padding);
	void drawBmp(BmpDib dib);
	void changePixel(int row, int col, RGB dest);
	PixelArray& operator =(const PixelArray &pixelArr);
	bool cutPartFrom(const PixelArray &source, int top, int left, int bot, int right);
	void changeLightness(unsigned char value);
	void edit(void(*handle) (RGB &color));
	~PixelArray();
};



