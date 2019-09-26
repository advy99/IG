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

void Malla3D::draw()
{
   glEnable (GL_CULL_FACE);

   glPolygonMode(GL_FRONT, GL_FILL);

   // completar .....(práctica 1)
   glEnableClientState( GL_VERTEX_ARRAY );

   glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;

   glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );

   glDisableClientState( GL_VERTEX_ARRAY );
}
