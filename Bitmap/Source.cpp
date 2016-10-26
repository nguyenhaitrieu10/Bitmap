#include "Bitmap.h"
#include <iostream>
#include <Windows.h>
using namespace std;

//1) Cho trước 1 ảnh, hãy chuyển ảnh sang dạng Grayscale(tức là Red = Green = Blue).
//Gợi ý : Red(mới) = Green(mới) = Blue(mới) = 0.3* Red(cũ) + 0.59* Green(cũ) + 0.11 * Blue(cũ).
//2) Làm ảnh ố vàng(giả làm ảnh cũ) :
//Cường độ sáng(gọi là I) = 0.3* Red(cũ) + 0.59* Green(cũ) + 0.11 * Blue(cũ).
//Red(mới) = I * 1.1;
//Green(mới) = I * 1.15;
//Blue(mới) = I *0.75;
//3) Làm mờ ảnh :
//Mỗi pixel ảnh(mới) = trung bình cộng 9 pixel xung quanh

int main()
{
	char pathIn[100] = "test.bmp"; // đường dẫn file input
	char pathOut[100] = "../result.bmp"; // đường dẫn file output
	FILE *fin = fopen(pathIn, "rb"); 
	FILE *fout = fopen(pathOut, "wb");

	if (!fin) // không tìm thấy file
	{
		cout << pathIn << " not found!" << endl;
		return 1;
	}
	if (!fout) // không tìm thấy file
	{
		cout << pathOut << " not found!" << endl;
		return 1;
	}

	Bitmap bm;        // tạo đối tượng Bitmap
	bm.readBitmap(fin); // đọc file Bitmap (1)

	if (!bm.isBmpFile()) // file không phải định dạng BMP
	{
		cout << pathIn << " is not Bmp file!" << endl;
		return 1;
	}

	//bm.drawBitmap(); // Vẽ Bimap vừa đọc lên console

	bm.writeBitmap(fout); // ghi file Bitmap xuống ổ cứng (2)
	
	bm.printBitmapInfo(); // xuất ra các thông tin cơ bản của ảnh (3)
	
	// thay đổi giá trị điểm ảnh (4)
	RGB colorDest(BLACK, BLACK, BLACK);
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			bm.changeBmp(i, j, colorDest);

	// Tạo Bitmap mới cắt 1 phần từ Bitmap có sẵn
	Bitmap part(bm, 50, 150, 300, 300);

	bm.drawBitmap();
	bm.encreaseLightness();

	Sleep(1000);

	bm.drawBitmap();
	bm.encreaseLightness();
	bm.drawBitmap();
	bm.encreaseLightness();
	fcloseall();
	system("pause");
	return 0;
}