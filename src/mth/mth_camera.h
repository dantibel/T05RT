/* FILE NAME   : mth_camera.h
 * PURPOSE     : Raytracing project.
 *               Camera class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 25.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_camera_h_
#define __mth_camera_h_

#include <cmath>

#include "mth_def.h"

namespace mth
{
  /* Camera type */
  template <typename Type = DBL>
    class camera
    {
    public:
      vec3<Type>
        Loc,   // Camera location
        At,    // Camera view at-vector
        Dir,   // Camera direction
        Right, // Camera right-vector
        Up;    // Camera up-vector

      Type
        Wp, Hp, ProjSize, // Projection size
        ProjDist,         // Distance to projection
        FarClip;          // Maximim distance for drawing scene

      INT Ws, Hs; // Frame size

      matr<Type>
        ViewM, // View matrix
        ProjM, // Projection matrix
        VxP;   // Multiplication view and projection matrices

      /* Class constructor */
      camera() : Loc(), At(), Dir(), Right(), Up(), Wp(), Hp(), ProjSize(),
        ProjDist(), FarClip(), Ws(), Hs(), ViewM(), ProjM(), VxP()
      {
      } /* End of 'camera' function */

      /* Class constructor 
       *ARGUMENTS:
       *  - reference at camera location:
       *      const vec3<Type> &Loc;
       *  - reference at camera view at:
       *      const vec3<Type> &At;
       *  - reference at  camera up-vector;
       *      const vec3<Type> &Up;
       *  - projection size:
       *      Type ProjSize;
       *  - distance to projection:
       *      Type ProjDist;
       *  - maximim distance for drawing scene:
       *      Type FarClip;
       */
      camera( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up,
              Type ProjSize = 0.1, Type ProjDist = 0.1, Type FarClip = 1000) :
        Loc(Loc), At(At), Dir(At - Loc), Right(Dir % Up), Up(Up), Wp(), Hp(), ProjSize(ProjSize),
        ProjDist(ProjDist), FarClip(FarClip), Ws(), Hs(), ViewM(), ProjM(), VxP()
      {
      } /* End of 'camera' function */

      /* Set camera function.
       * ARGUMENTS:
       *   - camera location:
       *       vec3<Type> NewLoc;
       *   - camera direction:
       *       vec3<Type> NewAt;
       *   - camera up-vector:
       *       vec3<Type> NewUp;
       * RETURNS: None.
       */
      VOID Set( const vec3<Type> &NewLoc, const vec3<Type> &NewAt, const vec3<Type> &NewUp )
      {
        Loc = NewLoc, At = NewAt, Up = NewUp;

        ViewM = View(NewLoc, NewAt, NewUp);
        VxP = ViewM * ProjM;

        Right = vec3<Type>(ViewM.M[0][0], ViewM.M[1][0], ViewM.M[2][0]);
        Up = -vec3<Type>(ViewM.M[0][1], ViewM.M[1][1], ViewM.M[2][1]);
        Dir = -vec3<Type>(ViewM.M[0][2], ViewM.M[1][2], ViewM.M[2][2]);
      } /* End of 'Set' function */

      /* Resize camera function.
       * ARGUMENTS:
       *   - frame size:
       *       INT NewWs, NewHs;
       * RETURNS: None.
       */
      VOID Resize( INT NewWs, INT NewHs )
      {
        Ws = NewWs, Hs = NewHs;

        ProjSet();
      } /* End of 'Resize' function */

      /* Resize camera function.
       * ARGUMENTS:
       *   - projection size:
       *       Type Size;
       *   - distance to projection:
       *       Type ProjDist;
       *   - maximim distance far drawing scene:
       *       Type FarClip;
       * RETURNS: None.
       */
      VOID ProjSet( Type NewProjSize = 0.1, Type NewProjDist = 0.1, Type NewFarClip = 1000 )
      {
        ProjSize = NewProjSize, ProjDist = NewProjDist, FarClip = NewFarClip;

        // Correct aspect ratio
        Type rx = ProjSize * .5, ry = ProjSize * .5;
        if (Ws > Hs)
          rx *= (Type)Ws / Hs;
        else
          ry *= (Type)Hs / Ws;
        Wp = rx * 2, Hp = ry * 2;

        ProjM = Frustum(-rx, rx, -ry, ry, NewProjDist, NewFarClip);
        VxP = ViewM * ProjM;
      } /* End of 'ProjSet' function */

      /* Cast ray to frame function.
       * ARGUMENTS:
       *   - frame coordinates:
       *       Type Xs, Ys;
       * RETURNS: None.
       */
      ray<Type> CastRayToFrame( Type Xs, Type Ys ) const
      {
        vec3<Type> X =
          Dir * ProjDist +
          Right * (Xs - Ws * .5) / Ws * Wp +
          Up * (Hs * .5 - Ys) / Hs * Hp;

        return ray<Type>(Loc + X, X);
      } /* End of 'RayToFrame' function */

      /* Set view matrix function.
       * ARGUMENTS:
       *   - vectors for view:
       *       vec3<Type> Loc, At, Up;
       * RETURNS:
       *   (matr) view matrix.
       */
      static matr<Type> View( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up )
      {
        vec3<Type>
          Dir = (At - Loc).Normalizing(),
          Right = (Dir % Up).Normalizing(),
          Up1 = Right % Dir;

        return matr<Type>(Right.X, Up1.X, -Dir.X, 0,
                          Right.Y, Up1.Y, -Dir.Y, 0,
                          Right.Z, Up1.Z, -Dir.Z, 0,
                          -(Loc & Right), -(Loc & Up1), Loc & Dir, 1);
      } /* End of 'View' function */

      /* Set matrix of orthographic projection function.
       * ARGUMENTS:
       *   - grinds of projection cube:
       *       Type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr<Type>) matrix of orthographic projection.
       */
      static matr<Type> Ortho( Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far )
      {
        if (Right == Left || Top == Bottom || Far == Near)
          return matr::Identity();

        return matr<Type>(2 / (Right - Left), 0, 0, 0,
                          0, 2 / (Top - Bottom), 0, 0,
                          0, 0, -2 / (Far - Near), 0,
                         -(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom),
                         -(Far + Near) / (Far - Near), 1);
      } /* End of 'MatrOrtho' function*/

      /* Set view frustum matrix function.
       * ARGUMENTS:
       *   - grinds of projection cube:
       *       Type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr<Type>) view frustum matrix projection.
       */
      static matr<Type> Frustum( Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far )
      {
        if (Right == Left || Top == Bottom || Far == Near)
          return matr<Type>::Identity();

        return matr<Type>(2 * Near / (Right - Left), 0, 0, 0,
                          0, 2 * Near / (Top - Bottom), 0, 0,
                          (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),
                          -(Far + Near) / (Far - Near), -1,
                          0, 0, -2 * Far * Near / (Far - Near), 0);
      } /* End of 'MatrFrustum' function*/

    }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif // __mth_camera_h_

/* END OF 'mth_camera.h' FILE */