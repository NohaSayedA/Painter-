#pragma once
struct Point{
	int x, y;
};
class Shape
{
public:
	Point start, end;
	HDC hdc;
	int algorithm;
	Shape();
	Shape(HDC, int,Point,Point);
	virtual void draw(COLORREF ) = 0;
	~Shape();
};

