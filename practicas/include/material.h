#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material{

   private:
      Tupla4f ambiente;
      Tupla4f especular;
      Tupla4f difuso;
      Tupla4f emision;
      float brillo;


   public:
      Material();
      Material(const Tupla4f ambiente, const Tupla4f difuso,\
               const Tupla4f especular, const float brillo);

      void aplicar();

      void operator = (const Material & otro);

};

#endif
