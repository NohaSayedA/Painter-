#pragma once
#include <vector>
#include "Shape.h"
#include <iostream>
using namespace std;
class Load
{
public:
	Load();
	void load(vector<Shape*>,vector<Shape*> , vector<Shape*> , vector<Point>,bool,int,int,int);
	~Load();
};

