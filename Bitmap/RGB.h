#pragma once
#include <cstdint>
#define BLACK 0
#define WHITE 255
#define LIGHT_UNIT 10
#pragma pack(1)
class RGB
{
private:
	unsigned char blue;
	unsigned char green;
	unsigned char red;
public:
	RGB();
	RGB(unsigned char newRed, unsigned char newGreen, unsigned char newBlue);
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
	void setRed(unsigned char value);
	void setGreen(unsigned char value);
	void setBlue(unsigned char value);

	static void increLighness(RGB& color);
	static void convertGrayScale(RGB& color);
	static void convertWhiteBlack(RGB& color);
	static void convertOld(RGB &color);
	~RGB();
};

