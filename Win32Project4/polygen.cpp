#include "stdafx.h"
#include "polygen.h"


polygon::polygon(vector<LPARAM> points,HDC hdc)
{
	this->points = points;
	this->hdc = hdc;
}

void polygon::draw(COLORREF)
{
	vector<Point> actualPoints;
	for (int i = 0; i < this->points.size(); i++)
	{
		actualPoints.push_back({ LOWORD(points[i]), HIWORD(points[i]) });
	}
	MoveToEx(hdc, actualPoints[0].x, actualPoints[0].y, NULL);
	LineTo(hdc, actualPoints[1].x, actualPoints[1].y);
	LineTo(hdc, actualPoints[2].x, actualPoints[2].y);
	LineTo(hdc, actualPoints[3].x, actualPoints[3].y);
	LineTo(hdc, actualPoints[0].x, actualPoints[0].y);
}

polygon::~polygon()
{
}
