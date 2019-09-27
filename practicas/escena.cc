

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....


    cubo = new Cubo(50);
    tetraedro = new Tetraedro(50);

}

Escena::~Escena(){
   delete cubo;
   delete tetraedro;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
    glEnable (GL_CULL_FACE);


    if (modos_visualizacion[0]){
      glPolygonMode(GL_FRONT, GL_FILL);
      dibujar_objetos();
    }

   if (modos_visualizacion[1]){
     glPolygonMode(GL_FRONT, GL_LINE);
     dibujar_objetos();
   }

   if (modos_visualizacion[2]){
     glPointSize(6);
     glPolygonMode(GL_FRONT, GL_POINT);
     dibujar_objetos();
   }

}


void Escena::dibujar_objetos(){
   if (cubo != nullptr)
      cubo->draw(modo_dibujado);

   if (tetraedro != nullptr)
      tetraedro->draw(modo_dibujado);
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            modoMenu=NADA;
            cout << "Saliendo del menu" << endl;
         }
         else {
            salir=true ;
         }
         break ;

      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         // hay que poner si modomenu = nada, en todos
         if (modoMenu == NADA){
            modoMenu=SELOBJETO;
            cout << "Entrando en el menu de selección de objetos" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if (modoMenu == NADA){
            modoMenu=SELVISUALIZACION;
            cout << "Entrando en el menu de selección del modo de visualización" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if (modoMenu == NADA){
            modoMenu=SELDIBUJADO;
            cout << "Entrando en el menu de selección de dibujado" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break ;
         // COMPLETAR con los diferentes opciones de teclado

      // CASOS PARA MODO SELECCION DE OBJETO
      case 'C' :
         if (modoMenu == SELOBJETO){
            cubo->visible = !cubo->visible;
            if (cubo->visible){
               cout << "Mostrando el cubo" << endl;
            } else{
               cout << "Ocultando el cubo" << endl;
            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'T' :
         if (modoMenu == SELOBJETO){
            tetraedro->visible = !tetraedro->visible;
            if (tetraedro->visible){
               cout << "Mostrando el tetraedro" << endl;
            } else{
               cout << "Ocultando el tetraedro" << endl;
            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


      // CASOS PARA SELECCION DE MODO DE VISUALIZACION
      case 'P' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[2] = !modos_visualizacion[2];
            if (modos_visualizacion[2])
               cout << "Activando modo puntos" << endl;
            else
               cout << "Desactivando modo puntos" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break;

      case 'L' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[1] = !modos_visualizacion[1];
            if (modos_visualizacion[1])
               cout << "Activando modo lineas" << endl;
            else
               cout << "Desactivando modo lineas" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }


         break;

      case 'S' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[0] = !modos_visualizacion[0];
            if (modos_visualizacion[0])
               cout << "Activando modo relleno" << endl;
            else
               cout << "Desactivando modo relleno" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }


         break;

      case 'A' :
         if (modoMenu == SELVISUALIZACION){

         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         //modo_visualizacion = GL_CHESS;
         break;


      case '1' :
         if (modoMenu == SELDIBUJADO){
            modo_dibujado = INMEDIATO;
            cout << "Cambiando modo de dibujado a INMEDIATO" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case '2' :
         if (modoMenu == SELDIBUJADO){
            modo_dibujado = DIFERIDO;
            cout << "Cambiando modo de dibujado a DIFERIDO" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;



      default:
         cout << "ERROR: Opción no valida" << endl;
         break;


   }

   cout << endl << endl;
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
