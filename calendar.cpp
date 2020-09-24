#define STRICT
#include <windows.h>
#include <commctrl.h>
#include "calendar.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

char const * const myClass="MyCalendar";

HFONT hfontDlg;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow){
MSG msg;
WNDCLASSEX wcex={0};


INITCOMMONCONTROLSEX cc;
  cc.dwSize=sizeof(cc);
  cc.dwICC=ICC_DATE_CLASSES;
  InitCommonControlsEx(&cc);


//  InitCommonControls();

  wcex.cbSize=sizeof(WNDCLASSEX);
  wcex.lpfnWndProc=(WNDPROC)WndProc;
  wcex.hInstance=hInstance;
  wcex.hIcon=LoadIcon(hInstance,(LPCTSTR)"aaa");
  wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
  wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszClassName=myClass;
  wcex.hIconSm=LoadIcon(wcex.hInstance,(LPCTSTR)"aaa");
  RegisterClassEx(&wcex);

  hfontDlg=CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, VARIABLE_PITCH , "Times New Roman");
  if(!InitInstance (hInstance, nCmdShow))
    return FALSE;
  while (GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
  DeleteObject(hfontDlg);
  return msg.wParam;
  }


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
HWND hWnd,hWndChild;
RECT rect,clientRect,windowRect;

  hWnd=CreateWindow(myClass, "Year calendar", WS_DLGFRAME|WS_SYSMENU,
      CW_USEDEFAULT,  CW_USEDEFAULT, 160,55, NULL, NULL, hInstance, NULL);
  if(!hWnd)
    return FALSE;
  GetClientRect(hWnd,&clientRect);
  GetWindowRect(hWnd,&windowRect);

  hWndChild=CreateWindow(MONTHCAL_CLASS,"", WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_WEEKNUMBERS, 
     0,0,0,0, hWnd, NULL, hInstance, NULL);

// Get the size required to show an entire month.
  MonthCal_GetMinReqRect(hWndChild, &rect);
  SendMessage ( hWndChild, WM_SETFONT, (WPARAM)hfontDlg,TRUE);
  MonthCal_GetMinReqRect(hWndChild, &rect);
  SetWindowPos(hWndChild, NULL, 0,0,rect.right*6.1,rect.bottom*2,SWP_NOZORDER);
  SetWindowPos(hWnd, NULL, 0,0,rect.right*6.1+(windowRect.right-windowRect.left-clientRect.right),
    rect.bottom*2+(windowRect.bottom-windowRect.top-clientRect.bottom),SWP_NOZORDER|SWP_NOMOVE);


  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
  }


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  switch (message){
  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    }
  return 0;
  }

