#include "luz.h"


Luz::Luz(){
   activada = false;
}


void Luz::activar() const{

   if (activada){
      glLightfv(id, GL_DIFFUSE, colorDifuso );
      glLightfv(id, GL_AMBIENT, colorAmbiente );
      glLightfv(id, GL_SPECULAR, colorEspecular );
      glLightfv(id, GL_POSITION, posicion);
   }

}

bool Luz::estaActivada() const{
   return activada;
}

void Luz::setActivada(const bool act){
   activada = act;
   if (activada)
      glEnable(id);
   else
      glDisable(id);
}
