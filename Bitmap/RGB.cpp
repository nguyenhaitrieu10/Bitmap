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

void RGB::plusRGB(unsigned char value)
{
	red += value;
	blue += value;
	green += value;
}

RGB::~RGB()
{
}
