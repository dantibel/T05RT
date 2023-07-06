/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : triangle.h
 * PURPOSE     : Raytracing project.
 *               Triangle class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __triangle_h_
#define __triangle_h_

#include "rt/shapes/shape_def.h"

namespace dart
{
    /* triangle triangle class */
    class triangle : public shape
    {
      vec3
        P0, P1, P2,        // Triangle vertexes
        N0, N1, N2,        // Triangle normals
        U1, V1, N;         // Triangle basis
      DBL D, u0, v0, u, v; // Triangle basis coordinates

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - references at triangle vertexes:
       *       const vec3 &Point0, &Point1, &Point2;
       *   - references at triangle normals:
       *       const vec3 &Normal0, &Normal1, &Normal2
       *   - reference at triangle color:
       *       const surface &Surface;
       */
      triangle( const vec3 &Point0, const vec3 &Point1, const vec3 &Point2, const vec3 &Normal0, const vec3 &Normal1, const vec3 &Normal2, const surface &Surface, mods_list *Modifiers = nullptr ) :
        shape(Surface, Modifiers), P0(Point0), P1(Point1), P2(Point2), N0(Normal0.Normalizing()), N1(Normal1.Normalizing()), N2(Normal2.Normalizing()), D(), u0(), v0(), u(), v()
      {
        vec3 S1 = P1 - P0, S2 = P2 - P0;
        N = (S1 % S2).Normalizing();
        D = P0 & N;
        U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2)), u0 = P0 & U1;
        V1 = (S2 * (S1 & S1) - S1 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2)), v0 = P0 & V1;
      } /* End of 'triangle' functions */

      /* Determine if point is inside triangle function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) TRUE if point inside triangle, FALSE overwise.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        return FALSE;
      } /* End of 'IsInside' function */

      /* Find intersection with ray function.
       * ARGUMENTS:
       *   - reference at ray:
       *       const ray &Ray;
       * RETURNS:
       *   (BOOL) TRUE if there is intersection, FALSE overwise.
       */
      BOOL IsIntersect( const ray &Ray ) override
      {
        DBL t = -((N & Ray.Org) + (N & P0)) / (N & Ray.Dir);
        if (t >= Threshold)
        {
          vec3 p = Ray(t);
          u = (p & U1) - u0, v = (p & V1) - v0;
          if (u > -Threshold && u < 1 + Threshold && v > -Threshold && v < 1 + Threshold && u + v < 1 + Threshold)
          //if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && u + v <= 1)
            return TRUE;
        }
        return FALSE;
      } /* End of 'IsIntersect' function */

      /* Find intersection with ray function.
       * ARGUMENTS:
       *   - reference at ray:
       *       const ray &Ray;
       *   - pointer at intersection:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) TRUE if there is intersection, FALSE overwise.
       */
      BOOL Intersect( const ray &Ray, intr *Intr ) override
      {
        Intr->T = -((N & Ray.Org) + (N & P0)) / (N & Ray.Dir);
        if (Intr->T >= Threshold)
        {
          Intr->P = Ray(Intr->T);
          u = (Intr->P & U1) - u0, v = (Intr->P & V1) - v0;
          if (u > -Threshold && u < 1 + Threshold && v > -Threshold && v < 1 + Threshold && u + v < 1 + Threshold)
          //if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && u + v <= 1)
          //if (u >= Threshold && u <= Threshold && v >= Threshold && v <= Threshold && u + v <= Threshold)
          {
            Intr->N = N0 * (1 - u - v) + N1 * u + N2 * v;
            Intr->Shp = this;
            return TRUE;
          }
        }
        return FALSE;
      } /* End of 'Intersect' function */

      /* Get all intersections with ray function.
       * ARGUMENTS:
       *   - reference at ray:
       *       const ray &Ray;
       *   - reference at intersection list:
       *       intr_list &Intrs;
       * RETURNS:
       *   (INT) intersections count.
       */
      INT AllIntersect( const ray &Ray, intr_list &Intrs ) override
      {
        intr in;
        in.T = -((N & Ray.Org) + (N & P0)) / (N & Ray.Dir);
        if (in.T >= Threshold)
        {
          in.P = Ray(in.T);
          u = (in.P & U1) - u0, v = (in.P & V1) - v0;
          if (u > -Threshold && u < 1 + Threshold && v > -Threshold && v < 1 + Threshold && u + v < 1 + Threshold)
          //if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && u + v <= 1)
          {
            in.N = N0 * (1 - u - v) + N1 * u + N2 * v;;
            in.Shp = this;
            Intrs.push_back(in);
            return 1;
          }
        }
        return 0;
      } /* End of 'AllIntersect' function */
    }; /* End of 'triangle' class */
}/* end of 'dart' namespace */

#endif //__triangle_h_

/* END OF 'triangle.h' FILE */
