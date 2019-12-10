#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{


    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....


    cubo      = new Cubo(1);
	 cubo->setColorSeleccion(Tupla3f(1.0, 0.0, 0.0));

    tetraedro = new Tetraedro(1);
	 tetraedro->setColorSeleccion(Tupla3f(0.0, 1.0, 0.0));

    objetoPly = new ObjPly("./plys/samus1.ply");
	 objetoPly->setColorSeleccion(Tupla3f(0.0, 0.0, 1.0));

	 objR      = new ObjRevolucion("./plys/peon.ply", 30, true);
	 objR->setColorSeleccion(Tupla3f(1.0, 1.0, 0.0));

	 objR2     = new ObjRevolucion("./plys/peon.ply", 30, true);
	 objR2->setColorSeleccion(Tupla3f(0.0, 1.0, 1.0));

	 cilindro  = new Cilindro(30, 1, 1, true, EJE_Y);
	 cilindro->setColorSeleccion(Tupla3f(0.3, 1.0, 1.0));

	 esfera    = new Esfera(30, 30, 1);
	 esfera->setColorSeleccion(Tupla3f(0.2, 0.2, 0.2));

	 cono      = new Cono(30, 1, 1, true, EJE_Y);
	 cono->setColorSeleccion(Tupla3f(0.5, 0.5, 0.5));

	 r2d2      = new R2D2();
	 r2d2->setColorSeleccion(Tupla3f(1.0, 0.2, 0.5));

	 cuadro	  = new Cuadro();
	 cuadro->setColorSeleccion(Tupla3f(1.0, 0.1, 0.9));

	 if (cilindro != nullptr)
	 	cilindro->setTextura("img/text-lata-1.jpg");

	 if (esfera != nullptr)
	 	esfera->setTextura("img/tierra.jpg");

	 if (cuadro != nullptr)
	 	cuadro->setTextura("./img/metroid.jpg");


    Tupla3f posicion_luz_0 = {200, 150, 200};
    Tupla3f posicion_luz_1 = {0, 0, 10};

    asignar_materiales();

    luz0  = new LuzPosicional (posicion_luz_0, GL_LIGHT0,  {0, 0, 0, 1}, {1,1,1,1}, {1,1,1,1});
    luz1 = new LuzDireccional ( posicion_luz_1, GL_LIGHT1, {0, 0, 0, 1}, {1,1,1,1}, {1,1,1,1});

	 Tupla3f eye = {0, 100, 200};
	 Tupla3f at = {0, 0, 0};
	 Tupla3f up = {0, 1, 0};


	 Camara c1(eye, at, up, PERSPECTIVA, 50.0, 2000.0);

	 eye = {0, 0, 300};
	 at = {0, 0, 0};
	 up = {0, 1, 0};

	 Camara c2(eye, at, up, ORTOGONAL, 50.0, 2000.0);

	 eye = {0, 100, 100};
	 at = {0, 60, -115};
	 up = {0, 1, 0};

	 Camara c3(eye, at, up, PERSPECTIVA, 50.0, 2000.0);

	 camaras.push_back(c1);
	 camaras.push_back(c2);
	 camaras.push_back(c3);

	 camaraActiva = 0;

}

Escena::~Escena(){

   delete cubo;
   delete tetraedro;
   delete objetoPly;
   delete objR;
   delete objR2;
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


	for (int i = 0; i < camaras.size(); i++){

		camaras[i].setLeft(-UI_window_width/10);
		camaras[i].setRight(UI_window_width/10);
		camaras[i].setBottom(-UI_window_height/10);
		camaras[i].setTop(UI_window_height/10);

		//camaras[i].zoom((float)newWidth/(float)newHeight);
	}

   change_projection( (UI_window_width/10)/(UI_window_height/10) );
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
         glRotatef(rotacionLuz0, 0.0f, 1.0f, 0.0f);
         luz0->activar();
      glPopMatrix();
   }

   if (luz1 != nullptr){
      glPushMatrix();
         luz1->activar();
      glPopMatrix();
   }
}


