/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_win.h
 * PURPOSE     : Raytracing project.
 *               Window base class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __rt_win_h_
#define __rt_win_h_

#include "win/win.h"
#include "rt/timer.h"
#include "rt/scene.h"

namespace dart
{
  /* Ray trayccing scene window handle class */
  class rt : public win
  {
  public:
    /* Class default constructor.
     * ARGUMENTS:
     *   - application instance handle
     *       HINSTANCE hInst;
     */
    rt( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Class destructor */
    ~rt( VOID );

    /* rt_window messsages loop function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Run( VOID ) override;

    dart::frame Frame;   // Current frame
    dart::scene Scene;   // Ray tracing scene
    dart::camera Camera; // Scene camera

    /* Resize scene function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      Frame.Resize(NewW, NewH);
      Camera.Resize(NewW, NewH);
      InvalidateRect(hWnd, nullptr, FALSE);
    } /* End of 'Resize' function */

  private:
    // message cracks

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS ) override;

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID ) override;

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H ) override;

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC ) override;

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps ) override;

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id ) override;

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
    VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos ) override;

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
    VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos ) override;

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - down keys:
     *       UINT vk;
     * RETURNS: None.
     */
    VOID OnKeyDown( UINT vk, BOOL fDown, INT cRepeat, UINT flags ) override;

    /* WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP window messages handle function.
     * ARGUMENTS:
     *   - mouse position:
     *       INT X, INT Y;
     *   - down keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys ) override;

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
    LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) override;
  }; /* End of 'rt_win' class */
} /* end of 'dart' namespase */


#endif // __rt_win_h_

/* END OF 'rt_win.h' FILE */
