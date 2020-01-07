#include <iostream>
using namespace std;
#include <windows.h> 

// Gdiplus 
#pragma comment( lib, "gdiplus.lib" ) 
#include <gdiplus.h> 

static const wchar_t* filename = L"D:\\png.png";

#include <vector>
#include <cstdint>
#include "gif.h"

void example00() {
	int width = 100;
	int height = 200;
	std::vector<uint8_t> black(width * height * 4, 0);
	std::vector<uint8_t> white(width * height * 4, 255);

	auto fileName = "bwgif.gif";
	int delay = 100;
	GifWriter g;
	GifBegin(&g, fileName, width, height, delay);
	GifWriteFrame(&g, black.data(), width, height, delay);
	GifWriteFrame(&g, white.data(), width, height, delay);
	GifEnd(&g);
}

int main()
{
    // Start Gdiplus 
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Load the image 
    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(filename);

    // do something with your image 
    // ... 

    Gdiplus::PixelFormat format;
    format = bitmap->GetPixelFormat();

    switch (format) {
        case    PixelFormat1bppIndexed:     cout << "PixelFormat1bppIndexed" << endl; break;
        case    PixelFormat4bppIndexed:     cout << "PixelFormat4bppIndexed" << endl; break;
        case    PixelFormat8bppIndexed:     cout << "PixelFormat8bppIndexed" << endl; break;
        case    PixelFormat16bppGrayScale:  cout << "PixelFormat16bppGrayScale" << endl; break;
        case    PixelFormat16bppRGB555:     cout << "PixelFormat16bppRGB555" << endl; break;
        case    PixelFormat16bppRGB565:     cout << "PixelFormat16bppRGB565" << endl; break;
        case    PixelFormat16bppARGB1555:   cout << "PixelFormat16bppARGB1555" << endl; break;
        case    PixelFormat24bppRGB:        cout << "PixelFormat24bppRGB" << endl; break;
        case    PixelFormat32bppRGB:        cout << "PixelFormat32bppRGB" << endl; break;
        case    PixelFormat32bppARGB:       cout << "PixelFormat32bppARGB" << endl; break;
        case    PixelFormat32bppPARGB:      cout << "PixelFormat32bppPARGB" << endl; break;
        case    PixelFormat48bppRGB:        cout << "PixelFormat48bppRGB" << endl; break;
        case    PixelFormat64bppARGB:       cout << "PixelFormat64bppARGB" << endl; break;
        case    PixelFormat64bppPARGB:      cout << "PixelFormat64bppPARGB" << endl; break;
        case    PixelFormat32bppCMYK:       cout << "PixelFormat32bppCMYK" << endl; break;
        case    PixelFormatMax:             cout << "PixelFormatMax" << endl; break;
        break;
    }
    const auto bpp = Gdiplus::GetPixelFormatSize(format);
    const auto w = bitmap->GetWidth();
    const auto h = bitmap->GetHeight();
    const auto size = w * h * bpp / 8;

    Gdiplus::BitmapData data;
    const Gdiplus::Rect rect(0, 0, w, h);
    bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, format, &data);
    // delete the image when done 
    auto fileName = "bwgif.gif";
    GifWriter g;
    GifBegin(&g, fileName, w, h, 20);
    GifWriteFrame(&g, reinterpret_cast<BYTE*>(data.Scan0), w, h, 50);
    GifEnd(&g);
    bitmap->UnlockBits(&data);
    delete bitmap;
    bitmap = nullptr;

    // Shutdown Gdiplus 
    Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}