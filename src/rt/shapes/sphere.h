/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Raytracing project.
 *               Sphere implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __sphere_h_
#define __sphere_h_

#include "rt/shapes/shape_def.h"

namespace dart
{
    /* Sphere sphere class */
    class sphere : public shape
    {
      vec3 C;    // Sphere center
      DBL R, R2; // Sphere radius

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - reference at sphere center:
       *       const vec3 &Center;
       *   - sphere raius:
       *       DBL Radius;
       *   - reference at sphere color:
       *       const surface &Surface;
       */
      sphere( const vec3 &Center, DBL Radius, const surface &Surface, mods_list *Modifiers = nullptr ) :
        shape(Surface, Modifiers), C(Center), R(Radius), R2(Radius * Radius)
      {
      } /* End of 'sphere' functions */

      /* Determine if point is inside sphere function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) TRUE if point inside sphere, FALSE overwise.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        return C.Distance(P) < R + Threshold;
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
        vec3 a = C - Ray.Org;
        DBL
          oc2 = a & a,
          ok = (a & Ray.Dir),
          h2 = R2 - (oc2 - ok * ok);

        // Ray starts inside sphere
        if (oc2 < R2)
          return TRUE;

        // Ray starts back os sphere center
        if (ok < 0)
          return FALSE;

        // Ray treces away sphere
        if (h2 < 0)
          return FALSE;

        // ray starts outside sphere
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
        vec3 a = C - Ray.Org;
        DBL
          oc2 = a & a,
          ok = (a & Ray.Dir),
          h2 = R2 - (oc2 - ok * ok);

        // Ray starts inside sphere
        if (oc2 < R2)
        {
          Intr->T = ok + sqrt(h2);
          //Intr->P = Ray(Intr->T);
          Intr->N = (Intr->P - C) / R;
          Intr->Shp = this;
          return TRUE;
        }

        // Ray starts back os sphere center
        if (ok < 0)
          return FALSE;

        // Ray treces away sphere
        if (h2 < 0)
          return FALSE;

        // ray starts outside sphere
        Intr->T = ok - sqrt(h2);
        Intr->P = Ray(Intr->T);
        Intr->N = (Intr->P - C) / R;
        Intr->Shp = this;
        return TRUE;
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
        vec3 a = C - Ray.Org;
        DBL
          oc2 = a & a,
          ok = (a & Ray.Dir),
          h2 = R2 - (oc2 - ok * ok);
        intr in;

          // ray starts inside sphere
          if (oc2 < R2)
          {
            in.T = ok + sqrt(h2);
            //in.P = Ray(in.T);
            in.N = (in.P - C) / R;
            in.Shp = this;
            Intrs.push_back(in);
            return 1;
          }

          // ray starts back of sphere center
          if (ok < 0)
            return 0;

          // ray treces away sphere
          if (h2 < 0)
            return 0;

          // ray starts outside sphere
          in.T = ok - sqrt(h2);
          in.P = Ray(in.T);
          in.N = (in.P - C) / R;
          in.Shp = this;
          Intrs.push_back(in);
          in.T = ok + sqrt(h2);
          in.P = Ray(in.T);
          in.N = -(in.P - C) / R;
          //in.Shp = this;
          Intrs.push_back(in);
          return 2;
      } /* End of 'AllIntersect' function */
    }; /* End of 'sphere' class */
}/* end of 'dart' namespace */

#endif //__sphere_h_

/* END OF 'sphere.h' FILE */