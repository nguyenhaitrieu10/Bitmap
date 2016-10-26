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

// Tăng độ sáng ảnh
void RGB::increLighness(RGB &color)
{
	unsigned char _red = color.getRed();
	unsigned char _green = color.getGreen();
	unsigned char _blue = color.getBlue();

	color.setRed((_red + LIGHT_UNIT > 255) ? 255 : (_red + LIGHT_UNIT));
	color.setGreen((_green + LIGHT_UNIT > 255) ? 255 : (_green + LIGHT_UNIT));
	color.setBlue((_blue + LIGHT_UNIT > 255) ? 255 : (_blue + LIGHT_UNIT));
}

// Chuyển sang ảnh trắng đen
void RGB::convertWhiteBlack(RGB &color)
{
	unsigned char _red = color.getRed();
	unsigned char _green = color.getGreen();
	unsigned char _blue = color.getBlue();

	int gray = _red*0.299 + _green*0.587 + _blue*0.114;
	color.setRed((gray > 128) ? 255 : 0);
	color.setGreen((gray > 128) ? 255 : 0);
	color.setBlue((gray > 128) ? 255 : 0);
}

// Làm ảnh ố vàng (giả làm ảnh cũ) :
void RGB::convertOld(RGB &color)
{
	unsigned char _red = color.getRed();
	unsigned char _green = color.getGreen();
	unsigned char _blue = color.getBlue();

	int I = _red*0.299 + _green*0.587 + _blue*0.114;
	color.setRed( I*1.1 > 255? 255: I*1.1);
	color.setGreen(I*1.15 > 255 ? 255 : I*1.15);
	color.setBlue(I*0.75 > 255 ? 255 : I*0.75);
}

// Chuyển ảnh GrayScale
void RGB::convertGrayScale(RGB& color)
{
	unsigned char _red = color.getRed();
	unsigned char _green = color.getGreen();
	unsigned char _blue = color.getBlue();

	int I = _red*0.299 + _green*0.587 + _blue*0.114;
	color.setRed(I);
	color.setGreen(I);
	color.setBlue(I);
}
