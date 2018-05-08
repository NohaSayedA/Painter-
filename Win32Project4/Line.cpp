#include "stdafx.h"
#include "Line.h"
#include <iostream>
using namespace std;
Line::Line()
{
}

Line::Line(HDC hdc, int choice, Point start, Point end)
{
	this->hdc = hdc;
	this->algorithm = choice;
	this->start = start;
	this->end = end;
}

void Line::draw(COLORREF color){
	if (algorithm == 1)
	{
		this->DrawDDA(color);
	}
	else if (algorithm == 2)
	{
		this->DrawMidPoint(color);
	}
	else if (algorithm == 3)
	{
		this->DrawDirect(color);
	}
}

void Line::DrawMidPoint( COLORREF color){
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	if (abs(dy) <= abs(dx)) // slope less than 1
	{
		if (end.x < start.x)
		{
			swap(end.x, start.x);
			swap(end.y, start.y);
			dx = -dx;
			dy = -dy;
		}
		int d = dx - abs(2 * dy);
		int c1 = 2 * dx - abs(2 * dy);
		int c2 = -2 * abs(dy);
		int x = start.x;
		int y = start.y;
		while (x <= end.x)
		{
			SetPixel(hdc, x, y, color);
			if (d <= 0)
			{
				d += c1;
				//to check if y decrease or increase
				y = (dy > 0) ? y + 1 : y - 1;
			}
			else  d += c2;
			x++;

		}
	}
	else
	{
		if (dy < 0)
		{
			swap(end.y, start.y);
			swap(end.x, start.x);
			dy = -dy;
			dx = -dx;
		}
		int d = dy - abs(2 * dx);
		int c1 = 2 * dy - abs(2 * dx);
		int c2 = -2 * abs(dx);

		int y = start.y;
		int x = start.x;
		while (y <= end.y)
		{
			SetPixel(hdc, x, y, color);
			if (d <= 0)
			{
				d += c1;
				x = (dx > 0) ? x + 1 : x - 1;

			}
			else  d += c2;
			y++;
		}
	}
}
void Line::DrawDDA(COLORREF color){
	int dx = end.x - start.x, dy = end.y - start.y;
	if (dx == 0 && dy == dx){
		SetPixel(hdc, start.x, start.y, color);
		return;
	}
	if (abs(dy) <= abs(dx)){
		if (start.x>end.x){
			swap(start.y, end.y);
			swap(start.x, end.x);
			dx *= -1;
			dy = end.y - start.y;
		}
		double slope = (double)dy / dx;
		int x = start.x;
		double y = start.y;
		while (x <= end.x)
		{
			SetPixel(hdc, x, round(y), color);
			x++;
			y += slope;

		}
	}
	else{
		if (start.y>end.y){
			swap(start.y, end.y);
			swap(start.x, end.x);
			dy *= -1;
			dx = end.x - start.x;
		}
		double slope = (double)dx / dy;
		double x = start.x;
		int y = start.y;
		while (y <= end.y)
		{
			SetPixel(hdc, round(x), y, color);
			y++;
			x += slope;
		}
	}
}
void Line::DrawDirect(COLORREF color)
{
	int dx = end.x - start.x, dy = end.y - start.y;
	if (dx == 0 && dy == dx){
		SetPixel(hdc, start.x, start.y, color);
		return;
	}
	if (abs(dy) <= abs(dx))
	{
		if (start.x>end.x){
			swap(start.y, end.y);
			swap(start.x, end.x);
			dx *= -1;
			dy = end.y - start.y;
		}
		double slope = (double)dy / dx;
		int x = start.x;
		double y = start.y;
		while (x <= end.x)
		{
			SetPixel(hdc, x, round(y), color);
			x++;
			y = round(start.y + (x - start.x) * (double)slope);
		}
	}
	else
	{
		if (start.y>end.y){
			swap(start.y, end.y);
			swap(start.x, end.x);
			dy *= -1;
			dx = end.x - start.x;
		}
		double slope = (double)dx / dy;
		double x = start.x;
		int y = start.y;
		while (y <= end.y)
		{
			SetPixel(hdc, round(x), y, color);
			y++;
			x = round(start.x + (y - start.y)*(double)slope);
		}
	}
}
Line::~Line()
{
}
