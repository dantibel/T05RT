/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : model.h
 * PURPOSE     : Raytracing project.
 *               model class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 28.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __model_h_
#define __model_h_

#include <cstdio>
#include <vector>
#include <fstream>

#include "rt/shapes/shape_def.h"
#include "rt/shapes/triangle.h"

namespace dart
{
    /* model model class */
    class model : public shape
    {
      cube *BoundBox;              // Model bound box
      stock<triangle *> Triangles; // Model triangles

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - model file name:
       *       const char *FileName;
       *   - references at model points:
       *      const vec3 P0, P1, P2;
       *   - reference at model color:
       *       const surface &Surface;
       */
      model( const char *FileName, const surface &Surface, mods_list *Modifiers = nullptr ) : shape(Surface, Modifiers), BoundBox(nullptr), Triangles()
      {
        FILE *F;
        INT nv = 0, ni = 0, NormI = 0;
        static CHAR Buf[10000];

        if ((F = fopen(FileName, "r")) == NULL)
          return;

        // count vertexes and indexes
        while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
        {
          if (Buf[0] == 'v' && Buf[1] == ' ')
            nv++;
          else if (Buf[0] == 'f' && Buf[1] == ' ')
          {
            CHAR *S = Buf + 2, oldc = ' ';
            INT cnt = 0;

            while (*S != 0)
              cnt += isspace((UCHAR)oldc) && !isspace((UCHAR)*S), oldc = *S++;
            ni += cnt - 2;
          }
        }
        rewind(F);

        struct vertex
        {
          vec3 P, N; // Vertex position and normal
        };
        std::vector<vertex> V;
        V.resize(nv);
        std::vector<INT> I;
        I.resize(ni * 3);
        //Triangles.resize(ni / 3);

        // fill triangles
        DBL Xmax = DBL_MIN, Xmin = DBL_MAX, Ymax = DBL_MIN, Ymin = DBL_MAX, Zmax = DBL_MIN, Zmin = DBL_MAX;
        nv = 0;
        ni = 0;
        while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
        {
          if (Buf[0] == 'v' && Buf[1] == ' ') // read vertexes
          {
            DBL X, Y, Z;

            sscanf(Buf + 2, "%lf%lf%lf", &X, &Y, &Z);
            V[nv++].P = vec3(X, Y, Z);

            // fill bound box coords
            if (X > Xmax)
              Xmax = X;
            else if (X < Xmin)
              Xmin = X;
            if (Y > Ymax)
              Ymax = Y;
            else if (Y < Ymin)
              Ymin = Y;
            if (Z > Zmax)
              Zmax = Z;
            else if (Z < Zmin)
              Zmin = Z;
          }
          else if (Buf[0] == 'f' && Buf[1] == ' ') // read indexes
          {
            CHAR *S = Buf + 2, oldc = ' ';
            INT n = 0, n0 = 0, n1 = 0, nc;

            while (*S != 0)
            {
              if (isspace((UCHAR)oldc) && !isspace((UCHAR)*S))
              {
                sscanf(S, "%d", &nc);
                if (nc > 0)
                  nc--;
                else
                  nc += nv;
                if (n == 0)
                  n0 = nc;
                else if (n == 1)
                  n1 = nc;
                else
                {
                  I[ni++] = n0;
                  I[ni++] = n1;
                  I[ni++] = nc;
                  n1 = nc;
                }
                n++;
              }
              oldc = *S++;
            }
          }
        }
        fclose(F);

        // eval normals
        for (INT i = 0; i < ni; i += 3)
        {
          vec3
            P0 = V[I[i]].P,
            P1 = V[I[i + 1]].P,
            P2 = V[I[i + 2]].P,
            N = ((P1 - P0) %  (P2 - P0)).Normalize();

          V[I[i]].N += N;
          V[I[i + 1]].N += N;
          V[I[i + 2]].N += N;

          Triangles.push_back(new triangle(V[I[i]].P, V[I[i + 1]].P, V[I[i + 2]].P, V[I[i]].N, V[I[i + 1]].N, V[I[i + 2]].N, SOLID_MTL(vec3(1, 0, 0))));
        }

        BoundBox = new cube(vec3(Xmin, Ymin, Zmin), vec3(Xmax, Ymax, Zmax), SOLID_MTL(vec3(0)));
      } /* End of 'model' functions */

      /* Class destructor */
      ~model( VOID )
      {
        Triangles.Walk(
          []( triangle *Trl )
          {
            delete Trl;
          });
        delete BoundBox;
      }/* End of '~model' function */

      /* Determine if point is inside model function.
       * ARGUMENTS:
       *   - reference at point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) TRUE if point inside model, FALSE overwise.
       */
      BOOL IsInside( const vec3 &P ) override
      {
        if (BoundBox->IsInside(P))
          for (auto t : Triangles)
            if (t->IsInside(P))
              return TRUE;
        return FALSE;
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
        if (BoundBox->IsIntersect(Ray))
          for (auto t : Triangles)
            if (t->IsIntersect(Ray))
              return TRUE;
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
      BOOL Intersect( const ray &Ray, intr *Intr ) override
      {
        intr best_in;
        if (BoundBox->IsIntersect(Ray))
        {
          Triangles.Walk(
            [&]( triangle *Trl )
            {
              intr in;
              if (Trl->Intersect(Ray, &in))
                if (best_in.Shp  == nullptr || best_in.T > in.T)
                  best_in = in;
            });
        }
        *Intr = best_in;
        Intr->Shp = this;
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
        INT intrs_count = 0;
        if (BoundBox->IsIntersect(Ray))
          Triangles.Walk(
            [&]( triangle *Trl )
            {
              intrs_count += Trl->AllIntersect(Ray, Intrs);
            });
        return intrs_count;
      } /* End of 'AllIntersect' function */
    }; /* End of 'model' class */
}/* end of 'dart' namespace */

#endif //__model_h_

/* END OF 'model.h' FILE */

