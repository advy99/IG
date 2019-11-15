#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "cabeza.h"
#include "cilindro.h"

class Cuerpo{
   public:
      Cuerpo();

      void draw(const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);



   private:
      Cabeza * cabeza = nullptr;
      ObjPly * tronco = nullptr;


};



#endif
