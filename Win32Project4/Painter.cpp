#include "stdafx.h"
#include "Painter.h"


Painter::Painter()
{
	this->saved = false;
	notsavedLines = 0;
	notsavedShapes = 0;
	notsavesPolygons = 0;
}
 
void Painter::operate(HWND hwnd,int shape,HDC hdc , LPARAM first,LPARAM lParam,vector<LPARAM> &pointsForCurve)
{
	this->hdc = hdc;
	if (shape == 5){
		Clipping* clip = new Clipping();
		clip->clip(1, RGB(0, 0, 0), first, lParam, lines);
	}
	else if (shape == 1){
		Shape* circle = new Circle(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(0, 244, 255));
		shapes.push_back(circle);
		notsavedShapes++;
	}
	else if (shape == 2){
		Shape* circle = new Circle(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(0, 100, 255));
		shapes.push_back(circle);
		notsavedShapes++;
	}
	else if (shape == 6)
	{
		Shape* circle = new Circle(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(255, 0, 0));
		shapes.push_back(circle);
		notsavedShapes++;
	}
	else if (shape == 3)
	{
		Shape* line = new Line(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		int size= lines.size();
		line->draw(RGB(0, 100, 255));
		notsavedLines++;
	}
	else if (shape == 4)
	{
		Shape* line = new Line(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		line->draw(RGB(0, 244, 255));
		notsavedLines++;
	}

	else if (shape == 7)
	{
		Shape* line = new Line(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		line->draw(RGB(255, 0, 0));
		notsavedLines++;
	}
	else if (shape == 8)
	{
		Filling* filling = new Filling(hwnd);
		filling->fillBFS(hdc, { LOWORD(first), HIWORD(first) }, RGB(0, 0, 0));
		//filling->fillWithRecursion(hdc, { LOWORD(first), HIWORD(first) }, RGB(0, 0, 0)); //Stack overflow
		pointsForFill.push_back({ LOWORD(first), HIWORD(first) });
	}
	else if (shape == 9)
	{
		Shape* curve = new Curves(pointsForCurve, 1, hdc);
		curve->draw(RGB(0, 0, 255));
		shapes.push_back(curve);
		notsavedShapes++;
	}
	else if (shape == 10)
	{
		Shape* curve = new Curves(pointsForCurve, 2, hdc);
		curve->draw(RGB(0, 0, 0));
		shapes.push_back(curve);
		notsavedShapes++;
	}
	else if (shape == 11)
	{
		Clipping* clip = new Clipping();
		clip->clip(2, RGB(200, 13, 40), first, lParam, polygons);
	}
	else if (shape == 12)
	{
		Shape* Polygon = new polygon(pointsForCurve, hdc);
		Polygon->draw(RGB(0, 0, 12));
		polygons.push_back(Polygon);
		notsavesPolygons++;
	}
	else if (shape == 13)
	{
		this->saved = true;
		notsavedLines=0;
		notsavedShapes = 0;
		notsavesPolygons = 0;
	}
	else if (shape == 14)
	{
		Load* load = new Load();
		load->load(lines, polygons, shapes, pointsForFill,saved,notsavedLines, notsavesPolygons,notsavedShapes);
	}
}

Painter::~Painter()
{
}
