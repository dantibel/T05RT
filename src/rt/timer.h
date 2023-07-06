/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
 /* FILE NAME   : timer.h
 * PURPOSE     : Raytracing project.
 *               Timer class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 26.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __timer_h_
#define __timer_h_

#include "def.h"

typedef uint64_t UINT64;

namespace dart
{
    /* timer source class */
    class timer
    {
    public:
      DBL GlobalTime, GlobalDeltaTime, Time, DeltaTime, FPS;
      BOOL IsPause;
      UINT64 TimePerSec, StartTime, OldTime, OldTimeFPS, PauseTime, FrameCounter;

      /* Class constructor */
      timer( VOID ) : GlobalTime(), GlobalDeltaTime(), Time(), DeltaTime(), FPS(), IsPause(FALSE)
      {
        LARGE_INTEGER t;
        QueryPerformanceFrequency(&t);
        TimePerSec = t.QuadPart;

        QueryPerformanceCounter(&t);
        StartTime = OldTime = OldTimeFPS = t.QuadPart;
      } /* End of 'timer' function */

      /* Measure time and FPS function.
       * ARGUMENTS: None;
       * RETURNS: None.
       */
      VOID Response( VOID )
      {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);

        /* Global time */
        GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
        GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

        /* Time with pause */
        if (IsPause)
        {
          DeltaTime = 0;
          PauseTime += t.QuadPart - OldTime;
        }
        else
        {
          DeltaTime = GlobalDeltaTime;
          Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
        }

        /* FPS measure */
        FrameCounter++;
        if (t.QuadPart - OldTimeFPS > TimePerSec)
        {
          FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
          OldTimeFPS = t.QuadPart;
          FrameCounter = 0;
        }
        OldTime = t.QuadPart;
      } /* End of 'Response' function */
    }; /* End of 'timer' class */
} /* end of 'dart' namespace */

#endif // __timer_h_

/* END OF 'timer.h' FILE */
