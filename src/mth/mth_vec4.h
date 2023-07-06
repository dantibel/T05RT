/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Raytracing project.
 *               4D vector class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 25.07.2022.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include <cmath>

#include "mth_def.h"

namespace mth
{
  /* 4D vector type */
  template <typename Type = DBL>
    class vec4
    {
    public:
      Type X, Y, Z, W; // Vector components

      /* Default constructor function.
       * ARGUMENTS: None;
       * RETURNS: None.
       */
      vec4<Type>() : X(), Y(), Z(), W()
      {
      } /* End of 'vec4' function */

      /* Constructor by one value for all component function.
       * ARGUMENTS:
       *   - value:
       *       Type A;
       * RETURNS: None.
       */
      vec4<Type>( Type A ) : X(A), Y(A), Z(A), W(A)
      {
      } /* End of 'vec4' function */

      /* Constructor by value for each component function.
       * ARGUMENTS:
       *   - values:
       *       Type A, B, C, D;
       * RETURNS: None.
       */
      vec4<Type>( Type A, Type B, Type C, Type D ) : X(A), Y(B), Z(C), W(D)
      {
      } /* End of 'vec4' function */

      /* Constructor by 3D vector function.
       * ARGUMENTS:
       *   - reference at 3D vector:
       *       const vec3<Type> &V;
       *   - W component:
       *       Type A;
       * RETURNS: None.
       */
      vec4<Type>( const vec3<Type> &V, Type A = 1 ) : X(V.X), Y(V.Y), Z(V.Z), W(A)
      {
      } /* End of 'vec4' function */

      /* Coping constructor function.
       * ARGUMENTS:
       *   - reference at vector to copy:
       *       const vec4 &V;
       * RETURNS: None.
       */
      vec4<Type>( const vec4 &V ) : X(V.X), Y(V.Y), Z(V.Z), W(V.W)
      {
      } /* End of 'vec4' function */

      /* Get vector length function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (Type) vector length.
       */
      Type operator!() const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */
    
      /* Dot production function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) dot product result value.
       */
      Type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + V.Z * Z;
      } /* End of 'operator&' function */

      /* Cross product function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) cross product result vector.
       */
      vec4 operator%( const vec4 &V ) const
      {
        return vec4(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator/( const vec4 &V ) const
      {
        return vec4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
      } /* End of 'operator/' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( Type N ) const
      {
        return vec4(X * N, Y * N, Z * N, W);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator/( Type N ) const
      {
        return vec4(X / N, Y / N, Z / N, W);
      } /* End of 'operator/' function */

      /* Multiply vector and matrix function.
       * ARGUMENTS:
       *   - reference at matrix to multiply:
       *       const matr<Type> &M;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const matr<Type> &M ) const
      {
        FLT w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + W * M.M[3][3];

        return vec4((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + W * M.M[3][0]) / w,
                    (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + W * M.M[3][1]) / w,
                    (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + W * M.M[3][2]) / w);
      } /* End of 'operator*' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      vec4 & operator*=( const vec4 &V )
      {
        X *= V.X, Y *= V.Y, Z *= V.Z, W *= V.W;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & operator/=( const vec4 &V )
      {
        X /= V.X, Y /= V.Y, Z /= V.Z, W /= V.W;
        return *this;
      } /* End of 'operator/=' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      vec4 & operator*=( Type N )
      {
        X *= N, Y *= N, Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & operator/=( Type N )
      {
        X /= N, Y /= N, Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Multiply vector and matrix function.
       * ARGUMENTS:
       *   - reference at matrix to multiply:
       *       const matr<Type> &M;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      vec4 operator*=( const matr<Type> &M )
      {
        FLT w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + W * M.M[3][3];

        return *this = vec4((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + W * M.M[3][0]) / w,
                            (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + W * M.M[3][1]) / w,
                            (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + W * M.M[3][2]) / w);
      } /* End of 'operator*=' function */

      /* Get negative vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4) negative vector.
       */
      vec4 operator-() const
      {
        return vec4(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) add result vector.
       */
      vec4 operator+( const vec4 &V ) const
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) subtract result vector.
       */
      vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Add other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & operator+=( const vec4 &V )
      {
        X += V.X, Y += V.Y, Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract other vector from this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & operator-=( const vec4 &V )
      {
        X -= V.X, Y -= V.Y, Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Copy other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & operator=( const vec4 &V )
      {
         X = V.X, Y = V.Y, Z = V.Z;
         return *this;
      } /* End of 'operator=' function */

      /* Get vector component by index function.
       * ARGUMENTS:
       *   - component index:
       *       INT i;
       * RETURNS:
       *   (Type &) reference at component.
       */
      Type & operator[]( INT i ) const
      {
        if (i <= 0)
          return X;
        if (i == 1)
          return Y;
        if (i >= 2)
          return Z;
      } /* End of 'operator[]' function */

      /* Get vector by it's type function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) poINTer at first component.
       */
      Type * operatorType() const
      {
        return &X;
      } /* End of 'operatorType *' function */

      /* Normalize vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4 &) self referense.
       */
      vec4 & Normalize()
      {
        Type len = this->Length2();
        if (len == 1 || len == 0)
          return *this;
        else
          return *this /= sqrt(len);
      } /* End of 'Normalize' function */

      /* Get normalized vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4) normalized vector.
       */
      vec4 Normalizing() const
      {
        Type len = this->Length2();
        if (len == 1 || len == 0)
          return *this;
        else
          return vec4(X, Y, Z) / sqrt(len);
      } /* End of 'Normalizing' function */

      /* Get square of vector length function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (Type) square of vector length.
       */
      Type Length2() const
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Length2' function */

      /* Get distance beetween two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) distance beetween two vectors.
       */
      Type Distance( const vec4 &V ) const
      {
        return !(*this - V);
      } /* End of 'Normalizing' function */

      /* Get zero vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4) zero vector.
       */
      static vec4 Zero()
      {
        return vec4(0);
      } /* End of 'Zero' function */

      /* Get vector with random components from 0 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4) random vector.
       */
      static vec4 Rnd0()
      {
        return vec4(R0(), R0(), R0());
      } /* End of 'Rnd0' function */

      /* Get vector with random components from -1 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec4) random vector.
       */
      static vec4 Rnd1()
      {
        return vec4(R1(), R1(), R1());
      } /* End of 'Rnd1' function */
    }; /* End of 'vec4' class */

} /* end of namespace mth */


#endif // __mth_vec4_h_
/* END OF 'mth_vec4.h' FILE */
