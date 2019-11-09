// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tetraedro.h

//
// #############################################################################

#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen

class Tetraedro: public Malla3D
{
   public:
      Tetraedro(const float l=1);

} ;




#endif
