/* FILE NAME   : mth_matr.h
 * PURPOSE     : Raytracing project.
 *               Matrix class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'math'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

namespace mth
{
  /* 4x4 Matrix Type */
  template <typename Type = DBL>
    class matr
    {
    public:
      Type M[4][4];                 // Matrix elements
      mutable Type InvM[4][4];      // Inversed matrix elements
      mutable BOOL WasInvEvaluated; // Was inverse matrix evaluated flag

      /* Default constructor function.
       * ARGUMENTS: None;
       * RETURNS: None.
       */
      matr<Type>() : M{0}, InvM{0}, WasInvEvaluated(FALSE)
      {
      } /* End of 'matr' function */

      /* Constructor by all elements function.
       * ARGUMENTS:
       *   - elements:
       *       const Type A00, A01, A02, A03,
                          A10, A11, A12, A13,
                          A20, A21, A22, A23,
                          A30, A31, A32, A33;
       * RETURNS: None.
       */
      matr<Type>( Type A00, Type A01, Type A02, Type A03,
                  Type A10, Type A11, Type A12, Type A13,
                  Type A20, Type A21, Type A22, Type A23,
                  Type A30, Type A31, Type A32, Type A33 ) : M{ A00, A01, A02, A03,
                                                                A10, A11, A12, A13,
                                                                A20, A21, A22, A23,
                                                                A30, A31, A32, A33 }, InvM{0}, WasInvEvaluated(FALSE)
      {
      } /* End of 'matr' function */

      /* Constructor by elements array function.
       * ARGUMENTS:
       *   - elements array:
       *       const Type A[4][4];
       * RETURNS: None.
       */
      matr<Type>( const Type A[4][4] ) : M{A[0][0], A[0][1], A[0][2], A[0][3],
                                           A[1][0], A[1][1], A[1][2], A[1][3],
                                           A[2][0], A[2][1], A[2][2], A[2][3],
                                           A[3][0], A[3][1], A[3][2], A[3][3]}, InvM{0}, WasInvEvaluated(FALSE)
      {
      } /* End of 'matr' function */

    private:
      /* Get 3x3 matrix determinator function.
       * ARGUMENTS:
       *   - 3x3 matrix elements:
       *        const Type A11, A12, A13,
                           A21, A22, A23,
                           A31, A32, A33;
       * RETURNS:
       *   (Type) 3x3 matrix determinator.
       */
      static Type EvaluateDeterm3x3( const Type A11,  const Type A12,  const Type A13,
                                     const Type A21,  const Type A22,  const Type A23,
                                     const Type A31,  const Type A32,  const Type A33 )
      {

        return A11 * A22 * A33 +
               A12 * A23 * A31 + 
               A13 * A21 * A32 -
               A11 * A23 * A32 -
               A12 * A21 * A33 -
               A13 * A22 * A31;
      } /* End of 'Determ3x3' function */

    public:
     /* Copy other matrix to this function.
      * ARGUMENTS:
      *   - other matrix:
      *       const matr &M;
      * RETURNS:
      *   (matr &) self referense.
      */
      matr & operator=( const matr &X )
      {
        M[0][0] = X.M[0][0], M[0][1] = X.M[0][1], M[0][2] = X.M[0][2], M[0][3] = X.M[0][3];
        M[1][0] = X.M[1][0], M[1][1] = X.M[1][1], M[1][2] = X.M[1][2], M[1][3] = X.M[1][3];
        M[2][0] = X.M[2][0], M[2][1] = X.M[2][1], M[2][2] = X.M[2][2], M[2][3] = X.M[2][3];
        M[3][0] = X.M[3][0], M[3][1] = X.M[3][1], M[3][2] = X.M[3][2], M[3][3] = X.M[3][3];
        return *this;
      } /* End of 'operator=' function */

      /* Evaluate matrix determinator function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (Type) matrix determinator.
       */
      Type operator!() const
      {
        return
          +M[0][0] * EvaluateDeterm3x3(M[1][1], M[1][2], M[1][3],
                                       M[2][1], M[2][2], M[2][3],
                                       M[3][1], M[3][2], M[3][3]) +
          -M[0][1] * EvaluateDeterm3x3(M[1][0], M[1][2], M[1][3],
                                       M[2][0], M[2][2], M[2][3],
                                       M[3][0], M[3][2], M[3][3]) +
          +M[0][2] * EvaluateDeterm3x3(M[1][0], M[1][1], M[1][3],
                                       M[2][0], M[2][1], M[2][3],
                                       M[3][0], M[3][1], M[3][3]) +
          -M[0][3] * EvaluateDeterm3x3(M[1][0], M[1][1], M[1][2],
                                       M[2][0], M[2][1], M[2][2],
                                       M[3][0], M[3][1], M[3][2]);
      } /* End of 'operator!' function */

      /* Evaluate inverse matrix function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (matr) inversed matrix.
       */
      matr EvaluateInverse() const
      {
        if (WasInvEvaluated)
          return matr(InvM);

        WasInvEvaluated = TRUE;
        DBL det = !*this;
        if (det == 0)
          return Identity();

        InvM[0][0] =
          +EvaluateDeterm3x3(M[1][1], M[1][2], M[1][3],
                             M[2][1], M[2][2], M[2][3],
                             M[3][1], M[3][2], M[3][3]) / det;
        InvM[0][1] =
          -EvaluateDeterm3x3(M[1][0], M[1][2], M[1][3],
                             M[2][0], M[2][2], M[2][3],
                             M[3][0], M[3][2], M[3][3]) / det;
        InvM[0][2] =
          +EvaluateDeterm3x3(M[1][0], M[1][1], M[1][3],
                             M[2][0], M[2][1], M[2][3],
                             M[3][0], M[3][1], M[3][3]) / det;
        InvM[0][3] =
          -EvaluateDeterm3x3(M[1][0], M[1][1], M[1][2],
                             M[2][0], M[2][1], M[2][2],
                             M[3][0], M[3][1], M[3][2]) / det;

        InvM[1][0] =
          -EvaluateDeterm3x3(M[0][1], M[0][2], M[0][3],
                             M[2][1], M[2][2], M[2][3],
                             M[3][1], M[3][2], M[3][3]) / det;
        InvM[1][1] =
          +EvaluateDeterm3x3(M[0][0], M[0][2], M[0][3],
                             M[2][0], M[2][2], M[2][3],
                             M[3][0], M[3][2], M[3][3]) / det;
        InvM[1][2] =
          -EvaluateDeterm3x3(M[0][0], M[0][1], M[0][3],
                             M[2][0], M[2][1], M[2][3],
                             M[3][0], M[3][1], M[3][3]) / det;
        InvM[1][3] =
          +EvaluateDeterm3x3(M[0][0], M[0][1], M[0][2],
                             M[2][0], M[2][1], M[2][2],
                             M[3][0], M[3][1], M[3][2]) / det;

        InvM[2][0] =
          +EvaluateDeterm3x3(M[0][1], M[0][2], M[0][3],
                             M[1][1], M[1][2], M[1][3],
                             M[3][1], M[3][2], M[3][3]) / det;
        InvM[2][1] =
          -EvaluateDeterm3x3(M[0][0], M[0][2], M[0][3],
                             M[1][0], M[1][2], M[1][3],
                             M[3][0], M[3][2], M[3][3]) / det;
        InvM[2][2] =
          +EvaluateDeterm3x3(M[0][0], M[0][1], M[0][3],
                             M[1][0], M[1][1], M[1][3],
                             M[3][0], M[3][1], M[3][3]) / det;
        InvM[2][3] =
          -EvaluateDeterm3x3(M[0][0], M[0][1], M[0][2],
                             M[1][0], M[1][1], M[1][2],
                             M[3][0], M[3][1], M[3][2]) / det;

        InvM[3][0] =
          -EvaluateDeterm3x3(M[0][1], M[0][2], M[0][3],
                             M[1][1], M[1][2], M[1][3],
                             M[2][1], M[2][2], M[2][3]) / det;
        InvM[3][1] =
          +EvaluateDeterm3x3(M[0][0], M[0][2], M[0][3],
                             M[1][0], M[1][2], M[1][3],
                             M[2][0], M[2][2], M[2][3]) / det;
        InvM[3][2] =
          -EvaluateDeterm3x3(M[0][0], M[0][1], M[0][3],
                             M[1][0], M[1][1], M[1][3],
                             M[2][0], M[2][1], M[2][3]) / det;
        InvM[3][3] =
          +EvaluateDeterm3x3(M[0][0], M[0][1], M[0][2],
                             M[1][0], M[1][1], M[1][2],
                             M[2][0], M[2][1], M[2][2]) / det;

        return matr(InvM);
      } /* End of 'Inverse' function */

      /* Get identity matrix function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (matr) identity matrix.
       */
      static matr Identity()
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Set translate matrix for vector function.
       * ARGUMENTS:
       *   - reference at vector:
       *       const vec &T;
       * RETURNS:
       *   (matr) translate matrix.
       */
      static matr Translate( const vec3<Type> &T )
      {
        matr M = Identity();

        M.M[3][0] = T.X;
        M.M[3][1] = T.Y;
        M.M[3][2] = T.Z;
        return M;
      } /* End of 'Translate' function */

      /* Set scale matrix for vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &S;
       * RETURNS:
       *   (matr) scale matrix.
       */
      static matr Scale( const vec3<Type> &S )
      {
        matr M = Identity();

        M.M[0][0] = S.X;
        M.M[1][1] = S.Y;
        M.M[2][2] = S.Z;
        return M;
      } /* End of 'Scale' function */

      /* Set rotate around X-vector matrix for vector function.
       * ARGUMENTS:
       *   - angle:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) rotation matrix.
       */
      static matr RotateX( FLT AngleInDegree )
      {
        Type A = D2R(AngleInDegree), s = sin(A), c = cos(A);
        matr M = Identity();

        M.M[1][1] = c;
        M.M[1][2] = s;
        M.M[2][1] = -s;
        M.M[2][2] = c;
        return M;
      } /* End of 'RotateX' function */

      /* Set rotate around Y-vector matrix for vector function.
       * ARGUMENTS:
       *   - angle:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) rotation matrix.
       */
      static matr RotateY( FLT AngleInDegree )
      {
        FLT A = static_cast<FLT>(D2R(AngleInDegree)), s = sin(A), c = cos(A);
        matr M = Identity();

        M.M[0][0] = c;
        M.M[0][2] = -s;
        M.M[2][0] = s;
        M.M[2][2] = c;
        return M;
      } /* End of 'RotateY' function */

      /* Set rotate around Z-vector matrix for vector function.
       * ARGUMENTS:
       *   - angle:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) rotation matrix.
       */
      static matr RotateZ( FLT AngleInDegree )
      {
        FLT A = D2R(AngleInDegree), s = sin(A), c = cos(A);
        matr M = Identity();

        M.M[0][0] = c;
        M.M[0][1] = s;
        M.M[1][0] = -s;
        M.M[1][1] = c;
        return M;
      } /* End of 'RotateZ' function */

      /* Set rotate around custom vector matrix for vector function.
       * ARGUMENTS:
       *   - rotate by vector:
       *       const vec3 &R;
       *   - angle:
       *       Type AngleInDegre;
       * RETURNS:
       *   (matr) rotation matrix.
       */
      static matr Rotate( const vec3<Type> &R, FLT AngleInDegree )
      {
        FLT A = D2R(AngleInDegree), s = sin(A), c = cos(A);
        R.Normalize();
        matr M(c + R.X * R.X * (1 - c), R.X * R.Y * (1 - c) + R.Z * s, R.X * R.Z * (1 - c) + R.Z * s, 0,
               R.Y * R.X * (1 - c) - R.Z * s, c + R.Y * R.Y * (1 - c), R.Y * R.Y * (1 - c) + R.X * s, 0,
               R.Z * R.X * (1 - c) + R.Y * s, R.Z * R.Y * (1 - c) - R.X * s, c + R.Z * R.Z * (1 - c), 0,
               0, 0, 0, 1);
        return M;
      } /* End of 'Rotate' function */

      /* Transpose matrix function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (matr &) Transpossed matrix.
       */
      matr & Transpose()
      {
        return *this = matr(M[0][0], M[1][0], M[2][0], M[3][0],
                            M[0][1], M[1][1], M[2][1], M[3][1],
                            M[0][2], M[1][2], M[2][2], M[3][2],
                            M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transpose' function */

      /* Transpose matrix function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (matr) Transpossed matrix.
       */
      matr Transpossing() const
      {
        return matr(M[0][0], M[1][0], M[2][0], M[3][0],
                    M[0][1], M[1][1], M[2][1], M[3][1],
                    M[0][2], M[1][2], M[2][2], M[3][2],
                    M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transpose' function */

      /* Multiplicate two matrices function.
       * ARGUMENTS:
       *   - reference at second  metrix:
       *       const matr &M;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr &X )
      {
        INT i, j, k;
        matr R;

        
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++)
              R.M[i][j] += M[i][k] * X.M[k][j];
        

        /*
        R.M[0]  = M[0] * M.M[0]  + M[4] * M.M[1]  + M[8] * M.M[2]   + M[12] * M.M[3];
        R.M[4]  = M[0] * M.M[4]  + M[4] * M.M[5]  + M[8] * M.M[6]   + M[12] * M.M[7];
        R.M[8]  = M[0] * M.M[8]  + M[4] * M.M[9]  + M[8] * M.M[10]  + M[12] * M.M[11];
        R.M[12] = M[0] * M.M[12] + M[4] * M.M[13] + M[8] * M.M[14]  + M[12] * M.M[15];

        R.M[1]  = M[1] * M.M[0]  + M[5] * M.M[1]  + M[9] * M.M[2]   + M[13] * M.M[3];
        R.M[5]  = M[1] * M.M[4]  + M[5] * M.M[5]  + M[9] * M.M[6]   + M[13] * M.M[7];
        R.M[9]  = M[1] * M.M[8]  + M[5] * M.M[9]  + M[9] * M.M[10]  + M[13] * M.M[11];
        R.M[13] = M[1] * M.M[12] + M[5] * M.M[13] + M[9] * M.M[14]  + M[13] * M.M[15];

        R.M[2]  = M[2] * M.M[0]  + M[6] * M.M[1]  + M[10] * M.M[2]  + M[14] * M.M[3];
        R.M[6]  = M[2] * M.M[4]  + M[6] * M.M[5]  + M[10] * M.M[6]  + M[14] * M.M[7];
        R.M[10] = M[2] * M.M[8]  + M[6] * M.M[9]  + M[10] * M.M[10] + M[14] * M.M[11];
        R.M[14] = M[2] * M.M[12] + M[6] * M.M[13] + M[10] * M.M[14] + M[14] * M.M[15];

        R.M[3]  = M[3] * M.M[0]  + M[7] * M.M[1]  + M[11] * M.M[2]  + M[15] * M.M[3];
        R.M[7]  = M[3] * M.M[4]  + M[7] * M.M[5]  + M[11] * M.M[6]  + M[15] * M.M[7];
        R.M[11] = M[3] * M.M[8]  + M[7] * M.M[9]  + M[11] * M.M[10] + M[15] * M.M[11];
        R.M[15] = M[3] * M.M[12] + M[7] * M.M[13] + M[11] * M.M[14] + M[15] * M.M[15];
        */
        return R;
      } /* End of 'operator*' function */

      /* Multiplicate two matrices function.
       * ARGUMENTS:
       *   - reference at second  metrix:
       *       const matr &M;
       * RETURNS:
       *   (matr &) self reference.
       */
      matr & operator*=( const matr &M )
      {
        INT i, j, k;
        matr R;

        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++)
              R.M[i][j] += M[i][k] * M.M[k][j];

        return *this = R;
      } /* End of 'operator*=' function */

      /* Transform poINT by matrix function.
       * ARGUMENTS:
       *   - reference at poINT to transform:
       *       const vec3<Type> &P;
       * RETURNS:
       *   (vec3<Type>) result poINT.
       */
      vec3<Type> PointTransform( const vec3<Type> &P )
      {
        return vec3<Type>(P.X * M[0][0] + P.Y * M[1][0] + P.Z * M[2][0] + M[3][0],
                          P.X * M[0][1] + P.Y * M[1][1] + P.Z * M[2][1] + M[3][1],
                          P.X * M[0][2] + P.Y * M[1][2] + P.Z * M[2][2] + M[3][2]);
      } /* End of 'PointTransform' function */

      /* Transform normal by matrix function.
       * ARGUMENTS:
       *   - reference at normal to transform:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (vec3<Type>) result normal.
       */
      vec3<Type> NormalTransform( const vec3<Type> &N )
      {
        EvaluateInverse();
        return vec3<Type>(N.X * InvM[0][0] + N.Y * InvM[1][0] + N.Z * InvM[2][0],
                          N.X * InvM[0][1] + N.Y * InvM[1][1] + N.Z * InvM[2][1],
                          N.X * InvM[0][2] + N.Y * InvM[1][2] + N.Z * InvM[2][2]);
      } /* End of 'NormalTransform' function */

      /* Transform vector by matrix function.
       * ARGUMENTS:
       *   - reference at vector to transform:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator*( const vec3<Type> &V )
      {
        Type w = V.X * (*this).M[0][3] + V.Y * (*this).M[1][3] + V.Z * (*this).M[2][3] + (*this).M[3][3];

        return vec3<Type>((V.X * (*this).M[0][0] + V.Y * (*this).M[1][0] + V.Z * (*this).M[2][0] + (*this).M[3][0]) / w,
                          (V.X * (*this).M[0][1] + V.Y * (*this).M[1][1] + V.Z * (*this).M[2][1] + (*this).M[3][1]) / w,
                          (V.X * (*this).M[0][2] + V.Y * (*this).M[1][2] + V.Z * (*this).M[2][2] + (*this).M[3][2]) / w);
      } /* End of 'operator*' function */

      /* Transform vector by matrix function.
       * ARGUMENTS:
       *   - reference at vector to transform:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> Transform4x4( const vec3<Type> &V )
      {
        FLT w = V.X * (*this).M[0][3] + V.Y * (*this).M[1][3] + V.Z * (*this).M[2][3] + (*this).M[3][3];

        return vec3<Type>((V.X * (*this).M[0][0] + V.Y * (*this).M[1][0] + V.Z * (*this).M[2][0] + (*this).M[3][0]) / w,
                          (V.X * (*this).M[0][1] + V.Y * (*this).M[1][1] + V.Z * (*this).M[2][1] + (*this).M[3][1]) / w,
                          (V.X * (*this).M[0][2] + V.Y * (*this).M[1][2] + V.Z * (*this).M[2][2] + (*this).M[3][2]) / w);
      } /* End of 'Transform4x4' function */
    }; /* End of 'matr' class */

} /* end of namespace mth */

#endif // __mth_matr_h_
/* END OF 'mth_matr.h' FILE */
