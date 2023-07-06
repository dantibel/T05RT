/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.h
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
#ifndef __win_h_
#define __win_h_

#include <windows.h>

#include "def.h"

namespace dart
{
  /* Window base handle class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle

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
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

  private:
    BOOL IsFullScreen;       // Fullscreen mode flag
    RECT FullScreenSaveRect; // Fullscreen mode window rect
    INT MouseWheel;          // Mouse input value

  public:
    BOOL IsActive; // Is window active flag

    /* Class default constructor.
     * ARGUMENTS:
     *   - application instance handle
     *       HINSTANCE hInst;
     */
    win( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Class destructor */
    virtual ~win( VOID );

    virtual VOID Run( VOID );
    VOID FlipFullScreen( VOID );

  private:
    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    virtual BOOL OnCreate( CREATESTRUCT *CS );
    virtual VOID OnDestroy( VOID );
    virtual BOOL OnEraseBkgnd( HDC hDC );
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps );
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys );
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys );
    virtual VOID OnKeyDown( UINT vk, BOOL fDown, INT cRepeat, UINT flags );
    virtual VOID OnSize( UINT State, INT W, INT H );
    virtual VOID OnTimer( INT Id );
    virtual LRESULT OnClose( VOID );
    virtual VOID OnDropFiles( HDROP hDrop );
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead );
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags);
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnExitSizeMove( VOID );
    virtual VOID OnEnterSizeMove( VOID );
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );
  }; /* End of 'win' class */
} /* end of 'dart' namespase */
#endif // __win_h_

/* END OF 'win.h' FILE */
