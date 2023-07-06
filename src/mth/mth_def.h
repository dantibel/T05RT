/* FILE NAME   : mthdef.h
 * PURPOSE     : Raytracing project.
 *               Default math definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __mthdef_h_
#define __mthdef_h_

// Basic floating point types
typedef DOUBLE DBL;
typedef FLOAT FLT;

// Get random numbers macroses
#define R0() ((DBL)rand() / RAND_MAX)         // Get random number from 0 to 1
#define R1() (2 * (DBL)rand() / RAND_MAX - 1) // Get random number from -1 to 1

// Angle covertor macroses
const DBL PI = 3.14159265358979323846; // Pi number;
#define D2R(A) ((A) * (PI / 180.0))    // Degrees to radians
#define R2D(A) ((A) * (180.0 / PI))    // radians to degrees

// Space geometry types
template <typename Type = DBL> class vec2;
template <typename Type = DBL> class vec3;
template <typename Type = DBL> class vec4;
template <typename Type = DBL> class matr;
template <typename Type = DBL> class ray;

#endif // __mthdef_h_
/* END OF 'mthdef.h' FILE */
