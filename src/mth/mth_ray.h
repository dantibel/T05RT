/* FILE NAME   : mth_ray.h
 * PURPOSE     : Raytracing project.
 *               Window base class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_ray_h_
#define __mth_ray_h_

#include <cmath>

#include "mth_def.h"

namespace mth
{
  /* 3D ray type */
  template <typename Type = DBL>
    class ray
    {
    public:
      vec3<Type> Org, Dir; // Ray origin and direction

      /* Class constructor
       * ARGUMENTS:
       *   - ray origin:
       *       vec3<Type> O;
       *   - ray direction:
       *       vec3<Type> D;
       */
      ray( vec3<Type> O, vec3<Type> D ) : Org(O), Dir(D.Normalizing())
      {
      } /* End of 'ray' function */

      /* Get ray point by distance function
       * ARGUMENTS:
       *   - ray distance:
       *       Type T;
       * RETURNS:
       *   (vec3<Type>) Ray point.
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */

    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif // __mth_ray_h_

/* END OF 'mth_ray' FILE */
