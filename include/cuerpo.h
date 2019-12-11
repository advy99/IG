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

		void setColorSeleccion(const Tupla3f & c);
		Tupla3f getColorSeleccion()const;
		Tupla3f getCentro() const;

		void colorearModo(const GLenum modo);

   private:

      float alturaCuello;
      float incrementoVelocidad = 0.1;

      const float tope_cuello = 4;
		Tupla3f color_seleccion;


      Cabeza * cabeza = nullptr;
      ObjPly * tronco = nullptr;


};



#endif
