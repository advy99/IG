#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "cabeza.h"
#include "cilindro.h"

class Cuerpo{
   public:
      Cuerpo();

      void draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);

      void modificarAlturaCuello(const float incremento);

      void modificarGiroCabeza(const float incremento);

      void animarModeloJerarquico();

      void modificarVelocidadAnimacion(const float factor);


   private:

      float alturaCuello;
      float incrementoVelocidad = 0.1;

      const float tope_cuello = 4;

      Cabeza * cabeza = nullptr;
      ObjPly * tronco = nullptr;


};



#endif
