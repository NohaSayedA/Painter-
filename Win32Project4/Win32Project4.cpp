// Win32Project4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project4.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "menu.h"
#include "Shape.h"
#include "Circle.h"
#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LPARAM first;

vector<LPARAM> points;
//vector<Point> lines;
int numberofpoints = 0;
int shape = -1;
bool check = false;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT4, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT4));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
void DrawLineDDA(int XS, int YS, int XE, int YE, HDC  hdc, COLORREF color){
	int dx = XE - XS, dy = YE - YS;
	if (dx == 0 && dy == dx){
		SetPixel(hdc, XS, YS, color);
		return;
	}
	if (abs(dy) <= abs(dx)){
		if (XS>XE){
			swap(YS, YE);
			swap(XS, XE);
			dx *= -1;
			dy = YE - YS;
		}
		double slope = (double)dy / dx;
		int x = XS;
		double y = YS;
		while (x <= XE)
		{
			SetPixel(hdc, x, round(y), color);
			x++;
			y += slope;

		}
	}
	else{
		if (YS>YE){
			swap(YS, YE);
			swap(XS, XE);
			dy *= -1;
			dx = XE - XS;
		}
		double slope = (double)dx / dy;
		double x = XS;
		int y = YS;
		while (y <= YE)
		{
			SetPixel(hdc, round(x), y, color);
			y++;
			x += slope;
		}
	}
}
union outcode
{
	unsigned All : 4;
	struct 
	{
		unsigned left : 1, top : 1, right : 1, bottom : 1;
	};
};
void DrawLineMidPoint(HDC hdc, int xs, int ys, int xe, int ye,COLORREF color){
	int dx = xe - xs;
	int dy = ye - ys;
	if (abs(dy) <= abs(dx)) // slope less than 1
	{
		if (xe < xs)
		{
			swap(xe, xs);
			swap(ye, ys);
			dx = -dx;
			dy = -dy;
		}
		int d = dx - abs(2 * dy);
		int c1 = 2 * dx - abs(2 * dy);
		int c2= -2 * abs(dy);
		int x = xs;
		int y = ys;
		while (x<=xe)
		{
			SetPixel(hdc, x, y, color);
			if (d <= 0)
			{
				d += c1;
				//to check if y decrease or increase
				y = (dy > 0) ? y + 1 : y - 1;
			}
			else  d += c2;
			x++;

		}
	}
	else
	{
		if (dy < 0)
		{
			swap(ye, ys);
			swap(xe, xs);
			dy = -dy;
			dx = -dx;
		}
		int d = dy - abs(2 * dx);
		int c1 = 2 * dy - abs(2 * dx);
		int c2 = -2 * abs(dx);

		int y = ys;
		int x = xs;
		while (y<=ye)
		{
			SetPixel(hdc, x, y, color);
			if (d <= 0)
			{
				d += c1;
				x = (dx > 0) ? x + 1 : x - 1;

			}
			else  d += c2;
			y++;
		}
	}
}
/*void Draw8Points(int x, int y, int xc, int yc, COLORREF color, HDC hdc)
{
	SetPixel(hdc, xc + x, yc + y, color);
	SetPixel(hdc, xc - x, yc + y, color);
	SetPixel(hdc, xc - x, yc - y, color);
	SetPixel(hdc, xc + x, yc - y, color);
	SetPixel(hdc, xc + y, yc + x, color);
	SetPixel(hdc, xc - y, yc + x, color);
	SetPixel(hdc, xc - y, yc - x, color);
	SetPixel(hdc, xc + y, yc - x, color);
}
void DrawCircleCartesian(HDC hdc, int xc, int yc, int xr, int yr, COLORREF color)
{
	int R = sqrt(pow((xr - xc), 2) + pow((yr - yc), 2));
	int x = 0, y = R;
	Draw8Points(x, y, xc, yc, color, hdc);
	while (x < y)
	{
		x++;
		y = sqrt(pow(R, 2) - pow(x, 2));
		Draw8Points(x, y, xc, yc, color, hdc);
	}
	}*//**/
