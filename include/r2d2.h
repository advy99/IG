#ifndef R2D2_H_INCLUDED
#define R2D2_H_INCLUDED

#include "aux.h"
#include "cuerpo.h"
#include "objply.h"

class R2D2{
   public:
      R2D2();

      void draw(const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);

      void modificarAlturaCuello(const float incremento);
      void modificarInclunacionCuerpo(const float incremento);
      void modificarGiroCabeza(const float incremento);

      void animarModeloJerarquico();

      void modificarVelocidadAnimacion(const float factor);

   private:
      float inclinacionCuerpo;

      Cuerpo * cuerpo = nullptr;
      ObjPly * pierna_izq = nullptr;
      ObjPly * pierna_der = nullptr;

      float incrementoVelocidad = 1;

};



#endif
