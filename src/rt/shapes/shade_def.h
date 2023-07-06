/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : shape_def.h
 * PURPOSE     : Raytracing project.
 *               Shapes modifiers classes implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __modifier_h_
#define __modifier_h_

#include "def.h"
#include "rt/timer.h"

namespace dart
{
  /* Light tracing environment class*/
  class envi
  {
  public:
    DBL
      RefCoef,  // Refraction coefficient
      Decay;    // Environment media decay coefficient

    /* Class constructor
     * ARGUMENTS:
     *   - refraction coefficent:
     *       DBL RefractionCoef;
     *   - decaay coefficent:
     *       DBL DecayCoef;
     */
    envi( DBL RefractionCoef, DBL DecayCoef ) : RefCoef(RefractionCoef), Decay(DecayCoef)
    {
    } /* End of 'envi' function */
  }; /* End of 'envi' class*/

  /* Basic shape class */
  class shape;

  /* Shape surface material class*/
  class surface
  {
  public:
    vec3
      Ka, // Ambient coefficent
      Kd, // Diffuse coefficent
      Ks; // Specular coefficent
    DBL
      Kr, // Reflection coefficent
      Kt, // Transmession coefficent
      Ph; // Phong coefficent

    /* Class constructor */
    surface( VOID ) :  Ka(), Kd(), Ks(), Kr(), Kt(), Ph()
    {
    }

    /* Class constructor */
    surface( const vec3 &KaCoef, const vec3 &KdCoef, const vec3 &KsCoef, DBL KrCoef, DBL KtCoef, DBL PhCoef ) : 
      Ka(KaCoef), Kd(KdCoef), Ks(KsCoef), Kr(KrCoef), Kt(KtCoef), Ph(PhCoef)
    {
    } /* End of 'surface' function */
  }; /* End of 'surface' class*/

  /* Current shadding parameters struct */
  struct shade_info
  {
    vec3 P;       // Point
    vec3 N;       // Normal
    shape *Shp;   // Shape
    surface Surf; // Surface
    envi Media;   // Envirnment
    vec3 Du, Dv;  // Tangentspace vectors
  }; /* End of 'shade_info' struct */

   /* Shape modifier class */
  class modifier
  {
  public:
    /* Class destructor */
    virtual ~modifier( VOID )
    {
    } /* End of '~modifier' function */

    /* Apply modifier to shape function.
     * ARGUMENTS:
     *   - pointer at shade parameters:
     *       shade_info *Sh;
     *   - time from program start:
     *       const timer &Timer;
     * RETURNS: None.
     */
    virtual VOID Apply( shade_info *Sh, const timer &Timer )
    {
    } /* End of 'Apply' function */
  }; /* End of 'modifier' class*/

  /* Cheker shape modifier class */
  class cheker : public modifier
  {
    DBL Size; // Cell size

  public:
    /* Class constructor */
    cheker( DBL CellSize = 1 ) : Size(CellSize)
    {
    } /* End of 'cheker' function */

    /* Class destructor */
    ~cheker( VOID )
    {
    } /* End of '~cheker' function */

    /* Apply modifier to shape function.
     * ARGUMENTS:
     *   - pointer at shade parameters:
     *       shade_info *Sh;
     *   - time from program start:
     *       const timer &Timer;
     * RETURNS: None.
     */
    VOID Apply( shade_info *Sh, const timer &Timer ) override
    {
      if ((INT(Sh->P.X / Size + (Sh->P.X > 0)) ^ INT(Sh->P.Z / Size + (Sh->P.Z > 0))) & 1)
      {
        Sh->Surf.Kd = vec3(1);
        Sh->Surf.Ks = vec3(0.1);
      }
      else
      {
        Sh->Surf.Kd = vec3(0);
        Sh->Surf.Ks = vec3(1);
      }
    } /* End of 'Apply' function */
  }; /* End of 'cheker' class */


  /* Rotator shape modifier class */
  class rotator : public modifier
  {
    DBL Vel; // Rotation velocity

  public:
    /* Class constructor */
    rotator( DBL AngleVelocity = 1 ) : Vel(AngleVelocity)
    {
    } /* End of 'rotstor' function */

    /* Class destructor */
    ~rotator( VOID )
    {
    } /* End of '~rotator' function */

    /* Apply modifier to shape function.
     * ARGUMENTS:
     *   - pointer at shade parameters:
     *       shade_info *Sh;
     *   - time from program start:
     *       const timer &Timer;
     * RETURNS: None.
     */
    VOID Apply( shade_info *Sh, const timer &Timer ) override
    {
      if (!Timer.IsPause)
      {
        matr M = matr::RotateY(static_cast<FLT>(Timer.DeltaTime * Vel));
        Sh->P = M * Sh->P;
        Sh->N = M.NormalTransform(Sh->N);
      }
    } /* End of 'Apply' function */
  }; /* End of 'rotator' class*/
} /* end of 'dart' namespace */

#endif // __modifier_h_

/* END OF 'modifier.h' FILE */

