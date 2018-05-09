#include "stdafx.h"
#include "Painter.h"


Painter::Painter()
{
}
 
void Painter::operate(HWND hwnd,int shape,HDC hdc , LPARAM first,LPARAM lParam)
{
	
	this->hdc = hdc;
	if (shape == 5){
		Clipping* clip = new Clipping();
		clip->clip(1, RGB(0, 0, 0), first, lParam, lines);
	}
	else if (shape == 1){
		Shape* circle = new Circle(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(0, 244, 255));
	}
	else if (shape == 2){
		Shape* circle = new Circle(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(0, 100, 255));
	}
	else if (shape == 6)
	{
		Shape* circle = new Circle(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		circle->draw(RGB(255, 0, 0));
	}
	else if (shape == 3)
	{
		Shape* line = new Line(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		int size= lines.size();
		line->draw(RGB(0, 100, 255));
	}
	else if (shape == 4)
	{
		Shape* line = new Line(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		line->draw(RGB(0, 244, 255));
	}

	else if (shape == 7)
	{
		Shape* line = new Line(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
		this->lines.push_back(line);
		line->draw(RGB(255, 0, 0));
	}
	else if (shape == 8)
	{
		Filling* filling = new Filling(hwnd);
		filling->fillBFS(hdc, { LOWORD(first), HIWORD(first) }, RGB(0, 0, 0));
		//filling->fillWithRecursion(hdc, { LOWORD(first), HIWORD(first) }, RGB(0, 0, 0)); //Stack overflow
	}
}

Painter::~Painter()
{
}
