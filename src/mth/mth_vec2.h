/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Raytracing project.
 *               2D vector class implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include <cmath>

#include "mth_def.h"

namespace mth
{
  /* 2D vector type */
  template <typename Type = DBL>
    class vec2
    {
    public:
      Type X, Y; // Vector components

      /* Default constructor function.
       * ARGUMENTS: None;
       * RETURNS: None.
       */
      vec2<Type>() : X(), Y()
      {
      } /* End of 'vec2' function */

      /* Constructor by one value for all component function.
       * ARGUMENTS:
       *   - value:
       *       Type A;
       * RETURNS: None.
       */
      vec2<Type>( Type A ) : X(A), Y(A)
      {
      } /* End of 'vec2' function */

      /* Constructor by value for each component function.
       * ARGUMENTS:
       *   - values:
       *       Type A, B;
       * RETURNS: None.
       */
      vec2<Type>( Type A, Type B ) : X(A), Y(B)
      {
      } /* End of 'vec2' function */

      /* Coping constructor function.
       * ARGUMENTS:
       *   - reference at vector to copy:
       *       const vec2 &V;
       * RETURNS: None.
       */
      vec2<Type>( const vec2 &V ) : X(V.X), Y(V.Y)
      {
      } /* End of 'vec2' function */

      /* Get vector length function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (Type) vector length.
       */
      Type operator!() const
      {
        return sqrt(X * X + Y * Y);
      } /* End of 'operator!' function */
    
      /* Dot production function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) dot product result value.
       */
      Type operator&( const vec2 &V ) const
      {
        return X * V.X + Y * V.Y;
      } /* End of 'operator&' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const vec2 &V )
      {
        return vec2(X * V.X, Y * V.Y);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( const vec2 &V )
      {
        return vec2(X / V.X, Y / V.Y);
      } /* End of 'operator/' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( Type N )
      {
        return vec2(X * N, Y * N);
      } /* End of 'operator*' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( Type N )
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      vec2 & operator*=( const vec2 &V )
      {
        X *= V.X, Y *= V.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - reference at vector with coefficents:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & operator/=( const vec2 &V )
      {
        X /= V.X, Y /= V.Y;
        return *this;
      } /* End of 'operator/=' function */

      /* By-component production function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      vec2 & operator*=( Type N )
      {
        X *= N, Y *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* By-component divide function.
       * ARGUMENTS:
       *   - number:
       *       Type N;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & operator/=( Type N )
      {
        X /= N, Y /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Get negative vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec2) negative vector.
       */
      vec2 operator-() const
      {
        return vec2(-X, -Y);
      } /* End of 'operator-' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) add result vector.
       */
      vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) subtract result vector.
       */
      vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Add other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & operator+=( const vec2 &V )
      {
        X += V.X, Y += V.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract other vector from this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & operator-=( const vec2 &V )
      {
        X -= V.X, Y -= V.Y;
        return *this;
      } /* End of 'operator-=' function */

      /* Copy other vector to this function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & operator=( const vec2 &V )
      {
         X = V.X, Y = V.Y;
         return *this;
      } /* End of 'operator=' function */

      /* Get vector component by index function.
       * ARGUMENTS:
       *   - component index:
       *       const INT i;
       * RETURNS:
       *   (Type &) reference at component.
       */
      Type & operator[]( INT i ) const
      {
        if (i <= 0)
          return X;
        if (i >= 1)
          return Y;
      } /* End of 'operator[]' function */

      /* Get vector by it's type function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) poINTer at first component.
       */
      Type * operatorType( INT i ) const
      {
        return &X;
      } /* End of 'operatorType *' function */

      /* Normalize vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec2 &) self referense.
       */
      vec2 & Normalize()
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
       *   (vec2) normalized vector.
       */
      vec2 Normalizing() const
      {
        Type len = this->Length2();
        if (len == 1 || len == 0)
          return *this;
        else
          return vec2(X, Y) / sqrt(len);
      } /* End of 'Normalizing' function */

      /* Get square of vector length function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (Type) square of vector length.
       */
      Type Length2() const
      {
        return X * X + Y * Y;
      } /* End of 'Length2' function */

      /* Get distance beetween two vectors function.
       * ARGUMENTS:
       *   - reference at second vector:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) distance beetween two vectors.
       */
      Type Distance( const vec2 &V ) const
      {
        return !(*this - V);
      } /* End of 'Normalizing' function */

      /* Get zero vector function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec2) zero vector.
       */
      static vec2 Zero()
      {
        return vec2(0);
      } /* End of 'Zero' function */

      /* Get vector with random components from 0 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec2) random vector.
       */
      static vec2 Rnd0()
      {
        return vec2(R0(), R0());
      } /* End of 'Rnd0' function */

      /* Get vector with random components from -1 to 1 function.
       * ARGUMENTS: None;
       * RETURNS:
       *   (vec2) random vector.
       */
      static vec2 Rnd1()
      {
        return vec2(R1(), R1());
      } /* End of 'Rnd1' function */
    }; /* End of 'vec2' class */

} /* end of namespace mth */



#endif // __mth_vec2_h_
/* END OF 'mth_vec2.h' FILE */
