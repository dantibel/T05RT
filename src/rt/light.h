/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
 /* FILE NAME   : light.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing light declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 27.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __light_h_
#define __light_h_

#include <thread>
#include <vector>

#include "rt/shapes/shape_def.h"
#include "rt/frame.h"
#include "rt/light.h"

namespace dart
{
  namespace lgh
  {
    /* Light parameters class */
    class light_info
    {
    public:
      vec3 Dir;   // Light source direction
      vec3 Color; // Light source color
      DBL Dist;   // Distance to light source

    }; /* End of 'light_info' class */


    /* Light source class */
    class light
    {
    public:
      DBL Cc, Cl, Cq; // Attenuation coefficients

      /* Class constructor */
      light( DBL CoefConst = 1, DBL CoefLinear = 1, DBL CoefQuad = 1 ) : Cc(CoefConst), Cl(CoefLinear), Cq(CoefQuad)
      {
      } /* End of 'light' function */

      /* Get shadow coefficent for point function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       *   - pointer at light parameters:
       *       ligth_info *L;
       * RETURNS: None.
       */
      virtual DBL Shadow( const vec3 &P, light_info *LI )
      {
        return 0;
      } /* End of 'Shadow' function */
    }; /* End of 'light' class */


    /* Directional light source class */
    class direct : public light
    {
    public:
      vec3 Dir; // Light direction
      vec3 Clr; // Light color

      /* Class constructor.
       * ARGUMENTS:
       *   - reference at light direction:
       *       const vec3 &Direction;
       *   - reference at light color:
       *       const vec3 &Color;
       */
      direct( const vec3 &Direction, const vec3 &Color ) : light(1, 0, 0),
        Dir(Direction.Normalizing()), Clr(Color)
      {
      } /* End of 'direct' function */

      /* Get shadow coefficent for point function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       *   - pointer at light parameters:
       *       ligth_info *LI;
       * RETURNS: None.
       */
      DBL Shadow( const vec3 &P, light_info *LI ) override
      {
        LI->Color = Clr, LI->Dir = Dir, LI->Dist = DBL_MAX;
        return COM_MIN(1 / (Cc + Cl * LI->Dist + Cq * LI->Dist * LI->Dist), 1);
      } /* End of 'Shadow' function */
    }; /* End of 'direct' class */

    /* Spot light source class */
    class spot : public light
    {
    public:
      vec3 Pos;         // Light direction
      vec3 Dir;         // Light direction
      DBL ACos1, ACos2; // Light deflection angles coses
      vec3 Clr;         // Light color

      /* Class constructor.
       * ARGUMENTS:
       *   - reference at light Position:
       *       const vec3 &Position;
       *   - reference at light color:
       *       const vec3 &Color;
       */
      spot( const vec3 &Position, const vec3 &Direction, DBL Angle1, DBL Angle2, const vec3 &Color ) :
        light(1, 0, 0), Pos(Position), Dir(Direction.Normalizing()), ACos1(cos(D2R(Angle1))),
        ACos2(cos(D2R(Angle2))), Clr(Color)
      {
        DBL tmp;
        if (ACos1 > ACos2)
          COM_SWAP(ACos1, ACos2, tmp);
      } /* End of 'point' function */

      /* Get shadow coefficent for point function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       *   - pointer at light parameters:
       *       ligth_info *LI;
       * RETURNS: None.
       */
      DBL Shadow( const vec3 &P, light_info *LI ) override
      {
        LI->Color = Clr, LI->Dist = Pos.Distance(P);
        vec3 D = (Pos - P).Normalizing();
        if ((Dir & D) > ACos2)
          LI->Dir = D;
        else
          LI->Dir = Dir;
        return COM_MIN(1 / (Cc + Cl * LI->Dist + Cq * LI->Dist * LI->Dist), 1);
      } /* End of 'Shadow' function */
    }; /* End of 'spot' class */

    /* Point light source class */
    class point : public light
    {
    public:
      vec3 Pos; // Light direction
      vec3 Clr; // Light color

      /* Class constructor.
       * ARGUMENTS:
       *   - reference at light Position:
       *       const vec3 &Position;
       *   - reference at light color:
       *       const vec3 &Color;
       */
      point( const vec3 &Position, const vec3 &Color ) : light(1, 0, 0), Pos(Position), Clr(Color)
      {
      } /* End of 'point' function */

      /* Get shadow coefficent for point function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       *   - pointer at light parameters:
       *       ligth_info *LI;
       * RETURNS: None.
       */
      DBL Shadow( const vec3 &P, light_info *LI ) override
      {
        LI->Color = Clr, LI->Dir = (Pos - P).Normalizing(), LI->Dist = P.Distance(Pos);
        return COM_MIN(1 / (Cc + Cl * LI->Dist + Cq * LI->Dist * LI->Dist), 1);
      } /* End of 'Shadow' function */
    }; /* End of 'point' class */
  } /* end of 'lgh' namespace */
} /* end of 'dart' namespace */

#endif // __light_h_

/* END OF 'light.h' FILE */
