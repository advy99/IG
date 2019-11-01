#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{

   protected:
      GLenum id;
      Tupla4f posicion;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;

      bool activada;

   public:
      Luz();
      void activar() const;
      bool estaActivada() const;
      void setActivada(const bool activada);

};



#endif
