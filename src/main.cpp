/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Raytracing project.
 *               Main startup module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Danil Belov.
 * LAST UPDATE : 22.07.2022.
 * NOTE        : Module namespace 'dart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include <string>
#include <map>
#include <vector>

#include "def.h"
#include "mth/mth.h"
#include "win/win.h"
#include "rt/rt.h"
#include "rt/shapes/shape.h"

/* Scene examples */
#define SCENE_RAND_SPHERES() for (INT i = 0; i < 50; i++) \
                               MyRT.Scene << new dart::sphere(dart::vec3::Rnd1() * 10, ((DBL)rand() / RAND_MAX + .5), SOLID_MTL(dart::vec3::Rnd0() * 2)); \
                             for (INT i = 0; i < 10; i++) \
                               MyRT.Scene << new dart::lgh::point(dart::vec3::Rnd1() * 10, dart::vec3::Rnd0()); \
                             MyRT.Scene << new dart::plane(dart::vec3(1, 10, 0), dart::vec3(0, 10, 0), dart::vec3(0, 10, 1), dart::surface(dart::vec3(.5), dart::vec3(.5 * .8), dart::vec3(.2), .1, 0, 17));

#define SCENE_COORDS() MyRT.Scene << \
                         new dart::sphere(dart::vec3(5, 0, 0), 1, SOLID_MTL(dart::vec3(1, 0, 0))) << \
                         new dart::sphere(dart::vec3(0, 5, 0), 1, SOLID_MTL(dart::vec3(0, 1, 0))) << \
                         new dart::sphere(dart::vec3(0, 0, 5), 1, SOLID_MTL(dart::vec3(0, 0, 1))) <<  \
                         new dart::cube(dart::vec3(-1), dart::vec3(1), MtlLib["Black Plastic"]) << \
                         new dart::plane(dart::vec3(1, 5, 0), dart::vec3(0, 5, 0), dart::vec3(0, 5, 1), dart::surface(dart::vec3(.5), dart::vec3(.5 * .8), dart::vec3(.2), .1, 0, 17)) << \
                         new dart::lgh::direct(dart::vec3(1, 1, 1), dart::vec3(1));

#define SCENE_CSG() dart::mods_list Mods {new dart::cheker(5)}; \
                    MyRT.Scene << \
                      new dart::lgh::direct(dart::vec3(1, 1, 1), dart::vec3(1)) << \
                      new dart::plane(dart::vec3(1, 10, 0), dart::vec3(0, 10, 0), dart::vec3(0, 10, 1), dart::surface(dart::vec3(.5), dart::vec3(.5 * .8), dart::vec3(.2), .1, 0, 17), &Mods) << \
                      new dart::csg::substract(new dart::cube(dart::vec3(-1.4), dart::vec3(1.4), SOLID_MTL(dart::vec3(.7))), new dart::sphere(dart::vec3(0), 1.8, SOLID_MTL(dart::vec3(0, 0, 1)))) << \
                      new dart::sphere(dart::vec3(0), 1, MtlLib["Emerald"]) << \
                      new dart::csg::intersection(new dart::cube(dart::vec3(5, -1, -1), dart::vec3(7, 1, 1), MtlLib["Bronze"]), new dart::sphere(dart::vec3(6, 0, 0), 1.3, MtlLib["Polished Bronze"])) << \
                      new dart::csg::intersection(new dart::cube(dart::vec3(-7, -1, -1), dart::vec3(-5, 1, 1), MtlLib["Bronze"]), new dart::sphere(dart::vec3(-6, 0, 0), 1.3, MtlLib["Polished Bronze"])) << \
                      new dart::csg::intersection(new dart::cube(dart::vec3(-1, -1, 5), dart::vec3(1, 1, 7), MtlLib["Bronze"]), new dart::sphere(dart::vec3(0, 0, 6), 1.3, MtlLib["Polished Bronze"])) << \
                      new dart::csg::intersection(new dart::cube(dart::vec3(-1, -1, -7), dart::vec3(1, 1, -5), MtlLib["Bronze"]), new dart::sphere(dart::vec3(0, 0, -6), 1.3, MtlLib["Polished Bronze"]));

