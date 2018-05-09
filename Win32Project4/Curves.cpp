#include "stdafx.h"
#include "Curves.h"

Curves::Curves(vector<LPARAM> points, int choice, HDC hdc )
{
	this->hdc = hdc;
	this->algorithm = choice;
	this->points = points;
}

Vector4 operator *(Matrix4 M, Vector4& b)
{
	Vector4 res;  
	for (int i = 0; i<4; i++)   
		for (int j = 0; j<4; j++)    
			res[i] += M[i][j] * b[j]; 
	return res;
}
double Curves::DotProduct(Vector4& a, Vector4& b){
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]; 
}

void Curves::draw(COLORREF color)
{
	if (algorithm == 1)
	{
		Vector2 P0(LOWORD(points[0]), HIWORD(points[0]));
		Vector2 T0(LOWORD(points[1]), HIWORD(points[1]));
		Vector2 T1(LOWORD(points[2]), HIWORD(points[2]));
		Vector2 P1(LOWORD(points[3]), HIWORD(points[3]));
		this->DrawHermit(color,P0,T0,P1,T1);
	}
	else if (algorithm == 2)
	{
		this->DrawBezier(color);
	}
}
Vector4 Curves::GetHermiteCoeff(double x0, double s0, double x1, double s1) 
{
	static double H[16] = { 2, 1, -2, 1, -3, -2, 3, -1, 0, 1, 0, 0, 1, 0, 0, 0 }; 
	static Matrix4 basis(H);
	Vector4 v(x0, s0, x1, s1);
	return basis*v; 
}

void Curves::DrawHermit(COLORREF color,Vector2& P0,Vector2& T0,Vector2&P1,Vector2& T1) 
{
	
	Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x); 
	Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y); 
	double dt =(double) 1.0 / 30000.0;
	for (double t = 0; t <= 1; t += dt)  {
		Vector4 vt;   
		vt[3] = 1;
		for (int i = 2; i >= 0; i--)
			vt[i] =(double)vt[i+1]*t; 
		int x = round(DotProduct(xcoeff, vt));  
		int y = round(DotProduct(ycoeff, vt)); 
		if (t == 0)MoveToEx(hdc, x, y, NULL); else LineTo(hdc, x, y);
	}
}
void Curves::DrawBezier(COLORREF color)
{
	Vector2 P0(LOWORD(points[0]), HIWORD(points[0]));
	Vector2 P1(LOWORD(points[1]), HIWORD(points[1]));
	Vector2 P2(LOWORD(points[2]), HIWORD(points[2]));
	Vector2 P3(LOWORD(points[3]), HIWORD(points[3]));
	Vector2 T0(3 * (P1.x - P0.x), 3 * (P1.y - P0.y)); 
	Vector2 T1(3 * (P3.x - P2.x), 3 * (P3.y - P2.y)); 
	DrawHermit(color, P0, T0, P3, T1);
}
Curves::~Curves()
{
}
