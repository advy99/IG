#include "aux.h"
#include "objrevolucion.h"

ObjRevolucion::ObjRevolucion() {};

ObjRevolucion::ObjRevolucion(const std::string & archivo, const int num_rotaciones,\
                             const bool con_tapas,\
                             const rotacion eje)
									  :eje_rotacion(eje),
                             num_instancias(num_rotaciones) {


   //cosas

   ply::read_vertices(archivo, perfil);

   crearObjeto(con_tapas);
}


ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f> & perfil_n, const int num_rotaciones,\
                             const bool con_tapas,\
									  const rotacion eje)
									  :eje_rotacion(eje),
                              num_instancias(num_rotaciones) {


   //cosas

   perfil = perfil_n;

   crearObjeto(con_tapas);


}

void ObjRevolucion::crearObjeto(const bool con_tapas){

   // cosas

   tapas = true;

   crearMalla(perfil);

   tapas = con_tapas;

   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0, 0.5, 0.5};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original){


   Tupla3f vertice;
   float angulo;

   float n_x;
   float n_y;
   float n_z;


   // perfil modificado para orientarlo ascendentemente y añadir o quitar los polos
   std::vector<Tupla3f> perfil_modificado = perfil_original;


   // segun el eje comprobamos el sentido de los puntos dados
   bool orden_ascendente = sentidoAscendente(perfil_modificado);


   // si no estan en orden ascendente, los invertimos para que lo esten
   // siempre trabajamos con el perfil en orden ascendente
   if (!orden_ascendente){
      std::vector<Tupla3f> invertido (perfil_modificado.rbegin(), perfil_modificado.rend());
      perfil_modificado = invertido;
   }

   // escogemos el punto más al sur y el más al norte
   // obtenemos los polos norte y sur ADVERTENCIA: puede que modifiquemos perfil_modificado


   Tupla3f polo_sur, polo_norte;


   if (tapas)
      calcularPolos(perfil_modificado, polo_sur, polo_norte);




   // añadimos los vertices, rotandolos num_instancias veces segun el eje escogido
   for (int i = 0; i <= num_instancias; i++){

      angulo = 2*M_PI*i/num_instancias;

      for(int j = 0; j < perfil_modificado.size(); j++){



         switch(eje_rotacion){
            case EJE_Y:
               n_x = perfil_modificado[j](0) * cos(angulo) + perfil_modificado[j](2) * sin(angulo);
               n_y = perfil_modificado[j](1);
               n_z = perfil_modificado[j](0) * -sin(angulo) + perfil_modificado[j](2) * cos(angulo);
               break;

            case EJE_X:
               n_x = perfil_modificado[j](0);
               n_y = perfil_modificado[j](1) * cos(angulo) - perfil_modificado[j](2) * sin(angulo);
               n_z = perfil_modificado[j](1) * sin(angulo) + perfil_modificado[j](2) * cos(angulo);
               break;

            case EJE_Z:
               n_x = perfil_modificado[j](0) * cos(angulo) - perfil_modificado[j](1) * sin(angulo);
               n_y = perfil_modificado[j](0) * sin(angulo) + perfil_modificado[j](1) * cos(angulo);
               n_z = perfil_modificado[j](2);
               break;

         }


         // formamos el vertice y lo añadimos
         vertice = { n_x , n_y, n_z };

         v.push_back(vertice);

      }
   }

   //std::cout << v.size() << std::endl;

   // añadimos las caras
   int v1 = 0;
   int v2 = 0;
   int v3 = 0;

   for (int i = 0; i < num_instancias; i++){
      for (int j = 0; j < perfil_modificado.size() - 1; j++){
         v1 = perfil_modificado.size() * i + j;
         v2 = perfil_modificado.size() * (i+1) + j;
         v3 = v2 + 1;
         Tupla3i a = {v1, v2, v3};


         f.push_back({v1, v2, v3});

         v2 += 1;
         v3 = v1 + 1;


         f.push_back({v1, v2, v3});

      }
   }

   perfil = perfil_modificado;

   // insertamos los vertices de los polos si queremos dibujar las tapas



   if (tapas){

      v.push_back(polo_sur);
      v.push_back(polo_norte);

      addTapaSuperior();
      addTapaInferior();

   }


   calcular_normales();

	//num_instancias++;



}


// dato un perfil y un eje sobre el que rotar, comprobamos si los puntos estan
// en orden ascendente o no
bool ObjRevolucion::sentidoAscendente(const std::vector<Tupla3f> & perfil) const{

   bool orden_ascendente;

   switch(eje_rotacion){
      case EJE_X:
         orden_ascendente = perfil.front()(0) < perfil.back()(0);

         break;

      case EJE_Y:
         orden_ascendente = perfil.front()(1) < perfil.back()(1);

         break;

      case EJE_Z:
         orden_ascendente = perfil.front()(2) < perfil.back()(2);
         break;

   }

   return orden_ascendente;
}


// calcular los polos de los ejes
// CUIDADO!!!!! Si los polos existen en perfil, los elimina
void ObjRevolucion::calcularPolos(std::vector<Tupla3f> & perfil,\
											 Tupla3f & polo_sur,\
                                  Tupla3f & polo_norte){


   // cosas
   polo_sur = perfil.front();
   polo_norte = perfil.back();

   int coord1, coord2;

   switch(eje_rotacion){
      case EJE_X:
         //si el polo sur esta en el eje
         coord1 = 1;
         coord2 = 2;

         break;

      case EJE_Y:
         coord1 = 0;
         coord2 = 2;

         break;

      case EJE_Z:
         coord1 = 0;
         coord2 = 1;
         break;

   }


   if (polo_sur(coord1) == 0 && polo_sur(coord2) == 0){
      // lo eliminamos
      perfil.erase(perfil.begin());
   } else {
      // si no tenemos polo sur, creamos la proyeccion de este
      // no hace falta eliminarlo porque no esta
      polo_sur(coord1) = 0;
      polo_sur(coord2) = 0;
   }


   //si el polo norte esta en el eje
   if (polo_norte(coord1) == 0 && polo_norte(coord2) == 0){
      // lo eliminamos
      perfil.pop_back();
   } else {
      // si no tenemos polo sur, creamos la proyeccion de este
      // no hace falta eliminarlo porque no esta
      polo_norte(coord1) = 0;
      polo_norte(coord2) = 0;
   }

}