#define SCENE_REFL() dart::mods_list Mods {new dart::cheker(5)}; \
                     MyRT.Scene << \
                       new dart::lgh::direct(dart::vec3(0, 1, 1), dart::vec3(1, 1, 0)) << \
                       new dart::plane(dart::vec3(1, 2, 0), dart::vec3(0, 2, 0), dart::vec3(0, 2, 1), dart::surface(dart::vec3(.2), dart::vec3(.8), dart::vec3(.2), .1, 0, 17), &Mods) << \
                       new dart::sphere(dart::vec3(0, 3, 0), 2, MtlLib["Ruby"]);

#define SCENE_REFR() dart::mods_list Mods {new dart::cheker(5)}; \
                     MyRT.Scene << \
                       new dart::lgh::direct(dart::vec3(3, 3, 1), dart::vec3(1)) << \
                       new dart::cube(dart::vec3(-1, -1, 4), dart::vec3(1, 1, 6), SOLID_MTL(dart::vec3(0, 0, 1))) << \
                       new dart::cube(dart::vec3(-1, -1, -6), dart::vec3(1, 1, -4), SOLID_MTL(dart::vec3(1, 1, 0))) << \
                       new dart::cube(dart::vec3(4, -1, -1), dart::vec3(6, 1, 1), SOLID_MTL(dart::vec3(0, 1, 0))) << \
                       new dart::cube(dart::vec3(-6, -1, -1), dart::vec3(-4, 1, 1), SOLID_MTL(dart::vec3(1, 0, 0))) << \
                       new dart::sphere(dart::vec3(0, 3, 0), 2, dart::surface(dart::vec3(.3, .47, .8), dart::vec3(0), dart::vec3(0), 0, 0.1, 28)) << \
                       new dart::plane(dart::vec3(1, 10, 0), dart::vec3(0, 10, 0), dart::vec3(0, 10, 1), dart::surface(dart::vec3(.5), dart::vec3(.5 * .8), dart::vec3(.2), .1, 0, 17), &Mods);

