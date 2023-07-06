 /*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : cube.h
 * PURPOSE     : Raytracing project.
 *               cube implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __cube_h_
#define __cube_h_

#include "rt/shapes/shape_def.h"

namespace dart
{
    /* cube shape class */
    class cube : public shape
    {
      vec3 B1, B2; // cube bound points

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - reference at cube bound points:
       *       const vec3 &Bound1, &Bound2;
       *   - reference at cube material:
       *       const surface &Surface;
       */
      cube( const vec3 &Bound1, const vec3 &Bound2, const surface &Surface,  mods_list *Modifiers = nullptr ) :
        shape(Surface, Modifiers), B1(Bound1), B2(Bound2)
      {
        //vec3 tmp;
        //if (B1.MaxComp() > B2.MaxComp())
          //COM_SWAP(B1, B2, tmp);
      } /* End of 'cube' function */

       /* Determine if point is inside sphere function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) TRUE if point inside sphere, FALSE overwise.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        if (P.X >= B1.X && P.X <= B2.X &&
            P.Y >= B1.Y && P.Y <= B2.Y &&
            P.Z >= B1.Z && P.Z <= B2.Z)
          return TRUE;
        return FALSE;
      } /* End of 'IsInside' function */

      /* Determine if there is intersection with ray function.
       * ARGUMENTS:
       *   - reference at ray:
       *       const ray &Ray;
       * RETURNS:
       *   (BOOL) TRUE if there is intersection, FALSE overwise.
       */
      BOOL IsIntersect( const ray &Ray ) override
      {
        DBL TNear = 0, TFar = DBL_MAX, T0, T1, tmp;
        for (INT i = 0; i < 3; i++)
        {
          if (COM_ABS(Ray.Dir[i]) < Threshold)
          {
            if (Ray.Org[i] < B1[i] || Ray.Org[i] > B2[i])
              return FALSE;
          }
          else
          {
            T0 = (B1[i] - Ray.Org[i]) / Ray.Dir[i], T1 = (B2[i] - Ray.Org[i]) / Ray.Dir[i];
            if (T0 > T1)
              COM_SWAP(T0, T1, tmp);
            if (T0 > TNear)
              TNear = T0;
            if (T1 < TFar)
              TFar = T1;
            if (TNear > TFar || TFar < 0)
              return FALSE;
          }
        }
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
        vec3 Normals[3] { vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) };

        DBL TNear = 0, TFar = DBL_MAX, T0, T1, tmp;
        for (INT i = 0; i < 3; i++)
        {
          if (COM_ABS(Ray.Dir[i]) < Threshold)
          {
            if (Ray.Org[i] < B1[i] || Ray.Org[i] > B2[i])
              return FALSE;
          }
          else
          {
            T0 = (B1[i] - Ray.Org[i]) / Ray.Dir[i], T1 = (B2[i] - Ray.Org[i]) / Ray.Dir[i];
            if (T0 > T1 - Threshold)
              COM_SWAP(T0, T1, tmp);
            if (T0 > TNear)
            {
              TNear = T0;
              Intr->I[0] = i;
            }
            if (T1 < TFar)
              TFar = T1;
            if (TNear > TFar || TFar < 0)
              return FALSE;
          }
        }
        Intr->T = TNear;
        //Intr->P = Ray(Intr->T);
        Intr->Shp = this;
        if (Ray.Dir.Distance(Normals[Intr->I[0]]) >= 1)
          Intr->N = Normals[Intr->I[0]];
        else
          Intr->N = -Normals[Intr->I[0]];
        return TRUE;
      } /* End of 'Intersect' function */

      /* Get all intersection with ray function.
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
        vec3 Normals[3] { vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) };

        INT IntrCount = 0;
        DBL TNear = 0, TFar = DBL_MAX, T0, T1, tmp;
        intr in1, in2;
        for (INT i = 0; i < 3; i++)
        {
          if (COM_ABS(Ray.Dir[i]) < Threshold)
          {
            if (Ray.Org[i] < B1[i] || Ray.Org[i] > B2[i])
              return 0;
          }
          else
          {
            T0 = (B1[i] - Ray.Org[i]) / Ray.Dir[i], T1 = (B2[i] - Ray.Org[i]) / Ray.Dir[i];
            if (T0 > T1)
              COM_SWAP(T0, T1, tmp);
            if (T0 > TNear)
            {
              TNear = T0;
              in1.I[0] = i;
            }
            if (T1 < TFar)
              TFar = T1;
            if (TNear > TFar || TFar < 0)
              return 0;
          }
        }

        in1.T = TNear, in2.T = TFar;
        in1.P = Ray(in1.T), in2.P = Ray(in2.T);
        in1.Shp = in2.Shp = this;
        if (Ray.Dir.Distance(Normals[in1.I[0]]) >= 1)
          in1.N = Normals[in1.I[0]], in2.N = -in1.N;
        else
          in1.N = -Normals[in1.I[0]], in2.N = -in1.N;
        Intrs.push_back(in1);
        Intrs.push_back(in2);

        return 2;
      } /* End of 'AllIntersect' function */
    }; /* End of 'cube' class */
}/* end of 'dart' namespace */

#endif //__cube_h_

/* END OF 'cube.h' FILE */