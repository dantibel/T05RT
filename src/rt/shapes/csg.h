/* FILE NAME   : frame.h
 * PURPOSE     : Raytracing project.
 *               CSG classes declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 25.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __csg_h_
#define __csg_h_

#include "rt/shapes/shape.h"

namespace dart
{
  namespace csg
  {
    /* Shapes intersection class */
    class intersection : public shape
    {
    public:
      shape *ShpA, *ShpB; // Shapes to intersect

      /* Class constructor.
       * ARGUMENTS:
       *   - pointers at shapes to intersect:
       *       shape *ShapeA, *ShapeB;
       *  - reference at shape material:
       *       const surface &Surface;
       */
      intersection( shape *ShapeA, shape *ShapeB, const surface &Surface = SOLID_MTL(vec3(.6, .2, .2))  ) : shape(Surface), ShpA(ShapeA), ShpB(ShapeB)
      {
      } /* End of 'intersection' functions */

      /* Class destructor. */
      ~intersection( VOID )
      {
        delete ShpA, delete ShpB;
      } /* End of '~intersection' functions */

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
        intr_list il1, il2;
        intr best_in;
        if (ShpA->AllIntersect(Ray, il1) > 0 && ShpB->AllIntersect(Ray, il2) > 0)
        {
          for (auto &i : il1)
          {
            if (ShpB->IsInside(i.P))
              if (best_in.Shp == nullptr || best_in.T > i.T)
                best_in = i;
          }
          for (auto &i : il2)
          {
            if (ShpA->IsInside(i.P))
              if (best_in.Shp == nullptr || best_in.T > i.T)
                best_in = i;
          }
        }
        *Intr = best_in;
        return best_in.Shp != nullptr;;
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
        intr_list il1, il2;
        INT ins_count = 0;
        if (ShpA->AllIntersect(Ray, il1) > 0 && ShpB->AllIntersect(Ray, il2) > 0)
        {
          for (auto &i : il1)
          {
            if (ShpB->IsInside(i.P))
            {
              Intrs.push_back(i);
              ins_count++;
            }
          }
          for (auto &i : il2)
          {
            if (ShpA->IsInside(i.P))
            {
              Intrs.push_back(i);
              ins_count++;
            }
          }
        }
        return ins_count;
      } /* End of 'AllIntersect' function */
    }; /* End of 'intersection' class */


    /* Shapes substract class */
    class substract : public shape
    {
    public:
      shape *ShpA, *ShpB; // Shapes to intersect

      /* Class constructor.
       * ARGUMENTS:
       *   - pointers at shapes to intersect:
       *       shape *ShapeA, *ShapeB;
       *  - reference at shape material:
       *       const surface &Surface;
       */
      substract( shape *ShapeA, shape *ShapeB, const surface &Surface = SOLID_MTL(vec3(.6, .2, .2))  ) : shape(Surface), ShpA(ShapeA), ShpB(ShapeB)
      {
      } /* End of 'substract' functions */

      /* Class destructor. */
      ~substract( VOID )
      {
        delete ShpA, delete ShpB;
      } /* End of '~substract' functions */

      /* Find substract with ray function.
       * ARGUMENTS:
       *   - reference at ray:
       *       const ray &Ray;
       *   - pointer at substract:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) TRUE if there is substract, FALSE overwise.
       */
      BOOL Intersect( const ray &Ray, intr *Intr ) override
      {
        intr_list il;
        intr best_in;
        if (ShpA->AllIntersect(Ray, il) > 0)
        {
          for (auto &i : il)
          {
            if (!ShpB->IsInside(i.P))
              if (best_in.Shp == nullptr || best_in.T > i.T)
                best_in = i;
          }
        }
        *Intr = best_in;
        return best_in.Shp != nullptr;
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
        intr_list il;
        INT ins_count = 0;
        if (ShpA->AllIntersect(Ray, il) > 0)
        {
          for (auto &i : il)
          {
            if (!ShpB->IsInside(i.P))
            {
              Intrs.push_back(i);
              ins_count++;
            }
          }
        }
        return ins_count;
      } /* End of 'AllIntersect' function */
    }; /* End of 'substract' class */
  } /* end of 'csg' namespace */
} /* end of 'dart' namespace */

#endif //__csg_h_

/* END OF 'csg.h' FILE */
