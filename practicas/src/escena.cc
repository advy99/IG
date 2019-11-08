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


    cubo      = new Cubo(1);
    tetraedro = new Tetraedro(1);
    objetoPly = new ObjPly("./plys/samus1.ply");
    objR      = new ObjRevolucion("./plys/peon.ply", 30, true, true);
    cilindro  = new Cilindro(30, 2, 1, true, true);
    esfera    = new Esfera(60, 60, 1);
    cono      = new Cono(30, 1, 1);


    Tupla3f posicion_luz_0 = {30, 70, 50};
    Tupla3f posicion_luz_1 = {0, -110, 10};

    Tupla4f color0 = {1 ,1, 1,1};
    Tupla4f color1 = {1, 1, 1, 1};

    asignar_materiales();

    luz0  = new LuzPosicional (posicion_luz_0, GL_LIGHT0,  {0, 0, 0,1}, {1,1,1,1}, {1,1,1,1});
    luz1 = new LuzDireccional ( posicion_luz_1, GL_LIGHT1, {0, 0, 0, 1}, {1,1,1,1}, {1,1,1,1});

}

Escena::~Escena(){

   delete cubo;
   delete tetraedro;
   delete objetoPly;
   delete objR;
   delete cilindro;
   delete esfera;
   delete cono;

   delete luz0;
   delete luz1;
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

   glEnable (GL_CULL_FACE); // activar cull face para dibujar solo por un lado

   glEnable(GL_NORMALIZE);


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

    glDisable(GL_LIGHTING);
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer

    if (modos_visualizacion[0]){

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujar_objetos(GL_FILL);
    }

   if (modos_visualizacion[1]){
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     dibujar_objetos(GL_LINE);
   }

   if (modos_visualizacion[2]){
     glPointSize(6);
     glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
     dibujar_objetos(GL_POINT);
     glPointSize(1);

   }

   if (modos_visualizacion[3]){
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     dibujar_objetos(GL_FILL, true);
   }

   if (modos_visualizacion[4]){
     glEnable(GL_LIGHTING);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     activar_luces();
     dibujar_objetos(GL_FILL);
   }


}

void Escena::activar_luces(){
   if (luz0 != nullptr){
      glPushMatrix();
         glScalef(15.0f, 15.0f, 15.0f);
         luz0->activar();
      glPopMatrix();
   }

   if (luz1 != nullptr){
      luz1->activar();
   }
}


