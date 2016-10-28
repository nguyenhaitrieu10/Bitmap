#include "RGB.h"

RGB::RGB()
{
}

RGB::RGB(unsigned char newRed, unsigned char newGreen, unsigned char newBlue)
{
	red = newRed;
	green = newGreen;
	blue = newBlue;
}

unsigned char RGB::getRed()
{
	return this->red;
}

unsigned char RGB::getGreen()
{
	return this->green;
}

unsigned char RGB::getBlue()
{
	return this->blue;
}

void RGB::setRed(unsigned char value)
{
	red = value;
}

void RGB::setGreen(unsigned char value)
{
	green = value;
}

void RGB::setBlue(unsigned char value)
{
	blue = value;
}

RGB::~RGB()
{
}

//------- Các hàm xử lý điểm ảnh có thể truyền vào hàm editBmp() --------------

// Chuyển sang ảnh trắng đen
void convertWhiteBlack(RGB &color)
{
	int gray = color.red*0.299 + color.green*0.587 + color.blue*0.114;
	color.red = (gray > 128) ? 255 : 0;
	color.green = (gray > 128) ? 255 : 0;
	color.blue = (gray > 128) ? 255 : 0;
}

// Làm ảnh ố vàng (giả làm ảnh cũ) :
void convertOld(RGB &color)
{
	int I = color.red*0.299 + color.green*0.587 + color.blue*0.114;
	color.red = I*1.1 > 255? 255: I*1.1;
	color.green = I*1.15 > 255 ? 255 : I*1.15;
	color.blue = I*0.75 > 255 ? 255 : I*0.75;
}

// Chuyển ảnh GrayScale
void convertGrayScale(RGB& color)
{
	int I = color.red*0.299 + color.green*0.587 + color.blue*0.114;
	color.red = I;
	color.green = I;
	color.blue = I;
}
