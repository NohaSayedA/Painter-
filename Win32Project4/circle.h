#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
	HDC hdc;
	int algorithm;
public:
	Point center;
	Point r;
	Circle();
	Circle(HDC hdc, int choice,Point,Point);
	void draw(COLORREF );
	void DrawPolar(COLORREF);
	void Draw8Points(int ,int ,int ,int , COLORREF);
	void DrawCartesian(COLORREF);
	void DrawMidPoint(COLORREF );
	~Circle();
};

