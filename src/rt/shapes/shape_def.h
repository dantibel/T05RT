/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : shape_def.h
 * PURPOSE     : Raytracing project.
 *               Base implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __shape_def_h_
#define __shape_def_h_

#include "def.h"
#include "rt/shapes/shade_def.h" 

// Get solid color surface material macros
#define SOLID_MTL(Color) dart::surface(Color, Color * .8, dart::vec3(.5), 0, 0, 30)

namespace dart
{
  /* Threshold constant */
  const DBL Threshold = 0.0001;

  /* Basic shape class */
  class shape;

  /* Intersection class */
  class intr
  {
  public:
    DBL T;      // Ray intersection distance
    vec3 N, P;  // Intersection normal and intersection point
    shape *Shp; // Intersected shape
    INT I[5];   // Integer addons

    /* Class default constructor */
    intr() : T(0), N(), P(), Shp(nullptr), I{-1}
    {
    } /* End of 'intr' function */
  }; /* End of 'intr' class */

  /* Intersection list type */
  typedef stock<intr> intr_list;

  /* Modifiers list type */
  typedef stock<modifier *> mods_list;

  /* Basic shape class */
  class shape
  {
  public:
    surface Surf;   // Shape surface
    mods_list Mods; // Shape modifiers

    /* Class constructor.
     * ARGUMENTS:
     *   - reference at shape color:
     *       const surface &Surface;
     *   - pointer at shape modifiers:
     *       const stock<modifier *> *Modifiers
     */
    shape( const surface &Surface, mods_list *Modifiers ) : Surf(Surface), Mods()
    {
      if (Modifiers != nullptr)
        Mods = *Modifiers;
    } /* End of 'shape' constructor */

    /* Class destructor */
    ~shape()
    {
      Mods.Walk(
        []( modifier *Mod )
        {
          delete Mod;
        });
    } /* End of '~shape' function */

    /* Add modifier to shape function.
     * ARGUMENTS:
     *   - pointer at modifier:
     *       modifier *Modifier;
     * RETURNS:
     *   (shape *) self pointer.
     */
    shape * operator[]( modifier *Modifier )
    {
      Mods.push_back(Modifier);
      return this;
    }; /* End of 'operator[]' fucntion */

    /* Determine if point is inside shape function.
     * ARGUMENTS:
     *   - reference at point:
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) TRUE if point inside shape, FALSE overwise.
     */
    virtual BOOL IsInside( const vec3 &P )
    {
      return FALSE;
    } /* End of 'IsInside' function */


    /* Determine if there is intersection with ray function.
     * ARGUMENTS:
     *   - reference at ray:
     *       const ray &Ray;
     * RETURNS:
     *   (BOOL) TRUE if there is intersection, FALSE overwise.
     */
    virtual BOOL IsIntersect( const ray &Ray )
    {
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
    virtual BOOL Intersect( const ray &Ray, intr *Intr )
    {
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
    virtual INT AllIntersect( const ray &Ray, intr_list &Intrs )
    {
      return 0;
    } /* End of 'AllIntersect' function */
  }; /* End of 'shape' class */
}/* end of 'dart' namespace */

#endif //__shape_def_h_

/* END OF 'shape_def.h' FILE */
