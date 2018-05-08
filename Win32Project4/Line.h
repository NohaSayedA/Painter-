#include "Shape.h"

class Line : public Shape
{
public:
	Point start, end;
	Line();
	Line(HDC, int, Point, Point);
	void draw(COLORREF);
	void DrawMidPoint(COLORREF);
	void DrawDDA(COLORREF);
	void DrawDirect(COLORREF);
	~Line();
};
