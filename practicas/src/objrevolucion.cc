#include "aux.h"
#include "objrevolucion.h"

ObjRevolucion::ObjRevolucion() {};

ObjRevolucion::ObjRevolucion(const std::string & archivo, const int num_rotaciones,\
                             const bool tapa_superior, const bool tapa_inferior,\
                             const rotacion eje)
									  :eje_rotacion(eje),
                             num_instancias(num_rotaciones) {


   //cosas
   std::vector<Tupla3f> perfil;


   ply::read_vertices(archivo, perfil);

   tapa_sup = tapa_superior;
   tapa_inf = tapa_inferior;


   crearMalla(perfil);



   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0, 0.5, 0.5};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

}


ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_rotaciones,\
                             const bool tapa_superior, const bool tapa_inferior,\
									  const rotacion eje)
									  :eje_rotacion(eje),
                              num_instancias(num_rotaciones) {


   //cosas

   tapa_sup = tapa_superior;
   tapa_inf = tapa_inferior;

   crearMalla(perfil);


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


   calcularPolos(perfil_modificado, tapa_inf, tapa_sup);



   // añadimos los vertices, rotandolos num_instancias veces segun el eje escogido
   for (int i = 0; i < num_instancias; i++){

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



   // añadimos las caras
   int v1 = 0;
   int v2 = 0;
   int v3 = 0;

   for (int i = 0; i < num_instancias; i++){
      for (int j = 0; j < perfil_modificado.size() - 1; j++){
         v1 = perfil_modificado.size() * i + j;
         v2 = perfil_modificado.size() * ((i+1) % num_instancias) + j;
         v3 = v2 + 1;

         f.push_back({v1, v2, v3});

         v2 += 1;
         v3 = v1 + 1;

         f.push_back({v1, v2, v3});

      }
   }

   perfil = perfil_modificado;

   // insertamos los vertices de los polos si queremos dibujar las tapas

   if (tapa_inf){
      addTapaInferior();

   }


   if (tapa_sup){
      addTapaSuperior();
   }



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
											 const bool tapa_inf,\
                                  const bool tapa_sup){


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
      if (tapa_inf)
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
      if (tapa_sup)
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

   v.push_back(polo_sur);

   v2 = v.size() - 1;

   // añadimos la tapa inferior
   for (int i = 0; i < num_instancias; i++){
      //los primeros de cada instancia del perfil
      v1 = perfil.size() * i;

      // el punto polo_sur, que acabamos de añadir
      // lo comentamos, es constante dentro del bucle
      //v2 = v.size() - 1;

      // el siguiente punto con respecto a v1
      // hacemos % v2 para que al llegar al ultimo se ponga a 0 y una el
      // ultimo con el primero
      v3 = ( v1 + perfil.size() ) % v2;

      f.push_back({v1, v2, v3});
   }

   v1 = perfil.size() * num_instancias;
   v3 = 0;

   f.push_back({ v1, v2, v3 });

}

void ObjRevolucion::addTapaSuperior(){

   int v1 = 0;
   int v2 = 0;
   int v3 = 0;

   v.push_back(polo_norte);

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
      tapa_superior.push_back({v3, v2, v1});

   }

   // ultimo vertice
   v1 = perfil.size() * num_instancias - 1;

   // primer vertice
   v3 = perfil.size() - 1;

   f.push_back({v3,v2,v1});
}



bool operator == (const Tupla3f & t1, const Tupla3f & t2){
   for(int i = 0; i < 3; i++){
      if (t1(i) != t2(i))
         return false;
   }

   return true;
}


void ObjRevolucion::permutarPoloNorte(){


   if (tapa_sup){
      v.pop_back();

      for (int i = 0; i < num_instancias; i++){
         f.pop_back();
      }

   } else {
		v.push_back(polo_norte);
      addTapaSuperior();
	}

   tapa_sup = !tapa_sup;

   c.resize(v.size());



}


void ObjRevolucion::permutarPoloSur(){

	//comprobamos si tiene polo norte, para saber si el polo sur es v.size() - 2
	//o v.size() - 1
   //si tenemos el polo norte

	if (tapa_sup){
      //TODO
   } else {
      if (tapa_inf){
         // si esta, la quitamos
         v.pop_back();

         for (int i = 0; i < num_instancias; i++){
            f.pop_back();
         }
      } else {
         //si no, la añadimos
         v.push_back(polo_sur);
         addTapaSuperior();
      }
   }

   tapa_inf = !tapa_inf;

   c.resize(v.size());

}
