#pragma once
#include "BmpDib.h"
#include "BmpHeader.h"
#include <memory>
#include <Windows.h>
#pragma pack(1)
class Bitmap
{
private:
	BmpHeader header;
	BmpDib dib;
	unsigned char *pixels;
	uint32_t rowCount;
	uint32_t columnCount;
public:
	Bitmap();
	Bitmap(const Bitmap &source);
	Bitmap(const Bitmap &source, int top, int left, int bot, int right);

	bool isBmpFile();
	void readBitmap(FILE *fin);
	void writeBitmap(FILE *fout);
	void drawBitmap();
	void printBitmapInfo();

	void changeBmp(int row, int col, RGB dest);
	Bitmap& operator =(const Bitmap &bm);
	void increaseLightness(unsigned char value = LIGHT_UNIT);
	void decreaseLightness(unsigned char value = LIGHT_UNIT);
	void editBmp(void (*handle) (RGB &color));
	RGB getPixel(int row, int col);

	~Bitmap();
};

