/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : scene.cpp
 * PURPOSE     : Raytracing project.
 *               Ray tracing scene implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 26.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include <cmath>

#include "rt/rt.h"

namespace dart
{
  /* Add shape to scene function.
   * ARGUMENTS:
   *   - pointer at shape to add:
   *       shape *Shp;
   * RETURNS:
   *   (scene &) self reference.
   */
  scene & scene::operator<< ( shape *Shp )
  {
    Shapes.push_back(Shp);
    return *this;
  } /* End of 'operator<<' function */

  /* Add light source to scene function.
   * ARGUMENTS:
   *   - pointer at light source to add:
   *       light *Lgh;
   * RETURNS:
   *   (scene &) self reference.
   */
  scene & scene::operator<< ( lgh::light *Lgh )
  {
    Lights.push_back(Lgh);
    return *this;
  } /* End of 'operator<<' function */

  /* Render scene function.
   * ARGUMENTS:
   *   - reference at current camera:
   *       camera &Cam;
   *   - reference at frame:
   *       frame &Frm;
   * RETURNS: None.
   */
  VOID scene::Render( camera &Cam, frame &Frm )
  {
    IsRendered = FALSE;

    // prepare threads
    INT ThreadsAmount = std::thread::hardware_concurrency() - 1;
    std::vector<std::thread> Ths;
    Ths.resize(ThreadsAmount);

    // move camera
    if (!Timer.IsPause)
      Cam.Set(vec3(CamDist * sin(Timer.Time), CamDist, CamDist * cos(Timer.Time)), vec3(0), vec3(0, 1, 0));

    /*
    ThreadsAmount = 1;
    for (INT i = 0; i < ThreadsAmount; i++)
    {
      Ths[i] = std::thread(
        [&, i]( VOID )
        {
          // draw all scene
          for (INT Y = i; Y < Frm.H; Y += ThreadsAmount)
            for (INT X = 0; X < Frm.W; X++)
            {
              Frm.PutPixel(X, Y, vec4(Trace((Cam.CastRayToFrame(X + .5, Y - .5)), Air, 1, RecLevel < MaxRecLevel)));
            }
        });
    }
    for (INT i = 0; i < ThreadsAmount; i++)
      Ths[i].join();
    */
    // draw all scene
    for (INT Y = 0; Y < Frm.H; Y++)
      for (INT X = 0; X < Frm.W; X++)
        Frm.PutPixel(X, Y, vec4(Trace((Cam.CastRayToFrame(X + .5, Y - .5)), Air, 1, RecLevel < MaxRecLevel)));
    IsRendered = TRUE;
  } /* End of 'Render' function */

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
  vec3 scene::Trace( const ray &Ray, const envi &Media, DBL Weight, BOOL IsRecAvaible )
  {
    vec3 color = BackgroundColor;

    intr in;
    if (IsRecAvaible)
    {
      RecLevel++;
      if (Intersect(Ray, &in))
        color = Shade(Ray.Dir, Media, &in, Weight);

      // fog attenuation
#if 0
      DBL FogTrans;
      if (in.T < FogStart)
        FogTrans = 1;
      else if (in.T > FogEnd)
        FogTrans = 0;
      else
        FogTrans = (in.T - FogStart) / (FogEnd - FogStart);
      color = color * FogTrans + FogColor * (1 - FogTrans);
#endif
      color *= exp(-in.T * Media.Decay);

      RecLevel--;
    }
    return color;
  } /* End of 'Trace' funciton */

  /* Find intersection with ray function.
   * ARGUMENTS:
   *   - reference at ray:
   *       const ray &R;
   *   - pointer at intersection:
   *       intr *Intr;
   * RETURNS:
   *   (BOOL) TRUE if there is intersection, FALSE overwise.
   */
  BOOL scene::Intersect( const ray &R, intr *In )
  {
    intr best_in, in;
    Shapes.Walk(
      [R, &best_in, &in]( shape *Shp )
      {
        if (Shp->Intersect(R, &in))
          if (best_in.Shp == nullptr || best_in.T > in.T)
            best_in = in;
      });
    best_in.P = R(best_in.T);
    *In = best_in;
    return best_in.Shp != nullptr;
  } /* End of 'Intersect' function */

  /* Find all intersections with ray function.
   * ARGUMENTS:
   *   - reference at ray:
   *       const ray &R;
   *   - reference at intersection list:
   *       intr_list &Ins;
   * RETURNS:
   *   (INT) intersections count.
   */
  INT scene::AllIntersect( const ray &R, intr_list &Ins )
  {
    INT ins_count = 0;
    Shapes.Walk(
      [R, &Ins, &ins_count]( shape *Shp )
      {
        ins_count += Shp->AllIntersect(R, Ins);
      });
    return ins_count++;
  } /* End of 'AllIntersect' function */

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
  vec3 scene::Shade( const vec3 &V, const envi &Media, intr *In, DBL Weight )
  {
    shade_info si {In->P, In->N, In->Shp, In->Shp->Surf, Media, {1, 0, 0}, {0, 1, 0}}; //((In->N & V) > Threshold) ? -In->N : 
    In->Shp->Mods.Walk(
      [this, &si]( modifier *Mod)
      {
        Mod->Apply(&si, Timer);
      });

    if ((si.N & V) > Threshold)
      si.N *= -1;
    vec3 color = si.Surf.Ka * AmbientColor;
    vec3 R = (V - si.N * (2 * (V & si.N))).Normalizing();
    for (auto lgh : Lights)
    {
      // attenuation
      lgh::light_info lgh_info;
      color *= lgh->Shadow(si.P, &lgh_info);

      // cast shadow
      intr_list intr_list;
      if (AllIntersect(ray(si.P + lgh_info.Dir * Threshold, lgh_info.Dir), intr_list) > 0 && intr_list[0].T < lgh_info.Dist)
        continue;


      // diffuse
      DBL nl = si.N & lgh_info.Dir;
      if (abs(nl) > Threshold)
      {
        color += si.Surf.Kd * lgh_info.Color * nl;

#if 1
        // specular
        DBL rl = R & lgh_info.Dir;
        if (rl > Threshold)
        {
          color += si.Surf.Ks * lgh_info.Color * pow(rl, si.Surf.Ph);
        }
#endif
      }
    }
    // Reflection other scene shapes
    DBL w = si.Surf.Kr * Weight;
    if (w > .003921)
      color += Trace(ray(si.P + R * Threshold, R), Media, w, RecLevel < MaxRecLevel);

    if (color.MaxComp() > .9)
      w = w * 2;
#if 1
    // Refraction
    w = si.Surf.Kt * Weight;
    if (w > .003921)
    {
      DBL n = .95;
      vec3 T = (((V - si.N * (V & si.N)) * n) -
        si.N * sqrt(1 - (1 - (-V & si.N) * (-V & si.N)) * n * n)).Normalizing();
      vec3 c = Trace(ray(si.P + T * Threshold, T), envi(1.05, .028), w, RecLevel < MaxRecLevel);
      color += c;
    }
#endif
    return color;
  } /* End of 'Shade' funciton */
} /* end of 'dart' namespce */
/* END OF 'scene.h' FILE */