void Escena::dibujar_objetos(const GLenum modo, const bool modoAjedrez){

	if ( cuadro != nullptr ) {
		glPushMatrix();

			glTranslatef(100.0f, 100.0f, -100.0f);
			glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
			glScalef(100.0f, 100.0f, 100.0f);
			cuadro->draw(modo, modo_dibujado, modoAjedrez, sombreado);

		glPopMatrix();
	}

	/*
   if ( cubo != nullptr ){

      glPushMatrix();

      //glTranslatef(50.0f, 0.0f, 0.0f);
         glScalef(60.0f, 60.0f, 60.0f);

         cubo->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }*/


   if ( tetraedro != nullptr ){


      glPushMatrix();



         glTranslatef(-30.0f, 0.0f, -115.0f);
         glScalef(60.0f, 60.0f, 60.0f);


         tetraedro->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( objetoPly != nullptr ){


      glPushMatrix();

         glTranslatef(-100.0f, 60.0f, 0.0f);

         glScalef(7.0f, 7.0f, 7.0f);

         objetoPly->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( objR != nullptr ){


      glPushMatrix();
         glTranslatef(70.0f, 65.0f, 20.0f);
         glScalef(15.0f, 15.0f, 15.0f);
         objR->draw(modo, modo_dibujado, modoAjedrez, sombreado);
      glPopMatrix();

   }

   if ( objR2 != nullptr ){

      glPushMatrix();
         glTranslatef(130.0f, 65.0f, 20.0f);
         glScalef(15.0f, 15.0f, 15.0f);
         objR2->draw(modo, modo_dibujado, modoAjedrez, sombreado);
      glPopMatrix();

   }
   if ( cilindro != nullptr ){


      glPushMatrix();

         glTranslatef(-100.0f, 0.0f, 0.0f);

         glScalef(20.0f, 60.0f, 20.0f);

         cilindro->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( esfera != nullptr ){


      glPushMatrix();

         glTranslatef(0.0f, 110.0f, -100.0f);
         glScalef(60.0f, 60.0f, 60.0f);


         esfera->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   if ( r2d2 != nullptr ){

      //r2d2->colorearModo(modo);

      glPushMatrix();

         glRotatef(rotacionR2D2, 0.0f, 1.0f, 0.0f);

         glTranslatef(-200.0f, 0.0f, 0.0f);
         glScalef(3.0f, 3.0f, 3.0f);
         r2d2->draw(modo, modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }

   /*
   if ( cono != nullptr ){

      cono->colorearModo(modo);

      glPushMatrix();

         glTranslatef(100.0f, 0.0f, 100.0f);
         glScalef(40.0f, 40.0f, 40.0f);


         cono->draw(modo_dibujado, modoAjedrez, sombreado);

      glPopMatrix();

   }*/


   if (cono != nullptr && cubo != nullptr){

      glPushMatrix();
         glTranslatef(50, 0, 0);

         glPushMatrix();
            glTranslatef(0.0f, 20.0f, 0.0f);
            glScalef(100.0f, 25.0f, 60.0f);
            cubo->draw(modo, modo_dibujado, modoAjedrez, sombreado);
         glPopMatrix();


         glPushMatrix();
            glTranslatef(50.0f, 0.0f, 30.0f);
            glScalef(25.0f, 35.0f, 25.0f);
            cono->draw(modo, modo_dibujado, modoAjedrez, sombreado);
         glPopMatrix();


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
         if (modoMenu == VALFA || modoMenu == VBETA){
            modoMenu = SELLUZ;
         } else if (modoMenu!=NADA){
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

		case 'M':
			if (modoMenu == NADA){
				modoMenu = MOVMODELO;
			} else{
            cout << "ERROR: Opción no valida" << endl;
         }

			break;
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

         } else if (modoMenu == NADA){
				modoMenu = SELCAM;
			} else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'T' :
         if (modoMenu == NADA){
            modoMenu = SELTAPAS;
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
         if (modoMenu == SELVISUALIZACION){
				modoMenu = SELLUZ;
            modos_visualizacion[4] = true;

            modos_visualizacion[0] = false;
            modos_visualizacion[1] = false;
            modos_visualizacion[2] = false;
            modos_visualizacion[3] = false;

         } else if (modoMenu == SELOBJETO){
            if (cilindro != nullptr){
               cilindro->setVisible( !cilindro->esVisible() );

               if (cilindro->esVisible()){
                  cout << "Mostrando el cilindro" << endl;
               } else{
                  cout << "Ocultando el cilindro" << endl;
               }
            }
         } else if (modoMenu == SELTAPAS){
            if (cilindro != nullptr) {

               if ( cilindro->tieneTapas() ){
                  cout << "Ocultando tapas del cilindro" << endl;
               } else{
                  cout << "Mostrando tapa del cilindro" << endl;
               }

               cilindro->setTapas(!cilindro->tieneTapas());

            }
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
         } else if (modoMenu == SELTAPAS){
            if (objR != nullptr) {

               if ( objR->tieneTapas() ){
                  cout << "Ocultando tapas del objeto por revolución" << endl;
               } else{
                  cout << "Mostrando tapas del objeto por revolución" << endl;
               }

               objR->setTapas(!objR->tieneTapas());

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
         } else if (modoMenu == SELLUZ){
				luz_automatica = !luz_automatica;
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
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }


         break;

      case 'A' :

         if (modoMenu == SELLUZ || modoMenu == VBETA){
            modoMenu = VALFA;
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
         } else if (modoMenu == SELTAPAS){
            if (cono != nullptr) {

               if ( cono->tieneTapas() ){
                  cout << "Ocultando tapas del cono" << endl;
               } else{
                  cout << "Mostrando tapas del cono" << endl;
               }

               cono->setTapas(!cono->tieneTapas());

            }
         } else if (modoMenu == NADA) {
				if (animacion_automatica){
               cout << "Desactivando la animación automatica" << endl;
            } else {
               cout << "Activando la animación automatica" << endl;
            }
            animacion_automatica = !animacion_automatica;
            //modoMenu = MOVMODELOAUTO;
			} else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case 'B':
         if (modoMenu == SELLUZ || modoMenu == VALFA ){
            modoMenu = VBETA;
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


      case 'Z':
         if (modoMenu == SELLUZ){
            if (sombreado == GL_FLAT){
               sombreado = GL_SMOOTH;
            }
            else{
               sombreado = GL_FLAT;
            }
         } else{
            cout << "ERROR: Opción no valida" << endl;
         }
         break;


		case 'U':
			if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){
				Tupla3f direccion = camaras[camaraActiva].getAt() - camaras[camaraActiva].getEye();
				direccion = direccion.normalized()*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
			}

			break;

		case 'J':
			if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){
				Tupla3f direccion = camaras[camaraActiva].getAt() - camaras[camaraActiva].getEye();
				direccion = -direccion.normalized()*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
			}

			break;

		case 'H':
			if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){
				Tupla3f direccion = camaras[camaraActiva].getAt() - camaras[camaraActiva].getEye();
				direccion = direccion.normalized();

				direccion = -direccion.cross(camaras[camaraActiva].getUp())*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
			}

			break;

		case 'K':
			if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){
				Tupla3f direccion = camaras[camaraActiva].getAt() - camaras[camaraActiva].getEye();
				direccion = direccion.normalized();

				direccion = direccion.cross(camaras[camaraActiva].getUp())*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
			}

			break;


      case '0':
         if (luz0 != nullptr && modoMenu == SELLUZ){
            luz0->setActivada(!luz0->estaActivada());
         } else if (modoMenu == MOVMODELO){
            menuModelo = CUERPO;
         } else if (modoMenu == SELCAM){
				seleccionaCamara(0);
				cout << "Seleccionada camara 0" << endl;

			} else{
            cout << "ERROR: Opción no valida" << endl;
         }

         break;

      case '1' :
         if (luz1 != nullptr  && modoMenu == SELLUZ){
            luz1->setActivada(!luz1->estaActivada());

         } else if (modoMenu == MOVMODELO){
            menuModelo = ALTURA;
         } else if (modoMenu == SELDIBUJADO){
            modo_dibujado = INMEDIATO;
            cout << "Cambiando modo de dibujado a INMEDIATO" << endl;
         } else if (modoMenu == SELCAM){
				seleccionaCamara(1);
				cout << "Seleccionada camara 1" << endl;
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
         } else if (modoMenu == MOVMODELO){
            menuModelo = CABEZA;
         } else if (modoMenu == SELCAM){
				seleccionaCamara(2);
				cout << "Seleccionada camara 2" << endl;
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
         if (modoMenu == VALFA){
            luz1->variarAnguloAlpha(-5.0*SEXA_TO_RAD);
         } else if (modoMenu == VBETA){
            luz1->variarAnguloBeta(-5.0*SEXA_TO_RAD);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;

      case '>':
         if (modoMenu == VALFA){
            luz1->variarAnguloAlpha(5.0*SEXA_TO_RAD);
         } else if (modoMenu == VBETA){
            luz1->variarAnguloBeta(5.0*SEXA_TO_RAD);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;


      case '+':
         if (modoMenu == MOVMODELO){
            switch(menuModelo){
               case CUERPO:
                  r2d2->modificarInclunacionCuerpo(5);
                  break;
               case ALTURA:
                  r2d2->modificarAlturaCuello(0.1);
                  break;
               case CABEZA:
                  r2d2->modificarGiroCabeza(5);
                  break;

               default:
                  cout << "Primero debes seleccionar que parte mover" << endl;
            }
         } else if (modoMenu == NADA && animacion_automatica){
            velocidadLuz0 *= 1.2f;
            velocidadR2D2 *= 1.2f;
            r2d2->modificarVelocidadAnimacion(1.2f);
         } else {
            cout << "ERROR: Opción no valida" << endl;
         }
         break;

      case '-':
         if (modoMenu == MOVMODELO){
            switch(menuModelo){
               case CUERPO:
                  r2d2->modificarInclunacionCuerpo(-5);
                  break;
               case ALTURA:
                  r2d2->modificarAlturaCuello(-0.1);
                  break;
               case CABEZA:
                  r2d2->modificarGiroCabeza(-5);
                  break;

               default:
                  cout << "Primero debes seleccionar que parte mover" << endl;
            }
         } else if (modoMenu == NADA && animacion_automatica){
            velocidadLuz0 *= 0.8f;
            velocidadR2D2 *= 0.8f;
            r2d2->modificarVelocidadAnimacion(0.8f);
         } else {
            cout << "ERROR: Opción no valida" << endl;
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
              << "\t T: Menu seleccion tapa superior" << endl
				  << "\t A: Activar/desactivar animación automatica" << endl
				  << "\t M: Mover manualmente el modelo jerarquico" << endl
				  << "\t C: Seleccionar la camara" << endl;


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
              << "\t I: Activar modo iluminación" << endl;


         break;

      case SELDIBUJADO:
         cout << "MENU: Selección de modo de dibujado" << endl
              << "Opciones: " << endl
              << "\t Q: Salir del menu" << endl
              << "\t 1: Visualización en modo inmediato" << endl
              << "\t 2: Visualización en modo diferido" << endl;

         break;

     case SELTAPAS:
       cout << "MENU: Selección de tapas" << endl
            << "Opciones: " << endl
            << "\t Q: Salir del menu" << endl
            << "\t I: Permutar tapas del cilindro" << endl
            << "\t R: Permutar tapas del objeto por revolucion" << endl
            << "\t A: Permutar tapas del cono" << endl;


      break;


     case VALFA:
       cout << "MENU: Modo iluminación - Variar ángulo alfa (luz direccional)" << endl
            << "Opciones: " << endl
            << "\t Q: Salir del menu" << endl
            << "\t <: Disminuir ángulo alfa" << endl
            << "\t >: Aumentar ángulo alfa" << endl
            << "\t B: Variar ángulo beta" << endl;
      break;

      case VBETA:
       cout << "MENU: Modo iluminación - Variar ángulo beta (luz direccional)" << endl
            << "Opciones: " << endl
            << "\t Q: Salir del menu" << endl
            << "\t <: Disminuir ángulo beta" << endl
            << "\t >: Aumentar ángulo beta" << endl
            << "\t A: Variar ángulo alfa" << endl;

         break;


      case MOVMODELO:
         cout << "MENU: Modo movimiento manual del modelo " << endl
             << "Opciones: " << endl
             << "\t Q: Salir del menu" << endl
             << "\t 0: Variar inclinación del cuerpo" << endl
             << "\t 1: Variar altura del cuello" << endl
             << "\t 2: Variar giro de la cabeza" << endl
             << "\t +: Aumentar valor del último seleccionado" << endl
             << "\t -: Disminuir valor del último seleccionado" << endl;
         break;

		case SELLUZ:
			cout << "MENU: Modo movimiento manual del modelo " << endl
			 	  << "Opciones: " << endl
				  << "\t Q: Salir del menu" << endl
			 	  << "\t Z: Cambiar iluminación entre SMOOTH y FLAT" << endl
				  << "\t 0: Activar/desactivar luz 0 (posicional)" << endl
				  << "\t 1: Activar/desactivar luz 1 (direccional)" << endl
				  << "\t A: Variar ángulo alfa" << endl
				  << "\t B: Variar ángulo beta" << endl
				  << "\t P: Activar/desactivar movimiento automatico de luz puntual" << endl;

		   break;

		case SELCAM:
			cout << "MENU: Modo movimiento manual del modelo " << endl
				  << "Opciones: " << endl
				  << "\t Q: Salir del menu" << endl
				  << "\t 0: Seleccionar camara 0 (Perspectiva) " << endl
				  << "\t 1: Seleccionar camara 1 (Ortogonal)" << endl
				  << "\t 2: Seleccionar camara 2 (Perspectiva)" << endl;

			break;

   }

	if (animacion_automatica && modoMenu == NADA){
		cout << "\t +: Aumentar valor de la velocidad" << endl
			  << "\t -: Disminuir valor de la velocidad" << endl;
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
			camaras[camaraActiva].rotarYExaminar(-1*SEXA_TO_RAD);
         break;
	   case GLUT_KEY_RIGHT:
			camaras[camaraActiva].rotarYExaminar(1*SEXA_TO_RAD);
         break;
	   case GLUT_KEY_UP:
			camaras[camaraActiva].rotarXExaminar(-1*SEXA_TO_RAD);

         break;
	   case GLUT_KEY_DOWN:
			camaras[camaraActiva].rotarXExaminar(1*SEXA_TO_RAD);
         break;
	   case GLUT_KEY_PAGE_UP:
			camaras[camaraActiva].zoom(0.8);
         break;
	   case GLUT_KEY_PAGE_DOWN:
			camaras[camaraActiva].zoom(1.2);
         break;
	}

	change_projection(1);

}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
	//std::cout << ratio_xy << std::endl;
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
	//const float wx = float(Height)*ratio_xy ;


	camaras[camaraActiva].setProyeccion();
	//glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{

	const float ratio = (float)newWidth/(float)newHeight;

	for (int i = 0; i < camaras.size(); i++){

		camaras[i].setLeft(camaras[i].getBottom()*ratio);
		camaras[i].setRight(camaras[i].getTop()*ratio);

	}

   change_projection( (float)newWidth/(float)newHeight );
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

	camaras[camaraActiva].setObserver();
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);


	/*
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
	*/

}

void Escena::asignar_materiales(){

   // Materiales obtenidos de:
   // http://devernay.free.fr/cours/opengl/materials.html

   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material ruby({0.1745, 0.01175, 0.01175, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 128.0f * 0.6f );
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811,0.633, 1}, 0.6 * 128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273,0.508273, 0.508273, 1}, 0.4*128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.74151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1} ,0.1 * 128.0f);

   Material difuso({0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 128.0f);
   Material especular({0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 128.0f);




   if (objetoPly != nullptr){
      objetoPly->setMaterial(ruby);
   }

   if (objR != nullptr){
      objR->setMaterial(difuso);
   }

   if (objR2 != nullptr){
      objR2->setMaterial(especular);
   }

	if (cilindro != nullptr){
		cilindro->setMaterial(plata);
	}

   if (tetraedro != nullptr){
      tetraedro->setMaterial(turquesa);
   }

}


void Escena::animacion(){
	if (luz_automatica){
		rotacionLuz0 += velocidadLuz0;
		rotacionLuz0 = fmod(rotacionLuz0, 360);
	}

   if (animacion_automatica){

      rotacionR2D2 += velocidadR2D2;
      rotacionR2D2 = fmod(rotacionR2D2, 360);
      r2d2->animarModeloJerarquico();
   }
}

void Escena::seleccionaCamara(const int numeroCamara){
	camaraActiva = numeroCamara;
	change_projection(1);
	change_observer();
}



void Escena::clickRaton(int boton, int estado, int x, int y){

	xant = x;
	yant = y;

	if (boton == GLUT_RIGHT_BUTTON){

		if (estado == GLUT_DOWN){
			estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
		} else {
			estadoRaton = DESACTIVADO;
		}

	} else if (boton == MOUSE_WHEEL_UP ){
		camaras[camaraActiva].zoom(0.8);
	} else if (boton == MOUSE_WHEEL_DOWN){
		camaras[camaraActiva].zoom(1.2);

	} else if (boton == GLUT_LEFT_BUTTON){
		if (estado == GLUT_UP){
			dibujaSeleccion();
			processPick(x,y);
		}
	}

	change_projection(1);


}


void Escena::ratonMovido(int x, int y){

	if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){
		camaras[camaraActiva].girar(x-xant, y-yant);
		xant = x;
		yant = y;
	}

}


void Escena::dibujaSeleccion(){

	// deshabilitamos el degradado
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE);


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

	change_observer();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	dibujar_objetos(1);



	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE);

}




Tupla3f Escena::centroCamara(const Tupla3f & centro){

	Tupla3f n_centro;

	GLfloat inv[16];

	invertMatrix(mat, inv);


	// aplicamos la transformacion de la matriz al punto
	n_centro(0) = inv[0] * centro(0) + inv[4] * centro(1) + inv[8] * centro(2) + inv[12];
	n_centro(1) = inv[1] * centro(0) + inv[5] * centro(1) + inv[9] * centro(2) + inv[13];
	n_centro(2) = inv[2] * centro(0) + inv[6] * centro(1) + inv[10] * centro(2) + inv[14];

	return n_centro;

}

void Escena::processPick(int x, int y){

	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	GLint viewport[4];
	GLfloat pixel[3];


	glGetIntegerv(GL_VIEWPORT, viewport);

	glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void *) pixel);

	Tupla3f leido = {pixel[0], pixel[1], pixel[2]};

	Tupla3f centro;

	if (cubo != nullptr && leido == cubo->getColorSeleccion()){
		centro = cubo->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = CUBO;


	} else if (tetraedro != nullptr && leido == tetraedro->getColorSeleccion()){
		centro = tetraedro->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = TETRAEDRO;



	} else if (objetoPly != nullptr && leido == objetoPly->getColorSeleccion()){
		centro = objetoPly->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = PLY;


	} else if (objR != nullptr && leido == objR->getColorSeleccion()){
		centro = objR->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = OBJ_R;


	} else if (objR2 != nullptr && leido == objR2->getColorSeleccion()){
		centro = objR2->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = OBJ_R2;

	} else if (cilindro != nullptr && leido == cilindro->getColorSeleccion()){
		centro = cilindro->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = CILINDRO;

	} else if (esfera != nullptr && leido == esfera->getColorSeleccion()){
		centro = esfera->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = ESFERA;


	} else if (cono != nullptr && leido == cono->getColorSeleccion()){
		centro = cono->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = CONO;

	} else if (cuadro != nullptr && leido == cuadro->getColorSeleccion()){
		centro = cuadro->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = CUADRO;

	} else if (r2d2 != nullptr && leido == r2d2->getColorSeleccion()){
		centro = r2d2->getCentro();

		centro = centroCamara(centro);

		camaras[camaraActiva].setAt(centro);

		seleccionado = R2D2;
	} else {
		seleccionado = NINGUNO;
	}



	change_observer();

	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

}
