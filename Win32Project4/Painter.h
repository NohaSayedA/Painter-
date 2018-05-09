#pragma once
#include "Shape.h"
#include "Circle.h"
#include <iostream>
#include <vector>
#include "Clipping.h"
#include "Filling.h"
using namespace std;
class Painter
{
public:
	HDC hdc;
	vector <Shape *> lines;
	Painter();
	void operate(HWND,int,HDC,LPARAM,LPARAM);
	~Painter();
};

