/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win_msg.cpp
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
#include "win/win.h"

/* WM_GETMINMAXINFO window message handle function.
 * ARGUMENTS:
 *   - structure with window minimun and maximun size data:
 *       MINMAXINFO *MinMax;
 * RETURNS: None.
 */
VOID dart::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
} /* End of 'dart::win::OnGetMinMaxinfo' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL dart::win::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'dart::win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::win::OnDestroy( VOID )
{
} /* End of 'dart::win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID dart::win::OnSize( UINT State, INT W, INT H )
{
} /* End of 'dart::win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL dart::win::OnEraseBkgnd( HDC hDC )
{
  return TRUE;
} /* End of 'dart::win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID dart::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
} /* End of 'dart::win::OnPaint' function */ 


/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID dart::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'dart::win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID dart::win::OnTimer( INT Id ) 
{

} /* End of 'dart::win::OnTimer' function */

/* WM_CLOSE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
LRESULT dart::win::OnClose( VOID )
{
  return 0;
} /* End of 'OnClose' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID dart::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'dart::win::OnMouseWheel' function */

/* WM_DROPFILES window message handle function.
 * ARGUMENTS:
 *   - handle to an internal structure describing the dropped files:
 *       HDROP hDrop;
 * RETURNS: None.
 */
VOID dart::win::OnDropFiles( HDROP hDrop )
{
  static CHAR Buf[_MAX_PATH];

  INT n = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
  if (n > 0)
  {
    POINT pt;
    DragQueryPoint(hDrop, &pt);
    ClientToScreen(hWnd, &pt);
    HWND hWndItem = WindowFromPoint(pt);
    /// if (hWndItem == /* Check window */ )
    {
      /* for single file: DragQueryFile(hDrop, 0, Buf, sizeof(Buf)); */
      // Handle every file
      for (INT i = 0; i < n; i++)
      {
        DragQueryFile(hDrop, i, Buf, sizeof(Buf));
        /// Handle filename from 'Buf'
        // Can split:
        static CHAR
          Drive[_MAX_DRIVE], Dir[_MAX_DIR],
          FileName[_MAX_FNAME], FileExt[_MAX_EXT];
        _splitpath(Buf, Drive, Dir, FileName, FileExt);
        // . . .
      }
    }
  }
} /* End of 'dart::win::OnDropFiles' function */

/* WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN window messages handle function.
 * ARGUMENTS:
 *   - was double click flag:
 *       BOOL IsDoubleClick;
 *   - mouse position:
 *       INT X, INT Y;
 *   - down keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID dart::win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'dart::win::OnButtonDown' function */

/* WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP window messages handle function.
 * ARGUMENTS:
 *   - mouse position:
 *       INT X, INT Y;
 *   - down keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID dart::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'dart::win::OnButtonUp' function */

/* WM_MOUSEMOVE window message handle function.
 * ARGUMENTS:
 *   - mouse position:
 *       INT X, INT Y;
 *   - down keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID dart::win::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'dart::win::OnMouseMove' function */

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - down keys:
 *       UINT vk;
 * RETURNS: None.
 */
VOID dart::win::OnKeyDown( UINT vk, BOOL fDown, INT cRepeat, UINT flags )
{
} /* End of 'dart::win::OnKeyDown' function */

/* WM_NOTIFY window message handle function.
 * ARGUMENTS:
 *   - control identifier:
 *       INT Id;
 *   - notification header depended to control type:
 *       NMHDR *NoteHead;
 * RETURNS:
 *   (LRESULT) return value depended to notification.
 */
LRESULT dart::win::OnNotify( INT Id, NMHDR* NoteHead )
{
  return 0;
} /* End of 'dart::win::OnNotify' function */

/* WM_COMMAND window message handle function.
 * ARGUMENTS:
 *   - item (menu or accelerator) or control window identifier:
 *       INT Id;
 *   - control window handle:
 *       HWND hWndCtl;
 *   - notification: 0 - menu, 1 - accelerator, otherwise -
 *     depended to control (like BM_CLICKED):
 *       UINT CodeNotify;
 * RETURNS: None.
 */
VOID dart::win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify )
{
} /* End of 'dart::win::OnCommand' function */


/* WM_DRAWITEM window message handle function.
 * ARGUMENTS:
 *   - control identifier (for menu - 0):
 *       INT Id;
 *   - draw item information structure pointer:
 *       DRAWITEMSTRUCT *DrawItem;
 * RETURNS: None.
 */
VOID dart::win::OnDrawItem( INT Id, DRAWITEMSTRUCT* DrawItem )
{
  /// if (DrawItem->CtlID == ) // sample for check bax draw as button
  {
    UINT Flags = DFCS_BUTTONPUSH;

    if (DrawItem->itemState & ODS_DISABLED)
      Flags |= DFCS_INACTIVE;
    if (DrawItem->itemState & ODS_SELECTED)
      Flags |= DFCS_PUSHED;

    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
    InflateRect(&DrawItem->rcItem, -2, -2);
    Flags &= ~DFCS_PUSHED;
    Flags &= ~DFCS_BUTTONPUSH;
    Flags |= DFCS_BUTTONCHECK | DFCS_FLAT;
    /// if (DrawItem->CtlID == ...)
      Flags |= DFCS_CHECKED;
    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
  }
} /* End of 'dart::win::OnDrawItem' function */

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
VOID dart::win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'dart::win::OnHScroll' function */

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
VOID dart::win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'dart::win::OnVScroll' function */


/* WM_MENUSELECT window message handle function.
 * ARGUMENTS:
 *   - handle of menu:
 *       HMENU hMenu;
 *   - submenu item ID or submenu index
 *       INT Item;
 *   - handle of popup menu if selected popup submenu:
 *       HMENU hMenuPopup;
 *   - menu item flags (see MF_***):
 *       UINT Flags;
 * RETURNS: None.
 */
VOID dart::win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags )
{
} /* End of 'dart::win::OnMenuSelect' function */

/* WM_INITMENUPOPUP window message handle function.
 * ARGUMENTS:
 *   - handle of popup menu:
 *       HMENU hMenu;
 *   - submenu item position:
 *       UINT Item;
 *   - window system menu flag:
 *       BOOL IsSystemMenu;
 * RETURNS: None.
 */
VOID dart::win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
{
} /* End of 'dart::win::OnInitMenuPopup' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::win::OnExitSizeMove( VOID )
{
} /* End of 'dart::win::OnExitSizeMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID dart::win::OnEnterSizeMove( VOID )
{
} /* End of 'dart::win::OnEnterSizeMove' function */

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
LRESULT dart::win::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'dart::win::OnMessage' function */

/* END OF 'win_msg.cpp' FILE */
