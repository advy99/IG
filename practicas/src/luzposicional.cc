#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f p,\
                             const GLenum idLuzOpenGL, \
                             const Tupla4f colorA,\
                             const Tupla4f colorE,\
                             const Tupla4f colorD){

   id = idLuzOpenGL;
   colorAmbiente = colorA;
   colorDifuso = colorD;
   colorEspecular = colorE;


   posicion = {p(0), p(1), p(2), 1};

};
