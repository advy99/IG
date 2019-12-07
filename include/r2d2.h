#ifndef R2D2_H_INCLUDED
#define R2D2_H_INCLUDED

#include "aux.h"
#include "cuerpo.h"
#include "objply.h"

class R2D2{
   public:
      R2D2();

      void draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);

      void modificarAlturaCuello(const float incremento);
      void modificarInclunacionCuerpo(const float incremento);
      void modificarGiroCabeza(const float incremento);

      void animarModeloJerarquico();

      void modificarVelocidadAnimacion(const float factor);
		void setColorSeleccion(const Tupla3f & c);
		Tupla3f getColorSeleccion()const;
		Tupla3f getCentro() const;

   private:
      float inclinacionCuerpo;

      Cuerpo * cuerpo = nullptr;
      ObjPly * pierna_izq = nullptr;
      ObjPly * pierna_der = nullptr;
		Tupla3f color_seleccion;

      float incrementoVelocidad = 1;

};



#endif
