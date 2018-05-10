#pragma once
#include <vector>
#include "Shape.h"
#include "Line.h"
using namespace std;
struct Vertex 
{
	double x,y;  
	Vertex(int x1=0,int y1=0)
	{ 
		x=x1;
		y=y1;  
	} 
};
typedef vector<Vertex> VertexList; 
typedef bool (*IsInFunc)(Vertex& v,int edge); 
typedef Vertex (*IntersectFunc)(Vertex& v1,Vertex& v2,int edge);
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
	void ClippingPolygons(COLORREF, LPARAM, LPARAM, vector<Shape*>&);
	outcode GetOutCode(Point, int, int, int, int);
	Point vintersected(int, Shape*);
	Point hintersected(int, Shape*);
	Shape* ClippingLine(COLORREF, Shape*, int, int, int, int);
	/*Vertex VIntersect(Vertex& v1, Vertex& v2, int xedge);
	Vertex HIntersect(Vertex& v1, Vertex& v2, int yedge);
	bool InLeft(Vertex& v, int edge);
	bool InRight(Vertex& v, int edge);
	bool InTop(Vertex& v, int edge);
	bool InBottom(Vertex& v, int edge);
	VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect) 
	{
		VertexList OutList;
		Vertex v1 = p[p.size() - 1];
		bool v1_in = In(v1, edge);  
		for (int i = 0; i<(int)p.size(); i++) 
		{
			Vertex v2 = p[i]; 
			bool v2_in = In(v2, edge);   
			if (!v1_in && v2_in)   
			{ 
				OutList.push_back(Intersect(v1, v2, edge));   
				OutList.push_back(v2);
			} 
			else if (v1_in && v2_in)  
				OutList.push_back(v2); 
			else if (v1_in)
				OutList.push_back(Intersect(v1, v2, edge));
			v1 = v2;   
			v1_in = v2_in;
		} 
		return OutList; 
	}
	void PolygonClip(Shape* polygon, int xleft, int ytop, int xright, int ybottom) 
	{
		VertexList vlist; 
		for (int i = 0; i<4; i++)
			vlist.push_back(Vertex(polygon->, p[i].y)); 
		vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
		vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect); 
		vlist = ClipWithEdge(vlist, xright, InRight, VIntersect); 
		vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
		Vertex v1 = vlist[vlist.size() - 1]; 
		for (int i = 0; i<(int)vlist.size(); i++)
		{ 
			Vertex v2 = vlist[i];  
			MoveToEx(hdc, Round(v1.x), Round(v1.y), NULL); 
			LineTo(hdc, Round(v2.x), Round(v2.y)); 
			v1 = v2;
		}
	}*/
	~Clipping();
};

