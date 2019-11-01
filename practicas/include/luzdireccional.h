#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "luz.h"
#include "aux.h"

class LuzDireccional : public Luz{
   public:
      LuzDireccional(const Tupla3f direccion,\
                     const GLenum idLuzOpenGL,\
                     const Tupla4f colorAmbiente = {0.0f, 0.0f, 0.0f, 1.0f},\
                     const Tupla4f colorEspecular = {1.0f, 1.0f, 1.0f, 1.0f},\
                     const Tupla4f colorDifuso = {1.0f, 1.0f, 1.0f, 1.0f});

      void variarAnguloAlpha(const float incremento);
      void variarAnguloBeta(const float incremento);

   protected:
      float alpha;
      float beta;

};



#endif
