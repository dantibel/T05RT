/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_win_msg.cpp
 * PURPOSE     : Raytracing project.
 *               Window message crackers implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include "rt/rt.h"

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
   Frame.Resize(W, H);
#if 1
  HDC hDC = GetDC(hWnd);
  Frame.CreateDIB(hWnd, hDC);
  ReleaseDC(hWnd, hDC);
#endif
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
  //BitBlt(hDC, 0, 0, Frame.GetH(), Frame.GetW(), Frame.hMemDC, 0, 0, SRCCOPY);
} /* End of 'dart::rt_win::OnPaint' function */ 

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
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'dart::rt_win::OnMessage' function */

/* END OF 'rt_win_msg.cpp' FILE */
