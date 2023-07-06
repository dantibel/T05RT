/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Raytracing project.
 *               3D vector class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include <cmath>

#include "mth_def.h"

namespace mth
{
  /* 3D vector type */
  template <typename Type = DBL>
    class vec3
    {
    public:
      Type X, Y, Z; // Vector components

      /* Default constructor function.
       * ARGUMENTS: None;
       * RETURNS: None.
       */
      vec3<Type>() : X(), Y(), Z()
      {
      } /* End of 'vec3' function */

      /* Constructor by one value for all component function.
       * ARGUMENTS:
       *   - value:
       *       Type A;
       * RETURNS: None.
       */
      vec3<Type>( Type A ) : X(A), Y(A), Z(A)
      {
      } /* End of 'vec3' function */

      /* Constructor by value for each component function.
       * ARGUMENTS:
       *   - values:
       *       Type A, B, C;
       * RETURNS: None.
       */
      vec3<Type>( Type A, Type B, Type C ) : X(A), Y(B), Z(C)
      {
      } /* End of 'vec3' function */

      /* Coping constructor function.
       * ARGUMENTS:
       *   - reference at vector to copy:
       *       const vec3 &V;
       * RETURNS: None.
       */
      vec3<Type>( const vec3 &V ) : X(V.X), Y(V.Y), Z(V.Z)
      {
      } /* End of 'vec3' function */

      /* Constructor by 4D vector function.
       * ARGUMENTS:
       *   - reference at 4D vector:
       *       const vec4<Type> &V;
       * RETURNS: None.
       */
      vec3<Type>( const vec4<Type> &V ) : X(V.X), Y(V.Y), Z(V.Z)
      {
      } /* End of 'vec3' function */

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
       *       const vec3 &V;
       * RETURNS:
       *   (Type) dot product result value.
       */
      Type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + V.Z * Z;
      } /* End of 'operator&' function */

      /* Cross product function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) cross product result vector.
       */
      vec3 operator%( const vec3 &V ) const
      {
        return vec3(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator/( const vec3 &V ) const
      {
        return vec3(X / V.X, Y / V.Y, Z / V.Z);
      } /* End of 'operator/' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( Type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator/( Type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Multiply vector and matrix function.
       * ARGUMENTS:
       *   - reference at matrix to multiply:
       *       const matr<Type> &M;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const matr<Type> &M ) const
      {
        FLT w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + M.M[3][3];

        return vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0]) / w,
                    (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1]) / w,
                    (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]) / w);
      } /* End of 'operator*' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec3 & operator*=( const vec3 &V )
      {
        X *= V.X, Y *= V.Y, Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & operator/=( const vec3 &V )
      {
        X /= V.X, Y /= V.Y, Z /= V.Z;
        return *this;
      } /* End of 'operator/=' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec3 & operator*=( Type N )
      {
        X *= N, Y *= N, Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & operator/=( Type N )
      {
        X /= N, Y /= N, Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Multiply vector and matrix function.
       * ARGUMENTS:
       *   - reference at matrix to multiply:
       *       const matr<Type> &M;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec3 operator*=( const matr<Type> &M )
      {
        FLT w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + M.M[3][3];

        return *this = vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0]) / w,
                            (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1]) / w,
                            (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]) / w);
      } /* End of 'operator*=' function */

      /* Get negative vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec3) negative vector.
       */
      vec3 operator-() const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) add result vector.
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) subtract result vector.
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Add other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & operator+=( const vec3 &V )
      {
        X += V.X, Y += V.Y, Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract other vector from this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & operator-=( const vec3 &V )
      {
        X -= V.X, Y -= V.Y, Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Copy other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & operator=( const vec3 &V )
      {
         X = V.X, Y = V.Y, Z = V.Z;
         return *this;
      } /* End of 'operator=' function */

      /* Compare two vectors function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) TRUE if these vectors are equal, FALSE overwise.
       */
      BOOL & operator==( const vec3 &V ) const
      {
         return X == V.X && Y == V.Y && Z == V.Z;
      } /* End of 'operator==' function */

      /* Get vector component by index function.
       * ARGUMENTS:
       *   - component index:
       *       INT i;
       * RETURNS:
       *   (Type &) reference at component.
       */
      const Type & operator[]( INT i ) const
      {
        if (i <= 0)
          return X;
        else if (i == 1)
          return Y;
        else
          return Z;
      } /* End of 'operator[]' function */

      /* Get vector by it's type function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) Pointer at first component.
       */
      Type * operatorType() const
      {
        return &X;
      } /* End of 'operatorType *' function */

      /* Normalize vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec3 &) self referense.
       */
      vec3 & Normalize()
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
       *   (vec3) normalized vector.
       */
      vec3 Normalizing() const
      {
        Type len = this->Length2();
        if (len == 1 || len == 0)
          return *this;
        else
          return vec3(X, Y, Z) / sqrt(len);
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
       *       const vec3 &V;
       * RETURNS:
       *   (Type) distance beetween two vectors.
       */
      Type Distance( const vec3 &V ) const
      {
        return !(*this - V);
      } /* End of 'Distance' function */

      /* Get maximal vector component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) Maximal component.
       */
      Type MaxComp() const
      {
        return COM_MAX(X, COM_MAX(Y, Z));
      } /* End of 'MaxComp' function */

      /* Get minimal vector component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) Minimal component.
       */
      Type MinComp() const
      {
        return COM_MIN(X, COM_MIN(Y, Z));
      } /* End of 'MinComp' function */

      /* Get zero vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec3) zero vector.
       */
      static vec3 Zero()
      {
        return vec3(0);
      } /* End of 'Zero' function */

      /* Get vector with random components from 0 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec3) random vector.
       */
      static vec3 Rnd0()
      {
        return vec3(R0(), R0(), R0());
      } /* End of 'Rnd0' function */

      /* Get vector with random components from -1 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec3) random vector.
       */
      static vec3 Rnd1()
      {
        return vec3(R1(), R1(), R1());
      } /* End of 'Rnd1' function */
    }; /* End of 'vec3' class */

} /* end of namespace mth */

#endif // __mth_vec3_h_
/* END OF 'mth_vec3.h' FILE */