void ObjRevolucion::addTapaInferior(){

   int v1 = 0;
   int v2 = 0;
   int v3 = 0;


   //v.push_back(polo_sur);


   v2 = v.size() - 2;

   // añadimos la tapa inferior
   for (int i = 0; i < num_instancias - 1; i++){
      //los primeros de cada instancia del perfil
      v1 = perfil.size() * i;

      // el punto polo_sur, que acabamos de añadir
      // lo comentamos, es constante dentro del bucle
      //v2 = v.size() - 1;

      // el siguiente punto con respecto a v1
      // hacemos % v2 para que al llegar al ultimo se ponga a 0 y una el
      // ultimo con el primero
      v3 = v1 + perfil.size();

      f.push_back({v1, v2, v3});


   }
	f.push_back({(int) perfil.size() * (num_instancias - 1), v2, 0});


}

void ObjRevolucion::addTapaSuperior(){

   int v1 = 0;
   int v2 = 0;
   int v3 = 0;

   //v.push_back(polo_norte);

   v2 = v.size() - 1;

   // añadimos la tapa inferior
   for (int i = 0; i < num_instancias - 1; i++){

      //los primeros de cada instancia del perfil
      v1 = perfil.size() * (i + 1) - 1 ;

      // el punto polo_norte, que acabamos de añadir
      //v2 = v.size() - 1;

      // el siguiente punto con respecto a v1
      // hacemos % v2 - 1 para que al llegar al ultimo se ponga a 0 y una el
      // ultimo con el primero
      // retamos uno al hacer el modulo porque vamos al reves dibujando
      // (si lo dibujamos en el mismo sentido GL_CULL_FACE nos impediria ver la cara)
      v3 = v1 + perfil.size();

      f.push_back({v3, v2, v1});



   }

   // ultimo vertice
   v1 = perfil.size() * num_instancias - 1;

   // primer vertice
   v3 = perfil.size() - 1;


   f.push_back({v3, v2, v1});


}


void ObjRevolucion::setTapas(const bool & con_tapas){
   tapas = con_tapas;
}


bool ObjRevolucion::tieneTapas() const{
   return tapas;
}

void ObjRevolucion::pintar(){

   int tam = 3*f.size();

   if (!tapas){
      tam -= (num_instancias * 2) * 3;
   }

   glDrawElements(GL_TRIANGLES, tam, GL_UNSIGNED_INT, f.data());
}


void ObjRevolucion::setTextura(const std::string & archivo){
	textura = new Textura(archivo);

	asignarPuntosTextura(modo_textura);

}


#include <iomanip>

void ObjRevolucion::asignarPuntosTextura(const modoTextura & modo){

	ct.resize(v.size());

	float alpha, beta, h;

	float s, t;

	switch (modo){
		case CILINDRICA:
			for (int i = 0; i < ct.size(); i++){
				alpha = atan2( v[i](2), v[i](0) );
				h = v[i](1);

				s = 1 - ( 0.5 + (alpha/(M_PI*2)) );
				s += 0.5;
				s = fmod(s, 1.0);

				//std::cout << s <<  " " << alpha << std::endl;
				t = (h - perfil.front()(1) ) / (perfil.back()(1) - perfil.front()(1)) ;

				ct[i] = {s, t};

			}

			for (int i = (perfil.size() * num_instancias); i < perfil.size() * (num_instancias + 1); i++){
				alpha = atan2( v[i](2), v[i](0) );
				h = v[i](1);

				s = 1.0f;
				t = (h - perfil.front()(1) ) / (perfil.back()(1) - perfil.front()(1)) ;

				ct[i] = {s, t};
			}

			break;

		case ESFERICA:
			for (int i = 0; i < ct.size(); i++){
				alpha = atan2( v[i](2), v[i](0) );
				beta = atan2( v[i](1), sqrt( pow( v[i](0) ,2) + pow ( v[i](2) ,2) ) );

				s = 1 - ( 0.5 + (alpha/(M_PI*2)) );
				s += 0.5;
				s = fmod(s, 1.0);
				t = 0.5 + beta/M_PI;

				ct[i] = {s, t};
			}

			// asignamos las coordenadas de los extremos
			for (int i = num_instancias; i <= ct.size(); i = i + num_instancias){

				ct[i - num_instancias] = {0.0f, 0.0f};
				ct[i - 1] = {0.0f, 1.0f};
			}

			for (int i = 0; i < num_instancias; i++){
				std::cout << std::setw(10) << v[i] << " " << std::setw(10) << ct[i] << " " << std::setw(10) << i << std::endl;

			}

			std::cout << std::endl << std::endl;

			for (int i = perfil.size() * num_instancias ; i < v.size(); i++){
				alpha = atan2( v[i](2), v[i](0) );
				beta = atan2( v[i](1), sqrt( pow( v[i](0) ,2) + pow ( v[i](2) ,2) ) );

				s = 1;
				t = 0.5 + beta/M_PI;

				ct[i] = {s, t};
				std::cout << std::setw(10) << v[i] << " " << std::setw(10) << ct[i] << " " << std::setw(10) << i << std::endl;
			}



			break;

	}



}
