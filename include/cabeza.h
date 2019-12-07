#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cilindro.h"

class Cabeza{
   public:
      Cabeza();

      void draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                const GLenum sombreado);

      void modificarGiroCabeza(const float incremento);

      void animarModeloJerarquico();

      void modificarVelocidadAnimacion(const float factor);

		void setColorSeleccion(const Tupla3f & c);
		Tupla3f getColorSeleccion()const;

   private:
      float giroCabeza;

      float incrementoVelocidad = 1;
		Tupla3f color_seleccion;


      Cilindro * cuerpo_movil = nullptr;
      ObjPly * cabeza_ply = nullptr;


};



#endif