// Some surfaces materials
std::map<std::string, dart::surface> MtlLib
  {
    {"Black Plastic",   {{0.0, 0.0, 0.0},              {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                 0, 0, 32}},
    {"Brass",           {{0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843},    0, 0, 27.8974}},
    {"Bronze",          {{0.2125,0.1275,0.054},        {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},    0, 0, 25.6}},
    {"Chrome",          {{0.25, 0.25, 0.25},           {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597},  0, 0, 76.8}},
    {"Copper",          {{0.19125,0.0735,0.0225},      {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},    0, 0, 12.8}},
    {"Gold",            {{0.24725,0.1995,0.0745},      {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},    0, 0, 51.2}},
    {"Peweter",         {{0.10588,0.058824,0.113725},  {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},        0, 0, 9.84615}},
    {"Silver",          {{0.19225,0.19225,0.19225},    {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},    0, 0, 51.2}},
    {"Polished Silver", {{0.23125,0.23125,0.23125},    {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},    0, 0, 89.6}},
    {"Turquoise",       {{0.1, 0.18725, 0.1745},       {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678},   0, 0, 12.8}},
    {"Ruby",            {{0.1745, 0.01175, 0.01175},   {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959},  0.1, 0, 76.8}},
    {"Polished Gold",   {{0.24725, 0.2245, 0.0645},    {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006},  0, 0, 83.2}},
    {"Polished Bronze", {{0.25, 0.148, 0.06475},       {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621},  0, 0, 76.8}},
    {"Polished Copper", {{0.2295, 0.08825, 0.0275},    {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 0, 0, 51.2}},
    {"Jade",            {{0.135, 0.2225, 0.1575},      {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228},  0, 0, 12.8}},
    {"Obsidian",        {{0.05375, 0.05, 0.06625},     {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435},  0, 0, 38.4}},
    {"Pearl",           {{0.25, 0.20725, 0.20725},     {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648},  0, 0, 11.264}},
    {"Emerald",         {{0.0215, 0.1745, 0.0215},     {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},        0.005, 0, 76.8}},
    {"Black Rubber",    {{0.02, 0.02, 0.02},           {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                 0, 0, 10.0}},
  };

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *         CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
   */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  dart::rt MyRT(hInstance);

  SCENE_RAND_SPHERES();

#if 0
  MyRT.Scene <<
    //new dart::sphere(dart::vec3(5, 0, 0), 1, SOLID_MTL(dart::vec3(1, 0, 0))) <<
    //new dart::sphere(dart::vec3(0, 5, 0), 1, SOLID_MTL(dart::vec3(0, 1, 0))) <<
    //new dart::sphere(dart::vec3(0, 0, 5), 1, SOLID_MTL(dart::vec3(0, 0, 1))) <<
    //new dart::cube(dart::vec3(-1), dart::vec3(1), dart::surface(dart::vec3(.1), dart::vec3(.64), dart::vec3(.5), .1, 0, 30)) <<
    //(new dart::plane(dart::vec3(1, 10, 0), dart::vec3(0, 10, 0), dart::vec3(0, 10, 1), dart::surface(dart::vec3(.5), dart::vec3(.6), dart::vec3(.2), .1, 0, 17)))->operator[](new dart::cheker(5)) <<
    //new dart::lgh::point(dart::vec3(0), dart::vec3(1, 1, 0)) <<
    //new dart::lgh::spot(dart::vec3(0, 8, 8), dart::vec3(0, 1, 1), 10, 20, dart::vec3(1)) <<
    //new dart::csg::substract(new dart::cube(dart::vec3(-1.4), dart::vec3(1.4), SOLID_MTL(dart::vec3(.7))), new dart::sphere(dart::vec3(0), 1.8, SOLID_MTL(dart::vec3(0, 0, 1)))) <<
    //new dart::lgh::direct(dart::vec3(-1, 1, -1), dart::vec3(1)) <<
    //new dart::triangle(dart::vec3(2, 0, 0), dart::vec3(-2, 0, 0), dart::vec3(0, 3, 0), SOLID_MTL(dart::vec3(1, 0, 1)));
    //new dart::model("./bin/cow.obj", SOLID_MTL(dart::vec3(1, 0, 1)));
    //new dart::cube(dart::vec3(-1, -1, 4), dart::vec3(1, 1, 6), SOLID_MTL(dart::vec3(0, 0, 1))) <<
    //new dart::cube(dart::vec3(-1, -1, -6), dart::vec3(1, 1, -4), SOLID_MTL(dart::vec3(1, 1, 0))) <<
    //new dart::cube(dart::vec3(4, -1, -1), dart::vec3(6, 1, 1), SOLID_MTL(dart::vec3(0, 1, 0))) <<
    //(new dart::cube(dart::vec3(-6, -1, -1), dart::vec3(-4, 1, 1), SOLID_MTL(dart::vec3(1, 0, 0))))->operator[](new dart::rotator(10)) <<
    //new dart::sphere(dart::vec3(0, 3, 0), 2, dart::surface(dart::vec3(0, .17, .5), dart::vec3(0), dart::vec3(.9), 0, .1, 47));
    //new dart::csg::intersection(new dart::cube(dart::vec3(5, -1, -1), dart::vec3(7, 1, 1), SOLID_MTL(dart::vec3(1, 0, 0))), new dart::sphere(dart::vec3(6, 0, 0), 1.3, SOLID_MTL(dart::vec3(0, 1, 0)))) <<
    //new dart::csg::intersection(new dart::cube(dart::vec3(-7, -1, -1), dart::vec3(-5, 1, 1), SOLID_MTL(dart::vec3(1, 0, 0))), new dart::sphere(dart::vec3(-6, 0, 0), 1.3, SOLID_MTL(dart::vec3(0, 1, 0)))) <<
    //new dart::csg::intersection(new dart::cube(dart::vec3(-1, -1, 5), dart::vec3(1, 1, 7), SOLID_MTL(dart::vec3(1, 0, 0))), new dart::sphere(dart::vec3(0, 0, 6), 1.3, SOLID_MTL(dart::vec3(0, 1, 0)))) <<
    //new dart::csg::intersection(new dart::cube(dart::vec3(-1, -1, -7), dart::vec3(1, 1, -5), SOLID_MTL(dart::vec3(1, 0, 0))), new dart::sphere(dart::vec3(0, 0, -6), 1.3, SOLID_MTL(dart::vec3(0, 1, 0))));
    // new dart::csg::intersection(new dart::csg::substract(new dart::sphere(dart::vec3(0), 5, SOLID_MTL(dart::vec3(1, 0, 0))), dart::sphere(dart::vec3(0, 5, 6), .5, SOLID_MTL(dart::vec3(1, 0, 0))), new dart::csg::substract(new dart::cube(dart::vec3(-1.4), dart::vec3(1.4), SOLID_MTL(dart::vec3(.7))), new dart::csg::substract(new dart::cube(dart::vec3(-1.4), dart::vec3(1.4), SOLID_MTL(dart::vec3(.7))), new dart::sphere(dart::vec3(0), 1.8, SOLID_MTL(dart::vec3(0, 0, 1))))));

#endif

  MyRT.Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
