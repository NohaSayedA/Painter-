#include "stdafx.h"
#include "Filling.h"

Filling::Filling(HWND hwnd)
{
	this->hwnd = hwnd;
	RECT rect;
	if (GetClientRect(hwnd, &rect))
	{
		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;
	}
}
void Filling::fillBFS(HDC hdc, Point point, COLORREF color)
{
	vector<Point> points;
	points.push_back(point);
	while (points.size()!=0)
	{
		point = points.front();
		points.erase(points.begin());
		if (point.x<0 || point.x>width || point.y > height || point.y < 0)
			continue;
		if (GetPixel(hdc, point.x, point.y) != RGB(255, 255, 255))
			continue;
		SetPixel(hdc, point.x, point.y, color);
		points.push_back({ point.x + 1, point.y });
		points.push_back({ point.x - 1, point.y });
		points.push_back({ point.x , point.y + 1});
		points.push_back({ point.x , point.y - 1});
	}
}
void Filling::fillWithRecursion(HDC hdc, Point point,COLORREF color)
{
	if (point.x<0 || point.x>width || point.y > height || point.y < 0)
		return;
	if (GetPixel(hdc, point.x, point.y) != RGB(255, 255, 255))
		return;
	SetPixel(hdc, point.x, point.y, color);
	fillWithRecursion(hdc, { point.x + 1, point.y }, color);
	fillWithRecursion(hdc, { point.x, point.y - 1 }, color);
	fillWithRecursion(hdc, { point.x, point.y + 1 }, color);
	fillWithRecursion(hdc, { point.x - 1, point.y }, color);
}
Filling::~Filling()
{
}
