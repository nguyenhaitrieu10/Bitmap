#include "Bitmap.h"

Bitmap::Bitmap()
{
	pixels = NULL;
	columnCount = 0;
	rowCount = 0;
}

Bitmap::Bitmap(const Bitmap &source)
{
	header = source.header;
	dib = source.dib;
	columnCount = source.columnCount;
	rowCount = source.rowCount;

	// sao chép mảng pixels
	pixels = new unsigned char[columnCount*rowCount*sizeof(RGB)];
	memcpy(pixels, source.pixels, columnCount*rowCount*sizeof(RGB));
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
		columnCount = ncol;
		rowCount = nrow;
		pixels = new unsigned char[nrow * ncol * sizeof(RGB)];
		
		for (int i = 0; i < nrow; i++)
		{
			memcpy(pixels + i*ncol*3, source.pixels + ((i + top) * source.columnCount + left) * 3, ncol * 3);
		}
	}
}

void Bitmap::readBitmap(FILE *f)
{
	if (f == NULL)
		return;

	header.readBmpHeader(f);
	dib.readBmpDib(f);
	
	rowCount = dib.getImageHeight();
	columnCount = dib.getImageWidth();
	pixels = new unsigned char[rowCount * columnCount * 3];

	char paddingCount = dib.countPadding();
	fseek(f, header.getDataOffset(), 0L);

	char padding[3];
	for (int i = 0; i < rowCount; i++)
	{
		fread(pixels + (rowCount - 1 - i)*columnCount * 3, 3, columnCount, f);
		fread(padding, 1, paddingCount, f); // bỏ đọc padding
	}
}

void Bitmap::writeBitmap(FILE *f)
{
	if (f == NULL)
		return;

	header.writeBmpHeader(f);
	dib.writeBmpDib(f);
	fseek(f, header.getDataOffset(), SEEK_SET);
	char paddingCount = dib.countPadding();

	char padding[3];
	for (int i = 0; i < rowCount; i++)
	{
		fwrite(pixels + (rowCount - 1 - i)*columnCount * 3, 3, columnCount, f);
		fwrite(padding, 1, paddingCount, f); // ghi padding
	}
}

void Bitmap::drawBitmap()
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < columnCount; j++)
		{
			RGB *pixel = (RGB*)(pixels + (i* columnCount + j) * 3);
			SetPixel(hdc, j, i, RGB(pixel->getRed(), pixel->getGreen(), pixel->getBlue()));
		}

	ReleaseDC(console, hdc);
}

void Bitmap::printBitmapInfo()
{
	header.printBmpHeader();
	dib.printBmpDib();
}

void Bitmap::changeBmp(int row, int col, RGB dest)
{
	if (row >= 0 && col >= 0 && row < rowCount && col < columnCount)
	{
		RGB *color = (RGB*)(pixels + (row * columnCount + col) * 3);
		color->setRed(dest.getRed());
		color->setGreen(dest.getGreen());
		color->setBlue(dest.getBlue());
	}
}

Bitmap& Bitmap::operator =(const Bitmap &source)
{
	if (this != &source)
	{
		delete[]pixels;
		header = source.header;
		dib = source.dib;
		columnCount = source.columnCount;
		rowCount = source.rowCount;

		// sao chép mảng pixels
		pixels = new unsigned char[columnCount*rowCount*sizeof(RGB)];
		memcpy(pixels, source.pixels, columnCount*rowCount*sizeof(RGB));
	}
	return *this;
}

void Bitmap::increaseLightness(unsigned char value)
{
	unsigned char *color = pixels;
	for (int i = 0; i < rowCount * columnCount * 3; i++)
	{
		if ((*color) + value > 255)
			(*color) = 255;
		else
			*color += value;
		color++;
	}
}

void Bitmap::decreaseLightness(unsigned char value)
{
	unsigned char *color = pixels;
	for (int i = 0; i < rowCount * columnCount * 3; i++)
	{
		if ((*color) - value < 0)
			(*color) = 0;
		else
			*color -= value;
		color++;
	}
}

void Bitmap::editBmp(void (*handle) (RGB &color))
{
	RGB *color = (RGB*)pixels;
	for (int i = 0; i < rowCount * columnCount ; i++)
	{
		handle(*color);
		color++;
	}
}

bool Bitmap::isBmpFile()
{
	unsigned char *sign = header.getBmpSignature();
	return sign[0] == 'B' && sign[1] == 'M';
}

RGB Bitmap::getPixel(int row, int col)
{
	RGB color(WHITE,WHITE,WHITE);
	if (row < rowCount && col < columnCount && row >=0 && col >=0)
		color = *(RGB*)(pixels + (row * columnCount + col) * sizeof(RGB));
	
	return color;
}

uint32_t Bitmap::getRowCount()
{
	return rowCount;
}

uint32_t Bitmap::getcolumCount()
{
	return columnCount;
}

Bitmap::~Bitmap()
{
	delete[]pixels;
}



