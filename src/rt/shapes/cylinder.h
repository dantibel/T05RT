/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : cylinder.h
 * PURPOSE     : Raytracing project.
 *               Cylinder implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __cylinder_h_
#define __cylinder_h_

#include "rt/shapes/shape_def.h"

namespace dart
{
    /* Cylinder sphere class */
    class cylinder : public shape
    {
      vec3 C, A; // Cylinder central and axis
      DBL H;     // Cylinder height

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - reference at cylinder center:
       *       const vec3 &Center;
       *   - reference at cylinder axis:
       *       const vec4 &Axis;
       *   - cylinder height:
       *       DBL Height;
       *   - reference at cylinder material:
       *       const surface &Surface;
       */
      cylinder( const vec3 &Center, const vec3 &Axis, DBL Height, const surface &Surface,  mods_list *Modifiers = nullptr ) :
        shape(Surface, Modifiers), C(Center), A(Axis), H(Height)
      {
      } /* End of 'cylinder' function */

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
        
      } /* End of 'Intersect' function */
    }; /* End of 'cylinder' class */
}/* end of 'dart' namespace */

#endif //__cylinder_h_

/* END OF 'cylinder.h' FILE */
