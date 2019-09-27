// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {INMEDIATO, DIFERIDO} dibujado;

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(const dibujado modo_dibujado) ;

   bool visible = true;

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c ; // terna de 3 floats, para los colores

   // completar: tabla de colores, tabla de normales de vértices

   private:
      GLuint id_vbo_ver = 0; // se inicializara a 0
      GLuint id_vbo_tri = 0; // se inicializara a 0
      GLuint id_vbo_col = 0;

      GLuint CrearVBO( const GLuint tipo_vbo, const GLuint tamanio_bytes,
                       const GLvoid * puntero_ram);
} ;


#endif
