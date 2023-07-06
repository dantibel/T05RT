/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : frame.h
 * PURPOSE     : Raytracing project.
 *               Window base class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 25.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __frame_h_
#define __frame_h_

#include <fstream>

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

namespace dart
{
  /* Frame represetation type */
  class frame
  {
  public:
    INT W, H;     // frame size
    DWORD *Image; // pixels array
    HDC hMemDC;   // Second device context
    HBITMAP hBm;  // Bitmap handle

    /* Class constructor.
     * ARGUMENTS:
     *  - frame size:
     *       INT Width, Height;
     */
    frame( INT Width = 0, INT Height = 0 ) : W(Width), H(Height), Image(nullptr), hMemDC(nullptr), hBm(nullptr)
    {
    } /* End of 'frame' function */

    /* Class destructor. */
    ~frame()
    {
    } /* End of '~Frame' funciton */

    /* Change frame size function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      W = NewW, H = NewH;
    } /* End of 'frame' function */

    /* Put pixel on frame function.
     *   ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     *   - pixel color (RGBA format):
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      if (X >= W || X < 0 || Y >= H || Y < 0)
        return;

      Image[Y * W + X] = Color;
    } 
    /* End of 'PutPixel' function */

    /* Clamp color component lambda function.
     * ARGUMENTS:
     *   - color component in range [0; 1]:
     *       Type Value;
     * RETURNS:
     *   (BYTE) Color component in range [0; 255].
     */
    template <typename Type>
      BYTE Clamp( Type value )
      {
        if (value < 0)
          value = 0;
        if (value > 1)
          value = 1;
        return static_cast<BYTE>(value * 255);
      }; /* End of 'Clamp' function */

    /* Put pixel on frame function.
     * ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     *   - pixel color components:
     *       FLT R, G, B;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, FLT R, FLT G, FLT B, FLT A = 1 )
    {
      if (X >= W || X < 0 || Y >= H || Y < 0)
        return;

      Image[Y * W + X] = Clamp(A) << 24 | Clamp(R) << 16 | Clamp(G) << 8 | Clamp(B);
    } /* End of 'PutPixel' function */

    /* Put pixel on frame function.
     * ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     *   - pixel color (RGBA format):
     *       dart::vec3 Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, dart::vec4 Color)
    {
      if (X >= W || X < 0 || Y >= H || Y < 0)
        return;

      Image[Y * W + X] = Clamp(Color.W) << 24 | Clamp(Color.X) << 16 | Clamp(Color.Y) << 8 | Clamp(Color.Z);
    } /* End of 'PutPixel' function */

    /* Create DIB Section for current frame function.
     * ARGUMENTS:
     *   - reference at device context handle:
     *       HDC &hDC;
     * RETURNS: None.
     */
    VOID CreateDIB( HDC &hDC )
    {
      if (hBm != nullptr)
        DeleteObject(hBm);

      BITMAPINFOHEADER bmih = {0};
      bmih.biSize = sizeof(BITMAPINFOHEADER);
      bmih.biBitCount = 32;
      bmih.biPlanes = 1;
      bmih.biCompression = BI_RGB;
      bmih.biWidth = W;
      bmih.biHeight = H;
      bmih.biSizeImage = W * H * sizeof(DWORD);

      hBm = CreateDIBSection(nullptr, (BITMAPINFO*)&bmih, DIB_RGB_COLORS, (VOID**)&Image, NULL, 0);
      //SetStretchBltMode(hDC, COLORONCOLOR);
      if (hBm != nullptr)
        SelectObject(hMemDC, hBm);
      //StretchDIBits(hDC, X0, Y0, DrawW, DrawH, 0, 0, W, H, (VOID**)&Image, (BITMAPINFO*)&bmih, 0, 0);
      //StretchBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, W, H, SRCCOPY);
      //SetDIBitsToDevice(hDC, 0, 0, W, H, 0, 0, 0, H, Image, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
    } /* End of 'CreateDIB' function */

   /* Save frame to file function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Save( void )
    {
      CHAR FileName[102];
      SYSTEMTIME st;

      GetLocalTime(&st);
      wsprintf(FileName, "%04d%02d%02d_%02d%02d%02d_%03d.tga", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
      std::fstream F(FileName, std::fstream::out | std::fstream::binary);

      if (!F)
        return;

      CHAR Copyright[] = "DB6's picture";
      tgaFILEHEADER Header =
      {
        sizeof(Copyright),
        0,                // No palette
        2,                // Uncompressed RGB image
        0, 0, 0,          // color map info (absent)
        0, 0,             // Start (X,Y)
        (WORD)W, (WORD)H, // Image size
        32,               // Bits per pixel
        0x28,             // Upper-left image orign, 8-bit alpha-channel
      };

      F.write((const CHAR *)&Header, sizeof(Header));
      F.write(Copyright, sizeof(Copyright));
      F.write((const CHAR *) Image, (DWORD)W * (DWORD)H * 4);
      F.write(TGA_EXT_SIGNATURE, sizeof(TGA_EXT_SIGNATURE));
    } /* End of 'Save' function */
  }; /* End of 'frame' class */
} /* end of 'dart' namespace */

#endif //__frame_h_

/* END OF 'frame.h' FILE */
