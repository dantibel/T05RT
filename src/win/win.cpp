/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Raytracing project.
 *               Window functions implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include "win/win.h"
/* Class default constructor.
 * ARGUMENTS:
 *   - application instance handle
 *       HINSTANCE hInst;
 */
dart::win::win( HINSTANCE hInst ) : hWnd(nullptr), W(0), H(0), hInstance(hInst), IsFullScreen(FALSE), FullScreenSaveRect({}), MouseWheel(0), IsActive(FALSE)
{
  WNDCLASS wc;
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(win *);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = (WNDPROC)win::WinFunc;
  wc.lpszClassName = "RT window class name";
  wc.cbWndExtra = sizeof(win *);

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    exit(-1);
  }
} /* End of 'win' function */

/* Class destructor */
dart::win::~win( VOID )
{
} /* End of '~win' function */

/* Window message handle function (CALLBACK version).
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier (see WM_***):
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK dart::win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO *)lParam)->ptMinTrackSize.y =
      GetSystemMetrics(SM_CYCAPTION) * 8 +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO *)lParam)->ptMinTrackSize.x += 300;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
    if (Win != nullptr)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->W = (INT)(SHORT)LOWORD(lParam);
        Win->H = (INT)(SHORT)HIWORD(lParam);
        Win->OnSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));

        return 0;
      case WM_ACTIVATE:
        Win->IsActive = LOWORD(wParam) != WA_INACTIVE;
        Win->OnActivate((UINT)LOWORD(wParam),(HWND)(lParam),(BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return 0; //(LRESULT)Win->OnEraseBkgnd((HDC)wParam);
      case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        Win->OnPaint(hDC, &ps);
        EndPaint(hWnd, &ps);
        return 0;
      case WM_DRAWITEM:
        Win->OnDrawItem((INT)wParam, (DRAWITEMSTRUCT *)lParam);
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (INT)(SHORT)HIWORD(wParam),
                          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDBLCLK:
        Win->OnButtonDown(TRUE, (INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),(UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        Win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam),
                         (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        Win->OnButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), 
                         (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        Win->OnKeyDown((INT)(SHORT)LOWORD(wParam), (INT)(SHORT)HIWORD(wParam), 
                        (UINT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam));
        return 0;
      case WM_DROPFILES:
        Win->OnDropFiles((HDROP)wParam);
        return 0;
      case WM_NOTIFY:
        return Win->OnNotify((INT)wParam, (NMHDR *)lParam);
      case WM_COMMAND:
        Win->OnCommand((INT)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
        return 0;
      case WM_MENUSELECT:
        Win->OnMenuSelect((HMENU)lParam,
          (HIWORD(wParam) & MF_POPUP) ? 0L : (INT)LOWORD(wParam),
          (HIWORD(wParam) & MF_POPUP) ?
            GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L,
          (UINT)(((SHORT)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam)));
        return 0;

      case WM_INITMENUPOPUP:
        Win->OnInitMenuPopup((HMENU)wParam, (UINT)
          LOWORD(lParam), (BOOL)HIWORD(lParam));
        return 0;
      case WM_HSCROLL:
        Win->OnHScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_VSCROLL:
        Win->OnVScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_ENTERSIZEMOVE:
        Win->OnEnterSizeMove();
        return 0;
      case WM_EXITSIZEMOVE:
        Win->OnExitSizeMove();
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30); /// ?
        return 0;
      default:
        return Win->OnMessage(Msg, wParam, lParam);
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'win::WinFunc' function */

/* Window messsages loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::win::Run( VOID )
{
  MSG msg;
  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      /* Idle */
    }
  }
} /* End of 'dart::win::Run' function */

/* Switch window fullscreen mode function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::win::FlipFullScreen( VOID )
{
  if (IsFullScreen)
  {
    IsFullScreen = FALSE;

    /* Restore window position and size */
    SetWindowPos(hWnd, HWND_NOTOPMOST, FullScreenSaveRect.left, FullScreenSaveRect.top, FullScreenSaveRect.right - FullScreenSaveRect.left,
      FullScreenSaveRect.bottom - FullScreenSaveRect.top, SWP_NOOWNERZORDER);
  }
  else
  {
    HMONITOR hMon;
    MONITORINFOEX moninfo;
    RECT rc;

    IsFullScreen = TRUE;
 
    /* Save window rectangle */
    GetWindowRect(hWnd, &FullScreenSaveRect);

    /* Get closest monitor */
    hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    /* Expand window client area to full screen */
    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOOWNERZORDER);
  }
} /* End of 'dart::win::FlipFullScreen' function */

/* END OF 'win.cpp' FILE */
