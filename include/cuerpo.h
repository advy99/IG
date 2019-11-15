#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "cabeza.h"
#include "cilindro.h"

class Cuerpo{
   public:
      Cuerpo();

      void draw();



   private:
      Cabeza * cabeza = nullptr;
      ObjPly * tronco = nullptr;


};



#endif
