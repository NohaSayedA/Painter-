// Win32Project4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project4.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "menu.h"
#include "Painter.h"
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
Painter* painter;
vector<Point> lines;
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
	painter = new Painter();
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



//[
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
/*union outcode
{
	unsigned All : 4;
	struct 
	{
		unsigned left : 1, top : 1, right : 1, bottom : 1;
	};
};
outcode GetOutCode(int x, int y, int left, int top, int right, int bottom)
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
}
void ClippingLine(HDC hdc, COLORREF color, int xs, int ys, int xe, int ye, int left, int right, int top, int bottom)
{
	outcode out1 = GetOutCode(xs, ys, left, top, right, bottom);
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
		Line l;
		l.hdc = hdc;
		l.start = { xs, ys };
		l.end = { xe, ye };
		l.DrawDDA(RGB(0, 255, 255));
		Point start;
		start.x = xs;
		start.y = ys;
		Point end;
		end.x = xe;
		end.y = ye;
		lines.push_back(start);
		lines.push_back(end);
	}
}
void ClippingLines(HDC hdc, COLORREF color,LPARAM lparam)
{
	int left = LOWORD(first);
	int right = LOWORD(lparam);
	int top = HIWORD(first);
	int bottom = HIWORD(lparam);
	int size = lines.size();
	while (size)
	{
		Point start = lines.front();
		lines.erase(lines.begin());
		size--;
		Point end = lines.front();
		lines.erase(lines.begin());
		size--;
		Line l;
		l.hdc = hdc;
		l.start = start;
		l.end = end;
		l.DrawDDA(RGB(255, 255, 255));
		ClippingLine(hdc, color, start.x, start.y, end.x, end.y, left, right, top, bottom);
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
		case Line_Cartesian:
			shape = 7;
			break;
		case filling_ID:
			shape = 8;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		
		
			if (!check)
			{
				check = true;
				first = lParam;
				if (shape == 8)
				{
					check = false;
					hdc = GetDC(hWnd);
					painter->operate(hWnd,shape, hdc, first, NULL);
				}
			}
			else
			{
				check = false;
				hdc = GetDC(hWnd);
				painter->operate(hWnd,shape,hdc,first,lParam);
				/*hdc = GetDC(hWnd);
				if (shape == 5){
					ClippingLines(hdc, RGB(0, 100, 200), lParam);
				}
				else if (shape == 1){
					Shape* circle = new Circle(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					circle->draw(RGB(0, 244, 255));
				}
				else if (shape == 2){
					Shape* circle = new Circle(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					circle->draw(RGB(0, 100, 255));
				}
				else if (shape == 6)
				{
					Shape* circle = new Circle(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					circle->draw(RGB(255, 0, 0));
				}
				else if (shape == 3)
				{
					Point start = { LOWORD(first), HIWORD(first) };
					Point end = { LOWORD(lParam), HIWORD(lParam) };
					lines.push_back(start);
					lines.push_back(end);
					Shape* line = new Line(hdc, 1, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					line->draw(RGB(0, 100, 255));
				}
				else if (shape == 4)
				{
					Shape* line = new Line(hdc, 2, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					line->draw(RGB(0, 244, 255));
				}

				else if (shape == 7)
				{
					Shape* line = new Line(hdc, 3, { LOWORD(first), HIWORD(first) }, { LOWORD(lParam), HIWORD(lParam) });
					line->draw(RGB(255, 0, 0));
				}*/
			}
		break;
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
