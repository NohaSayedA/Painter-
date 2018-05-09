#include "stdafx.h"
#include "circle.h"
#include <math.h>
#include <iostream>

Circle::Circle()
{
}

Circle::Circle(HDC hdc,int choice,Point center ,Point r)
{
	this->hdc = hdc;
	this->algorithm = choice;
	this->r = r;
	this->center = center;
}
void Circle::draw( COLORREF color){
	if (algorithm == 1)
	{
		this->DrawCartesian(color);
	}
	else if (algorithm == 2)
	{
		this->DrawMidPoint(color);
	}
	else if (algorithm == 3)
	{
		this->DrawPolar( color);
	}
}
void Circle::DrawPolar(COLORREF color)
{
	int R = sqrt(pow((r.x - center.x), 2) + pow((r.y - center.y), 2));
	int x = 0, y = R;
	double theta = 90, d = (1.0 / R);
	while (x<=y)
	{
		Draw8Points(x, y, center.x, center.y, color);
		theta -= d;
		x = round(R*cos(theta));
		y = round(R*sin(theta));
	}
}
void Circle::DrawMidPoint( COLORREF color)
{
	int R = sqrt(pow((r.x - center.x), 2) + pow((r.y - center.y), 2));
	int x = 0, y = R;
	int d = 1 - R;
	while (x <= y)
	{
		Draw8Points(x, y, center.x, center.y, color);
		if (d < 0)		d += (2 * x + 3);
		else{
			d += 2 * x - 2 * y + 5;
			y--;
		}
		x++;
	}
}
void Circle:: Draw8Points(int x, int y, int xc, int yc, COLORREF color)
{
	SetPixel(hdc, xc + x, yc + y, color);
	SetPixel(hdc, xc - x, yc + y, color);
	SetPixel(hdc, xc - x, yc - y, color);
	SetPixel(hdc, xc + x, yc - y, color);
	SetPixel(hdc, xc + y, yc + x, color);
	SetPixel(hdc, xc - y, yc + x, color);
	SetPixel(hdc, xc - y, yc - x, color);
	SetPixel(hdc, xc + y, yc - x, color);
}
void Circle ::  DrawCartesian( COLORREF color)
{
	int R = sqrt(pow((r.x - center.x), 2) + pow((r.y - center.y), 2));
	int x = 0, y = R;
	while (x <= y)
	{
		Draw8Points(x, y, center.x, center.y, color);
		x++;
		y = sqrt(pow(R, 2) - pow(x, 2));
	}
}

Circle::~Circle()
{
}
