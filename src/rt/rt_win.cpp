/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_rt_win.cpp
 * PURPOSE     : Raytracing project.
 *               rt_window functions implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 25.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include <thread>

#include "rt/rt.h"
#include "rt/shapes/sphere.h"
#include "rt/shapes/plane.h"
#include "rt/shapes/cylinder.h"
#include "rt/shapes/cube.h"

/* Class default constructor.
 * ARGUMENTS:
 *   - application instance handle
 *       HINSTANCE hInst;
 */
dart::rt::rt( HINSTANCE hInst ) : win(hInst), Frame(600, 400), Camera(), Scene()
{
  hWnd = CreateWindow("RT window class name", "DB6's window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT, Frame.W, Frame.H,
    nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));

  Camera.Set(dart::vec3(20, 20, 20), dart::vec3(0), dart::vec3(0, 1, 0));
  Camera.Resize(Frame.W, Frame.H);

#if 0
  Scene <<
    new sphere(vec3(5, 0, 0), 1, SOLID_MTL(vec3(1, 0, 0))) <<
    new sphere(vec3(0, 5, 0), 1, SOLID_MTL(vec3(0, 1, 0))) <<
    new sphere(vec3(0, 0, 5), 1, SOLID_MTL(vec3(0, 0, 1))) <<
    new cube(vec3(-1), vec3(1), SOLID_MTL(vec3(1))) <<
    new plane(vec3(1, 5, 0), vec3(0, 5, 0), vec3(0, 5, 1), SOLID_MTL(vec3(.8))) <<
    new direct(vec3(1, 1, 0), vec3(1));
#endif

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
} /* End of 'dart::rr::rt' function */


/* Class destructor */
dart::rt::~rt( VOID )
{
  DestroyWindow(hWnd);
  //delete this;
} /* End of 'dart::rt::~rt' function */

/* rt_window messsages loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::rt::Run( VOID )
{
  MSG msg;

///  std::thread WinTh(
///    [&msg]( VOID )
///    {
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
///    });
} /* End of 'dart::rt::Run' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL dart::rt::OnCreate( CREATESTRUCT *CS )
{
  HDC hDC = GetDC(hWnd);
  Frame.hMemDC = CreateCompatibleDC(hDC);
  Frame.CreateDIB(hDC);
  BitBlt(hDC, W / 2 - Frame.W / 2, H / 2 - Frame.H / 2,
    W / 2 + Frame.W / 2, H / 2 + Frame.H / 2, Frame.hMemDC, 0, 0, SRCCOPY);
  ReleaseDC(hWnd, hDC);

  SetTimer(hWnd, 47, 0, nullptr);
  return TRUE;
} /* End of 'dart::rt_win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::rt::OnDestroy( VOID )
{
  ReleaseDC(hWnd, Frame.hMemDC);
  DeleteObject(Frame.hBm);
  KillTimer(hWnd, 47);
  PostQuitMessage(47);
} /* End of 'dart::rt_win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID dart::rt::OnSize( UINT State, INT W, INT H )
{
  HDC hDC = GetDC(hWnd);
  //Frame.Resize(W, H);
  Frame.CreateDIB(hDC);
  ReleaseDC(hWnd, hDC);
  InvalidateRect(hWnd, nullptr, FALSE);
} /* End of 'dart::rt_win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL dart::rt::OnEraseBkgnd( HDC hDC )
{
  return TRUE;
} /* End of 'dart::rt_win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID dart::rt::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  Scene.Render(Camera, Frame);
  BitBlt(hDC, W / 2 - Frame.W / 2, H / 2 - Frame.H / 2,
    W / 2 + Frame.W / 2, H / 2 + Frame.H / 2, Frame.hMemDC, 0, 0, SRCCOPY);
} /* End of 'dart::rt_win::OnPaint' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID dart::rt::OnTimer( INT Id )
{
  Scene.Timer.Response();
  InvalidateRect(hWnd, nullptr, FALSE);
  UpdateWindow(hWnd);
} /* End of 'dart::rt::OnTimer' function */

/* WM_HSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptrptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID dart::rt::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'dart::rt_win::OnHScroll' function */

/* WM_VSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptrptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID dart::rt::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'dart::rt_win::OnVScroll' function */

/* WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP window messages handle function.
 * ARGUMENTS:
 *   - mouse position:
 *       INT X, INT Y;
 *   - down keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID dart::rt::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'dart::rt::OnButtonUp' function */

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - down keys:
 *       UINT vk;
 * RETURNS: None.
 */
VOID dart::rt::OnKeyDown( UINT vk, BOOL fDown, INT cRepeat, UINT flags )
{
  switch (vk)
  {
  case VK_ESCAPE:
    DestroyWindow(hWnd);
    break;
  case 'S':
    Frame.Save();
    break;
  case VK_SPACE:
    Scene.Timer.IsPause = !Scene.Timer.IsPause;
    break;
  case VK_F11:
    FlipFullScreen();
    break;
  case '1':
    if (Scene.CamDist > 5)
    Scene.CamDist -= .3;
    break;
  case '2':
    if (Scene.CamDist < 25)
    Scene.CamDist += .3;
    break;
  }
} /* End of 'dart::rt::OnKeyDown' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT dart::rt::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  if (Msg == WM_KEYDOWN)
  {
    if (wParam == VK_ESCAPE)
      DestroyWindow(hWnd);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'dart::rt_win::OnMessage' function */

/* END OF 'rt_rt_win.cpp' FILE */
