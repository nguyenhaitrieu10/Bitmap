#include "Bitmap.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	char pathIn[100] = "test.bmp"; // đường dẫn file input
	char pathOut[100] = "clone.bmp"; // đường dẫn file output
	FILE *fin = fopen(pathIn, "rb"); 
	FILE *fout = fopen(pathOut, "wb");

	if (!fin || !fout) // không tìm thấy đường dẫn
	{
		cout << "Files not found!" << endl;
		return 1;
	}

	// (1) Đọc file Bitmap 
	Bitmap bm;        
	bm.readBitmap(fin);

	if (!bm.isBmpFile()) // file không phải định dạng BMP
	{
		cout << pathIn << " is not Bmp file!" << endl;
		return 1;
	}
	bm.drawBitmap(); // Vẽ Bimap vừa đọc lên console

	// (2) Ghi file Bitmap xuống ổ cứng
	bm.writeBitmap(fout); 
	
	// (3) Xuất ra các thông tin cơ bản của ảnh
	bm.printBitmapInfo(); 
	Sleep(2000);
	bm.drawBitmap(); 

	// (4) Thay đổi giá trị điểm ảnh
	// demo: Tô đen cột trái ảnh
	RGB dest(BLACK, BLACK, BLACK);
	Bitmap temp = bm;
	for (int i = 0; i < bm.getRowCount(); i++)
		for (int j = 0; j < bm.getcolumCount() / 3; j++)
		{
			temp.changeBmp(i, j, dest);
		}
	temp.drawBitmap();

	// (5) Tạo Bitmap mới bằng cách sao chép từ 1 đối tượng Bitmap khác
	Bitmap clone(bm);

	// (6) Tạo Bitmap mới cắt 1 phần từ Bitmap có sẵn
	Bitmap part(bm, 50, 150, 300, 300); // cắt từ đoạn (50,150) -> (300,300)
	
	// (7) Tăng giảm độ sáng của ảnh
	clone.increaseLightness(5); // tăng 5 đơn vị
	clone.drawBitmap();			// vẽ ảnh lên console
	clone.increaseLightness(5); // tăng 5 đơn vị
	clone.drawBitmap();			// vẽ ảnh lên console
	clone.decreaseLightness(20);// giảm 20 đơn vị
	clone.drawBitmap();			// vẽ ảnh lên console

	
	// (8) Nhận vào cơ chế xử lý điểm ảnh (dạng con trỏ hàm) và áp dụng lên toàn bộ ảnh
	// demo 1: chuyển sang ảnh trắng đen 
	void(*pFunc) (RGB&) = RGB::convertWhiteBlack;
	clone.editBmp(pFunc);
	clone.drawBitmap();
	FILE *fdemo = fopen("WhiteBlack.bmp", "wb");
	clone.writeBitmap(fdemo); 
	fclose(fdemo);

	// demo 2: chuyển sang ảnh GrayScale
	pFunc = RGB::convertGrayScale;
	clone = bm;
	clone.editBmp(pFunc);
	clone.drawBitmap();
	fdemo = fopen("GrayScale.bmp", "wb");
	clone.writeBitmap(fdemo); 
	fclose(fdemo);

	// demo 3: Làm ảnh úa vàng (giả làm ảnh cũ)
	pFunc = RGB::convertOld;
	clone = bm;
	clone.editBmp(pFunc);
	clone.drawBitmap();
	fdemo = fopen("Old.bmp", "wb");
	clone.writeBitmap(fdemo); 
	fclose(fdemo);

	fcloseall();
	return 0;
}