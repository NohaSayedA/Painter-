#include "stdafx.h"
#include "Clipping.h"


Clipping::Clipping()
{
}
void Clipping::clip(int choice,COLORREF color,LPARAM first, LPARAM lParam, vector<Shape*>& lines)
{
	if (choice == 1)
	{
		this->ClippingLines(color, first, lParam, lines);
	}
}
outcode Clipping::GetOutCode(Point point, int left, int top, int right, int bottom)
{
	outcode Out;
	Out.All = 0;
	if (point.x < left)
		Out.left = 1;
	else if (point.x>right)
		Out.right = 1;
	if (point.y > bottom)
		Out.bottom = 1;
	else if (point.y< top)
		Out.top = 1;
	return Out;
}

Point Clipping:: vintersected(int edge, Shape* line)
{
	Point n;
	n.x = edge;
	double slope = (double)(line->end.y - line->start.y) / (line->end.x - line->start.x);
	n.y = line->start.y + (edge - line->start.x)* (double)slope;
	return n;
}
Point Clipping:: hintersected(int edge,Shape* line)
{
	Point n;
	n.y = edge;
	double slope = (double)(line->end.x -line->start.x) / (line->end.y - line->start.y);
	n.x = line->start.x + (edge - line->start.y)* (double)slope;
	return n;
}
Shape* Clipping:: ClippingLine(COLORREF color, Shape* line, int left, int right, int top, int bottom)
{
	outcode out1 = GetOutCode(line->start, left, top, right, bottom);
	outcode out2 = GetOutCode(line->end, left, top, right, bottom);
	while ((out1.All != 0 || out2.All != 0) && !(out1.All&out2.All))
	{
		if (out1.All != 0)
		{
			Point N;
			if (out1.left)
				N = vintersected(left, line);
			else if (out1.right)
				N = vintersected(right,line);
			else if (out1.top)
				N = hintersected(top, line);
			else if (out1.bottom)
				N = hintersected(bottom, line);
			line->start.x = N.x;
			line->start.y = N.y;
			out1 = GetOutCode(line->start, left, top, right, bottom);
		}
		else if (out2.All != 0)
		{
			Point N;
			if (out2.left)
				N = vintersected(left, line);
			else if (out2.right)
				N = vintersected(right, line);
			else if (out2.top)
				N = hintersected(top, line);
			else if (out2.bottom)
				N = hintersected(bottom, line);
			line->end.x = N.x;
			line->end.y = N.y;
			out2 = GetOutCode(line->end, left, top, right, bottom);
		}
	}
	if (out1.All == 0 && out2.All == 0)
	{
		line->draw(RGB(0, 255, 255));
		return line;
	}
	return NULL;
}
void Clipping:: ClippingLines(COLORREF color,LPARAM first, LPARAM lparam,vector<Shape*>& lines)
{
	int left = LOWORD(first);
	int right = LOWORD(lparam);
	int top = HIWORD(first);
	int bottom = HIWORD(lparam);
	int size = lines.size();
	while (size)
	{
		Shape* line = lines.front();
		lines.erase(lines.begin());
		size--;
		line->draw(RGB(255,255,255));
		line=ClippingLine(color,line, left, right, top, bottom);
		if (line == NULL)
			continue;
		lines.push_back(line);
	}
}
void Clipping::ClippingPolygons(COLORREF color, LPARAM first, LPARAM lparam, vector<Shape*>& polygons)
{
	int left = LOWORD(first);
	int right = LOWORD(lparam);
	int top = HIWORD(first);
	int bottom = HIWORD(lparam);
	int size = polygons.size();
	while (size)
	{
		Shape* polygon = polygons.front();
		polygons.erase(polygons.begin());
		size--;
		polygon->draw(RGB(255, 255, 255));
		/*polygon = ClippingPolygon(color, line, left, right, top, bottom);
		if (line == NULL)
			continue;
		lines.push_back(line);*/
	}
}
/*
Vertex Clipping:: VIntersect(Vertex& v1, Vertex& v2, int xedge)
{
	Vertex res;
	res.x = xedge;
	res.y = v1.y + (xedge - v1.x)*(v2.y - v1.y) / (v2.x - v1.x);
	return res;
}
Vertex Clipping:: HIntersect(Vertex& v1, Vertex& v2, int yedge)
{
	Vertex res;
	res.y = yedge;
	res.x = v1.x + (yedge - v1.y)*(v2.x - v1.x) / (v2.y - v1.y);
	return res;
}
bool Clipping:: InLeft(Vertex& v, int edge)
{
	return v.x >= edge;
}
bool Clipping:: InRight(Vertex& v, int edge)
{
	return v.x <= edge;
}
bool Clipping:: InTop(Vertex& v, int edge)
{
	return v.y >= edge;
}
bool Clipping:: InBottom(Vertex& v, int edge)
{
	return v.y <= edge;
}*/
Clipping::~Clipping()
{
}
