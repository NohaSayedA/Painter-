#pragma once
#include "Shape.h"
#include <vector>
using namespace std;
class Filling
{
public:
	HWND hwnd;
	int width, height;
	Filling(HWND);
	void fillWithRecursion(HDC, Point,COLORREF);
	void fillBFS(HDC, Point, COLORREF);
	~Filling();
};

