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
vector<LPARAM> pointsForCurve;
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
		case Curve_Hermit:
			shape = 9;
			break;
		case Curve_Bezier:
			shape = 10;
			break;
		case Polygon_Clipping:
			shape = 11;
			break;
		case Polygon_Draw:
			shape = 12;
			break;
		case Save_ID:
			shape = 13;
			break; 
		case Load_ID:
			shape = 14;
			break;
		case Close:
			PostQuitMessage(0);
		}
		break;

	case WM_LBUTTONDOWN:
		if (shape == 13 || shape == 14)
		{
			hdc = GetDC(hWnd);
			painter->operate(hWnd, shape, hdc, NULL, NULL, pointsForCurve);
		}
		if (shape == 9||shape==10||shape==12)
		{
			pointsForCurve.push_back(lParam);
			if (pointsForCurve.size() == 4)
			{
				hdc = GetDC(hWnd);
				painter->operate(hWnd, shape, hdc, first, NULL,pointsForCurve);
				pointsForCurve.clear();
			}
		}
		else if (!check)
		{
			check = true;
			first = lParam;
			if (shape == 8)
			{
				check = false;
				hdc = GetDC(hWnd);
				painter->operate(hWnd,shape, hdc, first, NULL,pointsForCurve);
			}
		}
		else
		{
			check = false;
			hdc = GetDC(hWnd);
			painter->operate(hWnd,shape,hdc,first,lParam,pointsForCurve);
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
