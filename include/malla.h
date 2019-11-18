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
#include "material.h"

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

      void draw_ModoAjedrez();

      // función que redibuja el objeto
      // está función llama a 'draw_ModoInmediato' (modo inmediato)
      // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
      void draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez, const GLenum sombreado);

      void colorear(const Tupla3f color);
      void colorearDiferido(const Tupla3f color);

      Tupla3f getColorSolido() const;
      Tupla3f getColorLinea() const;
      Tupla3f getColorPunto() const;

      Tupla3f getColorDiferido() const;


      bool esVisible() const;
      void setVisible(const bool & visible);

      void setMaterial(const Material & m);

   protected:

      void colorearModo(const GLenum modo);

      void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

      std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
      std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
      std::vector<Tupla3f> c ; // terna de 3 floats, para los colores
      std::vector<Tupla3f> c_diferido ; // terna de 3 floats, para los colores

      std::vector<Tupla3f> nv;

      Material m;

      //Textura * textura = nullptr;
      std::vector<Tupla2f> ct;

      Tupla3f color_solido;
      Tupla3f color_linea;
      Tupla3f color_punto;

      Tupla3f color_diferido;
      bool visible = true;




   // completar: tabla de colores, tabla de normales de vértices

      GLuint id_vbo_ver         = 0; // se inicializara a 0
      GLuint id_vbo_tri         = 0; // se inicializara a 0
      GLuint id_vbo_tri_ajedrez = 0;
      GLuint id_vbo_nv          = 0;
      GLuint id_vbo_col         = 0;
      GLuint id_vbo_col_ajedrez = 0;



      virtual void pintar();


      GLuint CrearVBO( const GLuint tipo_vbo, const GLuint tamanio_bytes,
                       const GLvoid * puntero_ram);
} ;


#endif
