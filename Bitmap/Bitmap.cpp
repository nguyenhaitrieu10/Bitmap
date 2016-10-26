#include "Bitmap.h"

Bitmap::Bitmap()
{
}

Bitmap::Bitmap(const Bitmap &source)
{
	header = source.header;
	dib = source.dib;
	data = source.data; // Toán tử "=" đã được nạp chồng trong class PixelArray
}

Bitmap::Bitmap(const Bitmap &source, int top, int left, int bot, int right)
{
	if (top >= 0 && top <= bot && bot < source.dib.getImageHeight() && left >= 0 && left <= right && right < source.dib.getImageWidth())
	{
		header = source.header;
		dib = source.dib;

		uint32_t nrow = right - left + 1;
		uint32_t ncol = bot - top + 1;

		dib.setNewSize(nrow, ncol);
		uint32_t newSize = sizeof(BmpHeader) + sizeof(BmpDib) + nrow * (ncol * sizeof(RGB) + dib.countPadding());
		header.setFileSize(newSize);

		data.cutPartFrom(source.data, top, left, bot, right);
	}
}

void Bitmap::readBitmap(FILE *fin)
{
	if (fin == NULL)
		return;

	header.readBmpHeader(fin);
	dib.readBmpDib(fin);
	data.readBmpPixelArray(fin, header, dib);
}


void Bitmap::writeBitmap(FILE *fout)
{
	if (fout == NULL)
		return;

	header.writeBmpHeader(fout);
	dib.writeBmpDib(fout);
	fseek(fout, header.getDataOffset(), SEEK_SET);
	char padding = dib.countPadding();
	data.writeBmpPixelArray(fout, padding);
}

void Bitmap::drawBitmap()
{
	data.drawBmp(dib);
}

void Bitmap::printBitmapInfo()
{
	header.printBmpHeader();
	dib.printBmpDib();
}

void Bitmap::changeBmp(int row, int col, RGB dest)
{
	data.changePixel(row, col, dest);
}

void Bitmap::encreaseLightness(unsigned char value)
{
	data.changeLightness(value);
}

void Bitmap::decreaseLightness(unsigned char value)
{
	data.changeLightness(-value);
}

void Bitmap::editBmp(void(*handle) (RGB &color))
{
	data.edit(handle);
}

Bitmap::~Bitmap()
{
}

bool Bitmap::isBmpFile()
{
	unsigned char *sign = header.getBmpSignature();
	return sign[0] == 'B' && sign[1] == 'M';
}

void increLighness(RGB &color)
{
	color.setRed(color.getRed() + 10);
	color.setGreen(color.getGreen() + 10);
	color.setBlue(color.getBlue() + 10);
}


//int gray = p.pixels[i][j].red*0.299 + p.pixels[i][j].green*0.587 + p.pixels[i][j].blue*0.114;
//p.pixels[i][j].red = p.pixels[i][j].green = p.pixels[i][j].blue = (gray>128) ? 255 : 0;