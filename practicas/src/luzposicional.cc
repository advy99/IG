#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f posicion,\
                             const GLenum idLuzOpenGL, \
                             const Tupla4f colorAmbiente,\
                             const Tupla4f colorEspecular,\
                             const Tupla4f colorDifuso){

   id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;


   this->posicion = {posicion(0), posicion(1), posicion(2), 1};

};
