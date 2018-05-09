#include "Shape.h"

class Line : public Shape
{
public:
	
	Line();
	Line(HDC, int, Point, Point);
	void draw(COLORREF);
	void DrawMidPoint(COLORREF);
	void DrawDDA(COLORREF);
	void DrawDirect(COLORREF);
	~Line();
};
