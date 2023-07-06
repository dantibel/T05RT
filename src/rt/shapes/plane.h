/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : plane.h
 * PURPOSE     : Raytracing project.
 *               Plane implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __plane_h_
#define __plane_h_

#include "rt/shapes/shape_def.h"

namespace dart
{
    /* Plane sphere class */
    class plane : public shape
    {
      vec3 N; // Plane normal
      DBL D;  // Distanse from (0, 0, 0) to plane in normals

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - reference at plane points:
       *       const vec3 &P0, &P1, &P2;
       *   - reference at plane material:
       *       const surface &Surface;
       */
      plane( const vec3 &P0, const vec3 &P1, const vec3 &P2, const surface &Surface, mods_list *Modifiers = nullptr ) :
        shape(Surface, Modifiers), N(((P0 - P1) % (P0 - P2)).Normalizing()), D(N & P0)
      {
      } /* End of 'plane' function */

       /* Determine if point is inside sphere function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) TRUE if point inside sphere, FALSE overwise.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        return (N & P) == D;
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
        if (-((N & Ray.Org) - D) / (N & Ray.Dir) < Threshold)
          return FALSE;
        return TRUE;
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
        Intr->T = -((N & Ray.Org) + D) / (N & Ray.Dir);
        if (Intr->T < Threshold)
          return FALSE;
        //Intr->P = Ray(Intr->T);
        Intr->N = N;
        Intr->Shp = this;
        return TRUE;
      } /* End of 'Intersect' class */

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
        in.T = -((N & Ray.Org) + D) / (N & Ray.Dir);
        if (in.T < Threshold)
          return 0;
        in.P = Ray(in.T);
        in.N = N;
        in.Shp = this;
        Intrs.push_back(in);
        return 1;
      } /* End of 'AllIntersect' function */
    }; /* End of 'plane' class */
}/* end of 'dart' namespace */

#endif //__plane_h_

/* END OF 'plane.h' FILE */
