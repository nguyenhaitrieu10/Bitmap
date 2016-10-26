#include "PixelArray.h"


PixelArray::PixelArray()
{
	pixels = NULL;
	columnCount = 0;
	rowCount = 0;
}

PixelArray::PixelArray(const PixelArray &source)
{
	this->columnCount = source.columnCount;
	this->rowCount = source.rowCount;
	this->pixels = new RGB*[this->rowCount];

	for (int i = 0; i < this->rowCount; i++)
	{
		this->pixels[i] = new RGB[this->columnCount];
		for (int j = 0; j < this->columnCount; j++)
			this->pixels[i][j] = source.pixels[i][j];
	}
}

void scanBmpPixelLine(FILE *f, RGB *&line, uint32_t length)
{
	if (f == NULL)
		return;

	line = new RGB[length];
	fread(line, sizeof(RGB), length, f);
}

void skipBmpPadding(FILE *f, char count)
{
	if (f == NULL)
		return;

	if (count == 0)
		return;

	char padding[3];
	fread(padding, count, 1, f);
}

void PixelArray::readBmpPixelArray(FILE *f, BmpHeader header, BmpDib dib)
{
	if (f == NULL)
		return;

	this->rowCount = dib.getImageHeight();
	this->columnCount = dib.getImageWidth();
	this->pixels = new RGB*[this->rowCount];

	char paddingCount = dib.countPadding();

	fseek(f, header.getDataOffset(), 0L);

	for (int i = 0; i < this->rowCount; i++)
	{
		scanBmpPixelLine(f, this->pixels[this->rowCount - 1 - i], dib.getImageWidth());
		skipBmpPadding(f, paddingCount);
	}
}

void addBmpPadding(FILE *f, char count)
{
	if (count == 0)
		return;

	char padding[3];
	fwrite(padding, count, 1, f);
}

void PrintBmpPixelLine(FILE *f, RGB *line, uint32_t length)
{
	fwrite(line, sizeof(RGB), length, f);
}

void PixelArray::writeBmpPixelArray(FILE *f, char paddingCount)
{
	if (f == NULL)
		return;

	for (int i = 0; i < this->rowCount; i++)
	{
		PrintBmpPixelLine(f, this->pixels[rowCount - 1 - i], this->columnCount);
		addBmpPadding(f, paddingCount);
	}
}

void PixelArray::drawBmp(BmpDib dib)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < dib.getImageHeight(); i++)
		for (int j = 0; j < dib.getImageWidth(); j++)
		{
			RGB pixel = this->pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.getRed(), pixel.getGreen(), pixel.getBlue()));
		}

	ReleaseDC(console, hdc);
}

void PixelArray::changePixel(int row, int col, RGB dest)
{
	pixels[row][col] = dest;
}

PixelArray& PixelArray::operator = (const PixelArray &pixelArr)
{
	this->columnCount = pixelArr.columnCount;
	this->rowCount = pixelArr.rowCount;
	this->pixels = new RGB*[this->rowCount];

	for (int i = 0; i < this->rowCount; i++)
	{
		this->pixels[i] = new RGB[this->columnCount];
		for (int j = 0; j < this->columnCount; j++)
			this->pixels[i][j] = pixelArr.pixels[i][j];
	}

	return *this;
}

PixelArray::~PixelArray()
{
	for (int i = 0; i < this->rowCount; i++)
		delete[]this->pixels[i];

	delete[]this->pixels;
}

bool PixelArray::cutPartFrom(const PixelArray &source, int top, int left, int bot, int right)
{
	if (bot < top || right < left)
		return false;

	this->columnCount = right - left + 1;
	this->rowCount = bot - top + 1;
	this->pixels = new RGB*[this->rowCount];

	for (int i = top; i <= bot; i++)
	{
		this->pixels[i - top] = new RGB[this->columnCount];
		for (int j = left; j <= right; j++)
			this->pixels[i - top][j - left] = source.pixels[i][j];
	}

	return true;
}

void PixelArray::changeLightness(unsigned char value)
{
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < columnCount; j++)
			pixels[i][j].plusRGB(value);
}

void PixelArray::edit(void(*handle) (RGB &color))
{
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < columnCount; j++)
			handle(pixels[i][j]);
}