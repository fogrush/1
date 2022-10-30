#include <cstdio> // C语言代码中必须要引用的头文件
#include <windows.h> // 图像读取的头文件

// 使代码在新版本的VS中正常运行不报错
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// 定义一个结构体来读取BMP的信息
typedef struct {
	// 定义文件头信息
	BITMAPFILEHEADER header;
	// 定义位图信息头
	BITMAPINFOHEADER info;
	// 定义彩色表
	RGBQUAD rgb[256];
	// 定义位图数据指针
	unsigned char *data;
} BMP;

// 读图像函数
void bmpRead(const char *bmpPath, BMP &bmp) {
	// 以二进制的方式打开图片
	FILE *file = fopen(bmpPath, "rb");
	// 读取文件信息头
	fread(&bmp.header, sizeof(BITMAPFILEHEADER), 1, file);
	// 读取位图信息头
	fread(&bmp.info, sizeof(BITMAPINFOHEADER), 1, file);
	// 读取彩色表
	fread(&bmp.rgb, sizeof(RGBQUAD), 256, file);
	// 定义位图数据内存大小
	bmp.data = new unsigned char[bmp.info.biWidth * bmp.info.biHeight];
	// 读取元素的位图数据
	fread(bmp.data, sizeof(unsigned char), bmp.info.biWidth*bmp.info.biHeight, file);
	// 关闭图片
	fclose(file);
}

// 定一个函数将读取到bmp.data的像素灰度值存储到一个txt文档中
void bmpCells(const char *pixelValuePath, BMP &bmp){
	// 新建一个txt文件用于存储像素值
	FILE *file = fopen(pixelValuePath, "w");
	// 循环读取像素值
	for (int i = 0; i < bmp.info.biHeight; i++)
	{
		for (int j = 0; j < bmp.info.biWidth; j++)
		{
			// 获取循环到像元的像素值
			unsigned char pixel = bmp.data[j + i*bmp.info.biWidth];
			// 这里我们打印一下读出的像元
			printf("%d ", pixel);
			// 保存到文件中
			fprintf(file, "%d ", pixel);
		}
		// 打印一行后换行
		printf("\n");
		// 完成一行像素的保存后换行继续进行保存
		fprintf(file, "\n");
	}
	// 关闭文件
	fclose(file);
}

int main() {
	// 定义图像结构体
	BMP mbmp;
	// 读取图像（如果不是按照本文的新建项目方法，建议使用绝对路径，否则可能会因为文件路径错误而报错。）
	bmpRead("C:\\Users\\translation\\Desktop\\33840.bmp", mbmp);
	// 将像素值存储到一个txt文本中
	bmpCells("C:\\Users\\translation\\Desktop\\test.txt", mbmp);
	// 删除指针，释放内存
	delete[] mbmp.data;
	// 使程序暂停，便于查看
	scanf("……");

	return 0;
}
