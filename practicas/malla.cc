#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

  glEnableClientState( GL_VERTEX_ARRAY );

  glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;

  glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );

  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(const dibujado modo_dibujado)
{
   // completar .....(práctica 1)

   if (visible){
      if (modo_dibujado == INMEDIATO)
         draw_ModoInmediato();
      else
         draw_ModoDiferido();
   }


}
