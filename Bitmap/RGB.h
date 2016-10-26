#pragma once
#include <cstdint>
#define BLACK 0
#define WHITE 255

#pragma pack(1)
class RGB
{
private:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
public:
	RGB();
	RGB(unsigned char newRed, unsigned char newGreen, unsigned char newBlue);
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
	void setRed(unsigned char value);
	void setGreen(unsigned char value);
	void setBlue(unsigned char value);
	void plusRGB(unsigned char value);
	~RGB();
};

