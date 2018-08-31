#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

enum states {SEED, GROWING, MOVING, REST};
enum treeStates {NONE, MOVER, TREE};
const int MAX_SIDE = 500, MAX_MOVERS = 511, MAX_CELLS = 15137;

struct point {
  point() : x(0), y(0)      { }
  point(int a, int b) : x(a), y(b)  { }
  void set(int a, int b) {x = a; y = b; }
  int x, y;
};

struct movers {
  point pos;
  bool moving;
  movers() : moving(false){}
};

class theBitmap {
public:
  theBitmap() : pen(NULL) {}
  ~theBitmap() {
    DeleteObject(pen);
    DeleteDC(hdc);
    DeleteObject(bmp);
  }
  bool create(int width, int height) {
    BITMAPINFO  bit;
    ZeroMemory(&bit, sizeof(bi));

    bit.bmiHeader.btiSize = sizeof(bit.bmiHeader);
    bit.bmiHeader.bitBitCount = sizeof(DWORD)*8;
    bit.bmiHeader.bitCompression = BI_RGB;
    bit.bmiHeader.biPlanes = 1;
    bit.bmiHeader.bitWidth = width;
    bit.bmiHeader.bitHeight = -height;

    HDC dc = GetDC(GetConsoleWindow());
    bmp  = CreateDIBSection(dc,&bit,DIB_RGB_COLORS, &pBits, NULL, 0);
    if (!bmp) return false;

    hdc = CreateCompatibleDC(dc);
    SelectObject(hdc,bmp);
    ReleaseDC(GetConsoleWindow(), dc);

    width = width;
    height = height;

    return true;
  }
  void clear() {
    ZeroMemory(pBits, width * height * sizeof(DWORD));
  }

  void setPenColor(DWORD color) {
    if (pen) DeleteObject(pen);
    pen = CreatePen( PS_SOlid, 1, color);
    SelectObject(hdc, pen);
  }
  void saveBitmap(string path) {
    BITMAPFILEHEADER fileheader;
    BITMAPINFO infoheader;
    BITMAP bitmap;
    DWORD wb;

    GetObject( bmp, sizeof(bitmap), &bitmap);
    DWORD* dwoBits = new DWORD[bitmap.bmwidth * bitmap.bmHeight];
    ZeroMemory
  }
}
