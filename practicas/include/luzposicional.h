#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "luz.h"
#include "aux.h"


class LuzPosicional : public Luz{
   public:
      LuzPosicional(const Tupla3f posicion,\
                    const GLenum idLuzOpenGL, \
                    const Tupla4f colorAmbiente = {0.0f, 0.0f, 0.0f, 1.0f},\
                    const Tupla4f colorEspecular = {1.0f, 1.0f, 1.0f, 1.0f},\
                    const Tupla4f colorDifuso = {1.0f, 1.0f, 1.0f, 1.0f});
};



#endif
