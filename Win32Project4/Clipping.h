#pragma once
#include <vector>
#include "Shape.h"
#include "Line.h"
using namespace std;
union outcode
{
	unsigned All : 4;
	struct
	{
		unsigned left : 1, top : 1, right : 1, bottom : 1;
	};
};

class Clipping 
{
public:
	Clipping();
	int algorithm;
	void clip(int, COLORREF, LPARAM, LPARAM, vector<Shape*>&);
	void ClippingLines(COLORREF, LPARAM, LPARAM, vector<Shape*>&);
	outcode GetOutCode(Point, int, int, int, int);
	Point vintersected(int, Shape*);
	Point hintersected(int, Shape*);
	Shape* ClippingLine(COLORREF, Shape*, int, int, int, int);
	~Clipping();
};

