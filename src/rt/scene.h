/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
 /* FILE NAME   : scene.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing scene declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 26.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __scene_h_
#define __scene_h_

#include <thread>

#include "rt/shapes/shape_def.h"
#include "rt/frame.h"
#include "rt/light.h"

namespace dart
{
  /* Ray tracing scene class */
  class scene
  {
    vec3 AmbientColor, BackgroundColor, FogColor; // Scene colors
    DBL FogStart, FogEnd; // Fog start and maximum distances;
    envi Air; // Default scene environment

    BOOL IsRendered; // Is scene rendered flag (for threads syncronization)

    stock<shape *> Shapes; // Shapes on scene
    stock<lgh::light *> Lights; // Light sources on scene

    INT RecLevel, MaxRecLevel; // Current and maximum recurcy level

  public:
    DBL CamDist; // Camera distance from (0, 0, 0)

    timer Timer; // Scene timer

    /* Class default constructor */
    scene( VOID ) : AmbientColor(vec3(.13)), BackgroundColor(vec3(0, .17, .5)), FogColor(vec3(.1, .1, .3)),
      FogStart(15), FogEnd(30), Air(1, .028), RecLevel(0), MaxRecLevel(3), IsRendered(FALSE), Shapes(), Lights(), Timer(), CamDist(15)
    {
    } /* End of 'scene' function */

    /* Class destructor */
    ~scene( VOID )
    {
      Shapes.Walk(
        []( shape *Shp )
        {
          delete Shp;
        });
      Lights.Walk(
        []( lgh::light *Lgh )
        {
          delete Lgh;
        });
    } /* End of '~scene' function */

    /* Add shape to scene function.
     * ARGUMENTS:
     *   - pointer at shape to add:
     *       shape *Shp;
     * RETURNS:
     *   (scene &) self reference.
     */
    scene & operator<< ( shape *Shp );

    /* Add light source to scene function.
     * ARGUMENTS:
     *   - pointer at light source to add:
     *       light *Lgh;
     * RETURNS:
     *   (scene &) self reference.
     */
    scene & operator<< ( lgh::light *Lgh );

    /* Render scene function.
     * ARGUMENTS:
     *   - reference at current camera:
     *       camera &Cam;
     *   - reference at frame:
     *       frame &Frm;
     * RETURNS: None.
     */
    VOID Render( camera &Cam, frame &Frm );

    /* Trace ray in scene function.
     * ARGUMENTS:
     *   - reference at ray:
     *       const ray &Ray;
     *   - reference at tracing environment:
     *       const envi &Media;
     *   - weigth:
     *       DBL Weight;
     *   - is recurcy ray tracing avaible flag:
     *       BOOL IsRecAvaible;
     * RETURNS:
     *   (vec3) Pixel color.
     */
    vec3 Trace( const ray &Ray, const envi &Media, DBL Weight, BOOL IsRecAvaible );

    /* Find intersection with ray function.
     * ARGUMENTS:
     *   - reference at ray:
     *       const mth::ray<Type> &R;
     *   - pointer at intersection:
     *       intr<Type> *Intr;
     * RETURNS:
     *   (BOOL) TRUE if there is intersection, FALSE overwise.
     */
    BOOL Intersect( const ray &R, intr *In );

    /* Find all intersections with ray function.
     * ARGUMENTS:
     *   - reference at ray:
     *       const ray &R;
     *   - reference at intersection list:
     *       intr_list *Ins;
     * RETURNS:
     *   (INT) intersections count.
     */
    INT AllIntersect( const ray &R, intr_list &Ins );

    /* Get pixel color function.
     * ARGUMENTS:
     *   - reference at light direction:
     *       const vec3 &V;
     *   - reference at tracing environment:
     *       const envi &Media;
     *   - point at intersection:
     *       const intr *In;
     *   - weigth:
     *       DBL Weight;
     * RETURNS:
     *   (vec3) Pixel color.
     */
    vec3 Shade( const vec3 &V, const envi &Media, intr *In, DBL Weight );
  }; /* End of 'scene' class */
}/* end of 'dart' namespace */

#endif //__scene_h_

/* END OF 'scene.h' FILE */