void Escena::dibujar_objetos(const GLenum modo, const bool modoAjedrez){

   if ( cubo != nullptr ){
      cubo->colorearModo(modo);

      glPushMatrix();

      //glTranslatef(50.0f, 0.0f, 0.0f);
         glScalef(60.0f, 60.0f, 60.0f);

         cubo->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( tetraedro != nullptr ){

      tetraedro->colorearModo(modo);

      glPushMatrix();



         glTranslatef(0.0f, 120.0f, 0.0f);
         glScalef(60.0f, 60.0f, 60.0f);


         tetraedro->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( objetoPly != nullptr ){

      objetoPly->colorearModo(modo);

      glPushMatrix();

         glTranslatef(-100.0f, 0.0f, 0.0f);
         glScalef(7.0f, 7.0f, 7.0f);


         objetoPly->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( objR != nullptr ){

      objR->colorearModo(modo);

      glPushMatrix();

         glTranslatef(0.0f, 0.0f, -100.0f);
         glScalef(15.0f, 15.0f, 15.0f);


         objR->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( cilindro != nullptr ){

      cilindro->colorearModo(modo);

      glPushMatrix();

         glTranslatef(0.0f, 0.0f, 100.0f);
         glScalef(30.0f, 30.0f, 30.0f);


         cilindro->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( esfera != nullptr ){

      esfera->colorearModo(modo);

      glPushMatrix();

         glTranslatef(0.0f, 100.0f, 100.0f);
         glScalef(60.0f, 60.0f, 60.0f);


         esfera->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( cono != nullptr ){

      cono->colorearModo(modo);

      glPushMatrix();

         glTranslatef(100.0f, 0.0f, 100.0f);
         glScalef(40.0f, 40.0f, 40.0f);


         cono->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

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
            if (cubo != nullptr) {
               cubo->setVisible(!cubo->esVisible());

               if ( cubo->esVisible() ){
                  cout << "Mostrando el cubo" << endl;
               } else{
                  cout << "Ocultando el cubo" << endl;
               }
            }

         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'T' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[4] = true;

            modos_visualizacion[0] = false;
            modos_visualizacion[1] = false;
            modos_visualizacion[2] = false;
            modos_visualizacion[3] = false;

         } else if (modoMenu == SELOBJETO){
            if (tetraedro != nullptr){
               tetraedro->setVisible( !tetraedro->esVisible() );

               if (tetraedro->esVisible()){
                  cout << "Mostrando el tetraedro" << endl;
               } else{
                  cout << "Ocultando el tetraedro" << endl;
               }
            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'I' :
         if (modoMenu == SELOBJETO){
            if (cilindro != nullptr){
               cilindro->setVisible( !cilindro->esVisible() );

               if (cilindro->esVisible()){
                  cout << "Mostrando el cilindro" << endl;
               } else{
                  cout << "Ocultando el cilindro" << endl;
               }
            }
         } else if (modoMenu == SELTAPAI){
            if (cilindro != nullptr) {

               if ( cilindro->tieneTapaInferior() ){
                  cout << "Ocultando tapa inferior del cilindro" << endl;
               } else{
                  cout << "Mostrando tapa inferior del cilindro" << endl;
               }

               cilindro->permutarTapaInferior();

            }
         } else if (modoMenu == SELTAPAS){
            if (cilindro != nullptr) {

               if ( cilindro->tieneTapaSuperior() ){
                  cout << "Ocultando tapa superior del cilindro" << endl;
               } else{
                  cout << "Mostrando tapa superior del cilindro" << endl;
               }

               cilindro->permutarTapaSuperior();

            }
         }  else if (modoMenu == NADA){
            modoMenu = SELTAPAI;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


      case 'R' :
         if (modoMenu == SELOBJETO){
            if (objR != nullptr){
               objR->setVisible( !objR->esVisible() );

               if (objR->esVisible()){
                  cout << "Mostrando objeto por revolucion" << endl;
               } else{
                  cout << "Ocultando objetoto por revolucion" << endl;
               }
            }
         }  else if (modoMenu == SELTAPAI){
            if (objR != nullptr) {

               if ( objR->tieneTapaInferior() ){
                  cout << "Ocultando tapa inferior del objeto por revolución" << endl;
               } else{
                  cout << "Mostrando tapa inferior del objeto por revolución" << endl;
               }

               objR->permutarTapaInferior();

            }
         } else if (modoMenu == SELTAPAS){
            if (objR != nullptr) {

               if ( objR->tieneTapaSuperior() ){
                  cout << "Ocultando tapa superior del objeto por revolución" << endl;
               } else{
                  cout << "Mostrando tapa superior del objeto por revolución" << endl;
               }

               objR->permutarTapaSuperior();

            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


      case 'E' :
         if (modoMenu == SELOBJETO){
            if (esfera != nullptr){
               esfera->setVisible( !esfera->esVisible() );

               if (esfera->esVisible()){
                  cout << "Mostrando la esfera" << endl;
               } else{
                  cout << "Ocultando la esfera" << endl;
               }
            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


      // CASOS PARA SELECCION DE MODO DE VISUALIZACION
      case 'P' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[2] = !modos_visualizacion[2];
            if (modos_visualizacion[2]){
               cout << "Activando modo puntos (desactivando iluminacion)" << endl;
               modos_visualizacion[3] = false;
               modos_visualizacion[4] = false;

            }
            else
               cout << "Desactivando modo puntos" << endl;
         } else if (modoMenu == SELOBJETO){
            if (objetoPly != nullptr){
               objetoPly->setVisible( !objetoPly->esVisible() );

               if (objetoPly->esVisible()){
                  cout << "Mostrando el objeto PLY" << endl;
               } else{
                  cout << "Ocultando el objeto PLY" << endl;
               }
            }
         } else {
            cout << "ERROR: Opción no valida" << endl;
         }

         break;

      case 'L' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[1] = !modos_visualizacion[1];
            if (modos_visualizacion[1]){
               cout << "Activando modo lineas (desactivando iluminacion)" << endl;
               modos_visualizacion[3] = false;
               modos_visualizacion[4] = false;
            }
            else
               cout << "Desactivando modo lineas" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }


         break;

      case 'S' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[0] = !modos_visualizacion[0];

            if (modos_visualizacion[0]){
               cout << "Activando modo relleno (desactivando iluminacion)" << endl;
               // no podemos ver en ajedrez si esta relleno
               modos_visualizacion[3] = false;
               modos_visualizacion[4] = false;

            }
            else
               cout << "Desactivando modo relleno" << endl;
         } else if (modoMenu == NADA){
            modoMenu = SELTAPAS;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }


         break;

      case 'A' :
         if (modos_visualizacion[4]){
            modoMenu = IALFA;
         } else if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[3] = !modos_visualizacion[3];

            if (modos_visualizacion[3]){
               cout << "Activando modo ajedrez (desactivando iluminacion)" << endl;
               // no podemos ver en relleno si esta en ajedrez
               modos_visualizacion[0] = false;
               modos_visualizacion[1] = false;
               modos_visualizacion[2] = false;
               modos_visualizacion[4] = false;
            }
            else
               cout << "Desactivando modo ajedrez" << endl;
         } else if (modoMenu == SELOBJETO){
            if (cono != nullptr){
               cono->setVisible( !cono->esVisible() );

               if (cono->esVisible()){
                  cout << "Mostrando el cono" << endl;
               } else{
                  cout << "Ocultando el cono" << endl;
               }
            }
         } else if (modoMenu == SELTAPAI){
            if (cono != nullptr) {

               if ( cono->tieneTapaInferior() ){
                  cout << "Ocultando tapa inferior del cono" << endl;
               } else{
                  cout << "Mostrando tapa inferior del cono" << endl;
               }

               cono->permutarTapaInferior();

            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'B':
         if (modos_visualizacion[4]){
            modoMenu = IBETA;
         }
         break;
      case 'Z':
         if (modos_visualizacion[4]){
            if (sombreado == GL_FLAT){
               sombreado = GL_SMOOTH;
            }
            else{
               sombreado = GL_FLAT;
            }
         }
         break;

      case '0':
         if (modos_visualizacion[4] && luz0 != nullptr){
            luz0->setActivada(!luz0->estaActivada());
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break;

      case '1' :
         if (modos_visualizacion[4] && luz1 != nullptr){
            luz1->setActivada(!luz1->estaActivada());

         } else if (modoMenu == SELDIBUJADO){
            modo_dibujado = INMEDIATO;
            cout << "Cambiando modo de dibujado a INMEDIATO" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case '2' :
         //if (modos_visualizacion[4] && luz2 != nullptr){
         //      luz2->setActivada(!luz2->estaActivada());

         //} else
          if (modoMenu == SELDIBUJADO){
            modo_dibujado = DIFERIDO;
            cout << "Cambiando modo de dibujado a DIFERIDO" << endl;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;
      /*
      case '3':
         if (modos_visualizacion[4] && luz3 != nullptr){
            luz3->setActivada(!luz3->estaActivada());
         }

         break;

      case '4':
         if (modos_visualizacion[4] && luz4 != nullptr){
            luz4->setActivada(!luz4->estaActivada());
         }

         break;

      case '5':
         if (modos_visualizacion[4] && luz5 != nullptr){
            luz5->setActivada(!luz5->estaActivada());
         }
         break;

      case '6':
         if (modos_visualizacion[4] && luz6 != nullptr){
            luz6->setActivada(!luz6->estaActivada());
         }
         break;

      case '7':
         if (modos_visualizacion[4] && luz7 != nullptr){
            luz7->setActivada(!luz7->estaActivada());
         }
         break;


*/
      case '<':
         if (modoMenu == IALFA){
            luz1->variarAnguloAlpha(-5.0*SEXA_TO_RAD);
         } else if (modoMenu == IBETA){
            luz1->variarAnguloBeta(-5.0*SEXA_TO_RAD);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;

      case '>':
         if (modoMenu == IALFA){
            luz1->variarAnguloAlpha(5.0*SEXA_TO_RAD);
         } else if (modoMenu == IBETA){
            luz1->variarAnguloBeta(5.0*SEXA_TO_RAD);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;

      default:
         cout << "ERROR: Opción no valida" << endl;
         break;


   }

   cout << endl;
   switch(modoMenu){
      case NADA:
         cout << "MENU: Principal" << endl
              << "Opciones: " << endl
              << "\t Q: Salir" << endl
              << "\t O: Menu selección de objeto" << endl
              << "\t V: Menu modo visualización de objeto" << endl
              << "\t D: Menu modo dibujado" << endl
              << "\t S: Menu seleccion tapa superior" << endl
              << "\t I: Menu seleccion tapa inferior" << endl;

         break;

      case SELOBJETO:
         cout << "MENU: Selección de objeto" << endl
              << "Opciones: " << endl
              << "\t Q: Salir del menu" << endl
              << "\t C: Mostrar/ocultar cubo" << endl
              << "\t T: Mostrar/ocultar tetraedro" << endl
              << "\t A: Mostrar/ocultar cono" << endl
              << "\t E: Mostrar/ocultar esfera" << endl
              << "\t I: Mostrar/ocultar cilindro" << endl
              << "\t P: Mostrar/ocultar objeto PLY" << endl
              << "\t R: Mostrar/ocultar objeto por revolucion" << endl;
         break;

      case SELVISUALIZACION:
         cout << "MENU: Selección de modo de visualización" << endl
              << "Opciones: " << endl
              << "\t Q: Salir del menu" << endl
              << "\t P: Activar/desactivar modo puntos" << endl
              << "\t L: Activar/desactivar modo lineas" << endl
              << "\t S: Activar/desactivar modo solido (por defecto)" << endl
              << "\t A: Activar/desactivar modo ajedrez" << endl
              << "\t T: Activar modo iluminación" << endl;


         break;

      case SELDIBUJADO:
         cout << "MENU: Selección de modo de dibujado" << endl
              << "Opciones: " << endl
              << "\t Q: Salir del menu" << endl
              << "\t 1: Visualización en modo inmediato" << endl
              << "\t 2: Visualización en modo diferido" << endl;

         break;

      case SELTAPAI:
         cout << "MENU: Selección de tapa inferior" << endl
              << "Opciones: " << endl
              << "\t Q: Salir del menu" << endl
              << "\t I: Permutar tapa inferior del cilindro" << endl
              << "\t R: Permutar tapa inferior del objeto por revolucion" << endl
              << "\t A: Permutar tapa inferior del cono" << endl;

        break;

     case SELTAPAS:
       cout << "MENU: Selección de tapa superior" << endl
            << "Opciones: " << endl
            << "\t Q: Salir del menu" << endl
            << "\t I: Permutar tapa superior del cilindro" << endl
            << "\t R: Permutar tapa superior del objeto por revolucion" << endl;

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

void Escena::asignar_materiales(){

   // Materiales obtenidos de:
   // http://devernay.free.fr/cours/opengl/materials.html

   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material ruby({0.1745, 0.01175, 0.01175, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 128.0f * 0.6f );
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811,0.633, 1}, 0.6 * 128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273,0.508273, 0.508273, 1}, 0.4*128.0f);

   if (cubo != nullptr){
      cubo->setMaterial(oro);
   }

   if (objetoPly != nullptr){
      objetoPly->setMaterial(ruby);
   }

   if (objR != nullptr){
      objR->setMaterial(perla);
   }

   if (esfera != nullptr){
      esfera->setMaterial(esmeralda);
   }

   if (cilindro != nullptr){
      cilindro->setMaterial(plata);
   }

}
