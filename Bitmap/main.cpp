#include <stdio.h>
#include "headerbmp.h"

void main()
{
	FILE *f = fopen("Bitmap.in", "rb");
	FILE *g = fopen("Bitmap.out", "w");

	if (f==NULL){

		return;
	}
	char *namein=new char [MAX];
	char *nameout=new char [MAX];
	Color source, dest;
	readInput(f,namein,nameout,source,dest);
	FILE *fi=fopen(namein,"rb");
	FILE *fo=fopen(nameout,"wb");
	if (fi==NULL)
		return;
	if (!isBmpFile(fi))
		fprintf(g,"%d",0);
	else fprintf(g,"%d",1);
	BmpHeader header;
	readBmpHeader(fi, header);

	BmpDib dib;
	readBmpDib(fi, dib);

	Output1(g,header,dib);
	fclose(f);
	fclose(g);
	PixelArray data;
	readBmpPixelArray(fi, header, dib, data);
	changeBmp(data,source,dest);
	drawBmp(dib, data);

	CopyBMP(fo,header,dib,data);

	fclose(fi);
	fclose(fo);
	delete []namein;
	delete []nameout;
	getchar();
	releaseBmpPixelArray(data);
}