#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{

   private:
      glEnum id;
      Tupla4f posicion;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;


   public:
      Luz();
      void activar();

};



#endif
