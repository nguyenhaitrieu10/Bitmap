#include <stdio.h>
#include <Windows.h>
#include "headerbmp.h"

bool isBmpFile(FILE *f)
{
	if (f == NULL)
		return false;

	BmpSignature signature;
	fseek(f, 0, 0L);
	fread(&signature, sizeof(BmpSignature), 1, f);

	return signature.data[0] == 'B' && signature.data[1] == 'M';
}

void readBmpHeader(FILE *f, BmpHeader &header)
{
	if (f == NULL)
		return;

	fseek(f, 0, 0L);
	fread(&header, sizeof(BmpHeader), 1, f);
}

void printBmpHeader(BmpHeader header)
{
	printf("*** BMP Header ***\n");
	printf("- File Size  : %d byte(s)\n", header.fileSize);
	printf("- Reserved1  : %d\n", header.reserved1);
	printf("- Reserved2  : %d\n", header.reserved2);
	printf("- Data Offset: %d byte(s)\n", header.dataOffset);
}

void readBmpDib(FILE *f, BmpDib &dib)
{
	if (f == NULL)
		return;

	fseek(f, sizeof(BmpHeader), 0L);
	fread(&dib, sizeof(BmpDib), 1, f);
}

void printBmpDib(BmpDib dib)
{
	printf("*** BMP Dib ***\n");
	printf("- DIB Size               : %d byte(s)\n", dib.dibSize);
	printf("- Image Width            : %d\n", dib.imageWidth);
	printf("- Image Height           : %d\n", dib.imageHeight);
	printf("- Number of Color Planes : %d\n", dib.colorPlaneCount);
	printf("- Pixel Size             : %d bit(s)\n", dib.pixelSize);
	printf("- Compress Method        : %d\n", dib.compressMethod);
	printf("- Bitmap Size            : %d byte(s)\n", dib.bitmapByteCount);
	printf("- Horizontal Resolution  : %d\n", dib.horizontalResolution);
	printf("- Vertical Resolution    : %d\n", dib.verticalResolution);
	printf("- Number of Colors       : %d\n", dib.colorCount);
	printf("- Number of Impt Colors  : %d\n", dib.importantColorCount);
}


void readBmpPixelArray(FILE *f, BmpHeader header, BmpDib dib, PixelArray &data)
{
	if (f == NULL)
		return;

	data.rowCount = dib.imageHeight;
	data.columnCount = dib.imageWidth;
	data.pixels = new Color*[data.rowCount];

	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;

	fseek(f, header.dataOffset, 0L);

	for (int i = 0; i < data.rowCount; i++)
	{
		scanBmpPixelLine(f, data.pixels[data.rowCount - 1 - i], dib.imageWidth);
		skipBmpPadding(f, paddingCount);
	}
}

void scanBmpPixelLine(FILE *f, Color *&line, uint32_t length)
{
	if (f == NULL)
		return;

	line = new Color[length];
	fread(line, sizeof(Color), length, f);
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

void drawBmp(BmpDib dib, PixelArray data)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < dib.imageHeight; i++)
		for (int j = 0; j < dib.imageWidth; j++)
		{
			Color pixel = data.pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.red, pixel.green, pixel.blue));
		}

	ReleaseDC(console, hdc);
}

void releaseBmpPixelArray(PixelArray data)
{
	for (int i = 0; i < data.rowCount; i++)
		delete []data.pixels[i];

	delete []data.pixels;
}

void changeBmp(PixelArray &p, Color source, Color dest)
{
	for (int i = 0; i < p.rowCount; i++)
		for (int j = 0; j < p.columnCount; j++)
		{
			if (p.pixels[i][j].red == source.red && p.pixels[i][j].green == source.green && p.pixels[i][j].blue == source.blue)
			{	
				p.pixels[i][j].red = dest.red;
				p.pixels[i][j].green = dest.green;
				p.pixels[i][j].blue = dest.blue;
			}
		}
}

void readInput(FILE *f, char *namein, char *nameout, Color &source, Color &dest)
{
	fgets(namein,MAX,f);
	namein[strlen(namein)-2]='\0';
	fgets(nameout,MAX,f);
	nameout[strlen(nameout)-2]='\0';
	int r,g,b;
	fscanf(f,"\n%d %d %d",&r,&g,&b);
	source.red=(unsigned char)r; source.blue=(unsigned char)b;source.green=(unsigned char)g;
	fscanf(f,"\n%d %d %d",&r,&g,&b);
	dest.red=(unsigned char)r; dest.blue=(unsigned char)b;dest.green=(unsigned char)g;
}

void Output1(FILE *g, BmpHeader header, BmpDib dib)
{
	fprintf(g,"\n%d %d %d %d",header.fileSize,dib.imageWidth,dib.imageHeight,dib.pixelSize);
}
void addPadding(FILE* fo, char count)
{
	if (fo == NULL)
		return;

	char padding[3];
	fwrite(padding, count, 1, fo);
}
void PrintBmpPixelLine(FILE *fo, Color *&line, uint32_t length)
{
	if (fo == NULL)
		return;

	fwrite(line, sizeof(Color), length, fo);
}

void CopyBMP( FILE *fo, BmpHeader header, BmpDib dib, PixelArray data)
{
	if (fo == NULL)
		return;

	fwrite(&header, sizeof(BmpHeader), 1, fo);
	fwrite(&dib, sizeof(BmpDib), 1, fo);
	fseek(fo, header.dataOffset, 0L);
	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;
	for (int i = 0; i < data.rowCount; i++)
	{
		PrintBmpPixelLine(fo, data.pixels[data.rowCount - i - 1], dib.imageWidth);
		addPadding(fo, paddingCount);
	}
}

void writeBmpPixelArray(FILE *f, BmpHeader header, BmpDib dib, PixelArray &data)
{
	if (f == NULL)
		return;

	data.rowCount = dib.imageHeight;
	data.columnCount = dib.imageWidth;

	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;

	fseek(f, header.dataOffset, 0L);

	for (int i = 0; i < data.rowCount; i++)
	{
		writeBmpPixelLine(f, data.pixels[data.rowCount - i - 1], dib.imageWidth);
		addBmpPadding(f, paddingCount);
	}
}


void writeBmpPixelLine(FILE *f, Color *&line, uint32_t length)
{
	if (f == NULL)
		return;

	fwrite(line, sizeof(Color), length, f);
}