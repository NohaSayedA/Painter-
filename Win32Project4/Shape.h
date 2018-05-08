#pragma once
struct Point{
	int x, y;
};
class Shape
{
public:
	HDC hdc;
	int algorithm;
	Shape();
	Shape(HDC, int,Point,Point);
	virtual void draw(COLORREF ) = 0;
	~Shape();
};

