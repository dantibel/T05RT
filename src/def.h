/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Raytracing project.
 *               Default definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 22.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __def_h_
#define __def_h_

#include <vector>

#include <windows.h>
#include "commondf.h"

#include "mth/mth.h"

/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  // Class constructor
  __Dummy( VOID )
  { 
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* _DEBUG */

namespace dart
{
  /* Basic types definitions */
  typedef mth::vec2<DBL> vec2;
  typedef mth::vec3<DBL> vec3;
  typedef mth::vec4<DBL> vec4;
  typedef mth::matr<DBL> matr;
  typedef mth::ray<DBL> ray;
  typedef mth::camera<DBL> camera;

  /* Data stock type */
  template <typename Type>
    class stock : public std::vector<Type>
    {
    public:
      /* Class constructor */
      stock ( VOID )
      {
      } /* End of 'stock' function */

      /* Class constructor */
      stock ( std::initializer_list<Type> List )
      {
        for (auto i : List)
          this->push_back(i);
      } /* End of 'stock' function */

      /* Add data to stock function.
       * ARGUMENTS:
       *   - data to add:
       *       Type Data;
       * RETURNS:
       *   (scene &) self reference.
       */
      stock & operator<< ( Type Data )
      {
        this->push_back(Data);
        return *this;
      } /* End of 'operator<<' function */

      /* Call function for each element of stock function.
       * ARGUMENTS:
       *   - pointer at function to call:
       *       WalkType Walk;
       * RETURNS: None.
       */
      template <typename WalkType>
        VOID Walk( WalkType Walk )
        {
          for (auto &x : *this)
            Walk(x);
        } /* End of 'Walk' function */
    }; /* End of 'stock' class */
} /* end of 'dart' namespace*/

#ifdef _DEBUG
# ifdef _CRTDBG_MAP_ALLOC
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
# endif // _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#endif // __def_h_

/* END OF 'def.h' FILE */
