#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"
#include "r2d2.h"

#include "luzposicional.h"
#include "luzdireccional.h"

#include <vector>

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, SELTAPAS, VALFA, VBETA} menu;


class Escena
{

   private:



 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();



   void clear_window();

   menu modoMenu=NADA;

   GLenum sombreado = GL_SMOOTH;


   dibujado modo_dibujado = INMEDIATO;
   // modos de visualizacion: solido, puntos, lienas, ajedrez e iluminacion
   bool modos_visualizacion [5] = {true, false, false, false, false};

   // Objetos de la escena
   Ejes ejes;


   Cubo * cubo           = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPly * objetoPly    = nullptr;
   ObjRevolucion * objR  = nullptr;
   ObjRevolucion * objR2 = nullptr;
   Cilindro * cilindro   = nullptr;
   Esfera * esfera       = nullptr;
   Cono * cono           = nullptr;
   R2D2 * r2d2           = nullptr;


   LuzPosicional * luz0 = nullptr;
   LuzDireccional * luz1   = nullptr;

   void dibujar_objetos(const GLenum modo, const bool modoAjedrez = false);
   void activar_luces();
   void asignar_materiales();


   public:

    Escena();
    ~Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
