// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: aux.h
//
// -- includes de OpenGL/glut/glu/glew (dependen del S.O.)
// -- includes de la librería estándard de C++
// -- includes de 'tuplasg.h'
//
// #############################################################################

#ifndef AUX_H_INCLUDED
#define AUX_H_INCLUDED

#ifdef _WIN32
#  include <windows.h>
#endif

#include <cmath>    // sin, cos, etc....
#include <cstdlib>  // exit
#include <ostream> // cout y demás .....
#include <string>   // std::string
#include <vector>   // std::vector

#ifdef LINUX
#  include <GL/glew.h> // en linux: incluye GL.h
#  include <GL/glut.h> // GLUT (gestión de ventanas)
#  include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef MACOS
#  include <OpenGL/GL.h>
#  include <OpenGL/glu.h>   // librería 'glu' (funciones 'glu....')
#  include <GLUT/glut.h>    // glut standard (incluye cabecera opengl)
#  pragma GCC diagnostic ignored "-Wdeprecated-declarations" // ignora advertencias por uso de funciones obsoletas (p.ej. en GLUT)(sirve en OSX)
#endif

#include "tuplasg.h" // tipos: Tupla3f, Tupla2f, Tupla3d, etc.........

#define SEXA_TO_RAD M_PI/180
#define RAD_TO_SEXA 180/M_PI

bool invertMatrix(const float m[16], float invOut[16]);
bool compara_floats(const float & a, const float & b, const float epsilon = 0.005f);
bool operator == (const Tupla3f & t1, const Tupla3f & t2);

#endif // AUX_H_INCLUDED
