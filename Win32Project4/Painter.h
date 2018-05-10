#pragma once
#include "Shape.h"
#include "Circle.h"
#include <iostream>
#include <vector>
#include "Clipping.h"
#include "Filling.h"
#include "Curves.h"
#include "polygen.h"
#include "Load.h"
using namespace std;
class Painter
{
public:
	HDC hdc;
	bool saved;
	int notsavedLines;
	int notsavedShapes;
	int notsavesPolygons;
	vector<Point> pointsForFill;
	vector <Shape *> lines;
	vector <Shape*> shapes;
	vector<Shape*> polygons;
	Painter();
	void operate(HWND, int, HDC, LPARAM, LPARAM, vector<LPARAM>&);
	~Painter();
};

