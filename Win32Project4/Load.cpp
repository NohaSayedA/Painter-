#include "stdafx.h"
#include "Load.h"


Load::Load()
{

}

void Load::load(vector<Shape*> lines, vector<Shape*> polygons, vector<Shape*> shapes, vector<Point> fillingPoints,bool saved,int notsavedLines, int notsavedPolygons, int notsavedShapes)
{
	if (saved == false)
		return;
	for (vector<Shape*>::iterator it = lines.begin(); it != lines.end()-notsavedLines; ++it){
		Shape * cur = *it;
		cur->draw(RGB(0, 0, 0));
	}
	for (vector<Shape*>::iterator it = polygons.begin(); it != polygons.end()-notsavedPolygons; ++it){
		Shape * cur = *it;
		cur->draw(RGB(0, 0, 0));
	}
	for (vector<Shape*>::iterator it = shapes.begin(); it != shapes.end()-notsavedShapes; ++it){
		Shape * cur = *it;
		cur->draw(RGB(0, 0, 0));
	}
}
Load::~Load()
{
}
