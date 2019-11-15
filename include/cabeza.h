#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cilindro.h"

class Cabeza{
   public:
      Cabeza();

      void draw(const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);

      void modificarGiroCabeza(const float incremento);


   private:
      float giroCabeza;


      Cilindro * cuerpo_movil = nullptr;
      ObjPly * cabeza_ply = nullptr;


};



#endif
