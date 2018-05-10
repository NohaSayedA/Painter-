#pragma once
#include "Shape.h"
#include <iostream>
#include <vector>
using namespace std;
class polygon :
	public Shape
{
public:
	vector<LPARAM> points;
	polygon(vector<LPARAM>,HDC);
	void draw(COLORREF color);
	~polygon();
};