/*outcode GetOutCode(int x, int y, int left, int top, int right, int bottom)
{
	outcode Out;
	Out.All = 0;
	if (x < left)
		Out.left = 1;
	else if (x>right)
		Out.right = 1;
	if (y > bottom)
		Out.bottom = 1;
	else if (y< top)
		Out.top = 1;
	return Out;
}

Point vintersected(int edge, int xs, int ys, int xe, int ye)
{
	Point n;
	n.x = edge;
	double slope = (double)(ye - ys) / (xe - xs);
	n.y = ys + (edge - xs)* (double)slope;	
	return n;
}
Point hintersected(int edge, int xs, int ys, int xe, int ye)
{
	Point n;
	n.y = edge;
	double slope = (double)(xe - xs) / (ye - ys);
	n.x = xs + (edge - ys)* (double)slope;
	return n;
}*/
void ClippingLine(HDC hdc, COLORREF color, int xs, int ys, int xe, int ye, int left, int right, int top, int bottom)
{
	/*outcode out1 = GetOutCode(xs, ys, left, top, right, bottom);
	outcode out2 = GetOutCode(xe, ye, left, top, right, bottom);
	while ((out1.All != 0 || out2.All != 0) && !(out1.All&out2.All))
	{
		if (out1.All != 0)
		{
			Point N;
			if (out1.left)
				 N= vintersected(left, xs, ys, xe, ye);
			else if (out1.right)
				 N=vintersected(right, xs, ys, xe, ye);
			else if (out1.top)
				 N=hintersected(top, xs, ys, xe, ye);
			else if (out1.bottom)
				 N=hintersected(bottom, xs, ys, xe, ye);
			xs = N.x; 
			ys = N.y;
			out1 = GetOutCode(xs, ys, left, top, right, bottom);
		}
		else if (out2.All != 0)
		{
			Point N;
			if (out2.left)
				N = vintersected(left, xs, ys, xe, ye);
			else if (out2.right)
				N = vintersected(right, xs, ys, xe, ye);
			else if (out2.top)
				N = hintersected(top, xs, ys, xe, ye);
			else if (out2.bottom)
				N = hintersected(bottom, xs, ys, xe, ye);
			xe = N.x;
			ye = N.y;
			out2 = GetOutCode(xe, ye, left, top, right, bottom);
		}
	}
	if (out1.All == 0 && out2.All == 0)
	{
		DrawLineMidPoint(hdc, xs, ys, xe, ye, color);
		Point start;
		start.x = xs;
		start.y = ys;
		Point end;
		end.x = xe;
		end.y = ye;
		lines.push_back(start);
		lines.push_back(end);
	}*/
}
void ClippingLines(HDC hdc, COLORREF color)
{
	/*int left = LOWORD(points.front());
	points.erase(points.begin());
	int right = LOWORD(points.front());
	points.erase(points.begin());
	int top = HIWORD(points.front());
	points.erase(points.begin());
	int bottom = HIWORD(points.front());
	int size = lines.size();
	while (size)
	{
		Point start = lines.front();
		lines.erase(lines.begin());
		size--;
		Point end = lines.front();
		lines.erase(lines.begin());
		size--;
		DrawLineDDA(start.x, start.y, end.x, end.y, hdc, RGB(255, 255, 255));
		ClippingLine(hdc, color, start.x, start.y, end.x, end.y, left, right, top, bottom);
	}*/
}
/*void DrawCircleMidPoint(HDC hdc, int xc, int yc, int xr, int yr, COLORREF color)
{
	int R = sqrt(pow((xr - xc), 2) + pow((yr - yc), 2));
	int x = 0, y = R;
	int d = 1 - R;
	//Draw8Points(x, y, xc, yc, color, hdc);
	while (x < y)
	{
		if (d < 0)		d += (2*x + 3);
		else{
			d += 2*x - 2*y + 5;
			y--;
		}
		x++;
		//Draw8Points(x, y, xc, yc, color, hdc);

	}

}*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case Circle_Cartesian:
			shape = 1;
			break;
		case Circle_MidPoint:
			shape = 2;
			break;
		case Line_DDA:
			shape = 3;
			break;
		case Line_MidPoint:
			shape = 4;
			break;
		case Line_Clipping:
			shape = 5;
			break;
		case Circle_Polar:
			shape = 6;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		if (shape == 5)
		{
			if (points.size() == 3)
			{
				hdc = GetDC(hWnd);
				points.push_back(lParam);
				ClippingLines(hdc, RGB(0, 0, 240));
				points.clear();
			}
			else
				points.push_back(lParam);
		}
		else
		{
			if (!check)
			{
				check = true;
				first = lParam;
			}
			else
			{
				check = false;
				hdc = GetDC(hWnd);
				if (shape == 1){
					//DrawCircleCartesian(hdc, LOWORD(first), HIWORD(first), LOWORD(lParam), HIWORD(lParam), RGB(0, 244, 255));
					Shape* circle = new Circle(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					circle->draw(RGB(0, 244, 255));
				}
				else if (shape == 2){
					//DrawCircleMidPoint(hdc, LOWORD(first), HIWORD(first), LOWORD(lParam), HIWORD(lParam), RGB(200, 0, 255));
				}
				else if (shape == 3)
				{
					/*DrawLineDDA(LOWORD(first), HIWORD(first), LOWORD(lParam), HIWORD(lParam), hdc, RGB(0, 0, 255));
					Point start;
					start.x = LOWORD(first);
					start.y = HIWORD(first);
					Point end;
					end.x = LOWORD(lParam);
					end.y = HIWORD(lParam);
					lines.push_back(start);
					lines.push_back(end);*/
				}
				else if (shape == 4)
				{
					/*DrawLineMidPoint(hdc, LOWORD(first), HIWORD(first), LOWORD(lParam), HIWORD(lParam), RGB(255, 0, 0));
					Point start;
					start.x = LOWORD(first);
					start.y = HIWORD(first);
					Point end;
					end.x = LOWORD(lParam);
					end.y = HIWORD(lParam);
					lines.push_back(start);
					lines.push_back(end);*/
				}
				else if (shape == 6)
				{
					Shape* circle = new Circle(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					
					circle->draw(RGB(255, 0, 0));
				}
			}
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
