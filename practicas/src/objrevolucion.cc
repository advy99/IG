#include "aux.h"
#include "objrevolucion.h"

ObjRevolucion::ObjRevolucion(const std::string & archivo, const int num_instancias,\
                             const bool tapa_sup, const bool tapa_inf,\
                             const rotacion eje){


   //cosas
   std::vector<Tupla3f> perfil;

   ply::read_vertices(archivo, perfil);

   crearMalla(perfil, num_instancias, eje);


}


ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_instancias,\
                             const bool tapa_sup, const bool tapa_inf,\
                             const rotacion eje){


   //cosas
   crearMalla(perfil, num_instancias, eje);

}


void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original,\
                               const int num_instancias,\
                               const bool tapa_sup, const bool tapa_inf,\
                               const rotacion eje){


   Tupla3f vertice;
   float angulo;

   float n_x;
   float n_y;
   float n_z;

   Tupla3f polo_sur;
   Tupla3f polo_norte;



   // segun el eje comprobamos el sentido de los puntos dados
   bool orden_ascendente = comprobarSentido(perfil_original, eje);


   // si no estan en orden ascendente, los invertimos para que lo esten
   // siempre trabajamos con el perfil en orden ascendente
   if (!orden_ascendente){
      std::vector<Tupla3f> invertido (perfil_original.rbegin(), perfil_original.rend());
      perfil_original = invertido;
   }

   // escogemos el punto más al sur y el más al norte
   polo_sur = perfil_original.front();
   polo_norte = perfil_original.back();


   calcularPolos(perfil, polo_sur, polo_norte, eje);



   for (int i = 0; i < num_instancias; i++){
      for(int j = 0; j < perfil_original.size(); j++){


         angulo = 2*M_PI*i/num_instancias;

         switch(eje){
            case EJE_Y:
               n_x = perfil_original[j](0) * cos(angulo) + perfil_original[j](2) * sin(angulo);
               n_y = perfil_original[j](1);
               n_z = perfil_original[j](0) * -sin(angulo) + perfil_original[j](2) * cos(angulo);
               break;

            case EJE_X:
               n_x = perfil_original[j](0);
               n_y = perfil_original[j](1) * cos(angulo) - perfil_original[j](2) * sin(angulo);
               n_z = perfil_original[j](1) * sin(angulo) + perfil_original[j](2) * cos(angulo);
               break;

            case EJE_Z:
               n_x = perfil_original[j](0) * cos(angulo) - perfil_original[j](1) * sin(angulo);
               n_y = perfil_original[j](0) * sin(angulo) + perfil_original[j](1) * cos(angulo);
               n_z = perfil_original[j](2);
               break;

         }



         vertice = { n_x , n_y, n_z };

         v.push_back(vertice);

      }
   }

   int v1 = 0;
   int v2 = 0;
   int v3 = 0;

   for (int i = 0; i < num_instancias; i++){
      for (int j = 0; j < perfil_original.size() - 1; j++){
         v1 = perfil_original.size() * i + j;
         v2 = perfil_original.size() * ((i+1) % num_instancias) + j;
         v3 = v2 + 1;

         f.push_back({v1, v2, v3});

         v2 += 1;
         v3 = v1 + 1;

         f.push_back({v1, v2, v3});

      }
   }


   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0, 0.5, 0.5};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);


}


// dato un perfil y un eje sobre el que rotar, comprobamos si los puntos estan
// en orden ascendente o no
bool ObjRevolucion::sentidoAscendente(const vector<Tupla3f> & perfil, const rotacion eje ){

   bool orden_ascendente;

   switch(eje){
      case EJE_X:
         orden_ascendente = perfil_original.back()(0) < perfil_original.back()(0);

         break;

      case EJE_Y:
         orden_ascendente = perfil_original.back()(1) < perfil_original.back()(1);

         break;

      case EJE_Z:
         orden_ascendente = perfil_original.back()(2) < perfil_original.back()(2);
         break;

   }

   return orden_ascendente;
}


// calcular los polos de los ejes
// CUIDADO!!!!! Si los polos existen en perfil, los elimina
void ObjRevolucion::calcularPolos(vector<Tupla3f> & perfil, Tupla3f & polo_sur,\
                                  Tupla3f & polo_norte, const rotacion eje){


   // cosas

   int coord1, coord2;

   switch(eje){
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
      perfil_original.erase(perfil_original.begin());
   } else {
      // si no tenemos polo sur, creamos la proyeccion de este
      // no hace falta eliminarlo porque no esta
      polo_sur(coord1) = 0;
      polo_sur(coord2) = 0;
   }

   //si el polo sur esta en el eje
   if (polo_norte(coord1) == 0 && polo_norte(coord2) == 0){
      // lo eliminamos
      perfil_original.erase(perfil_original.begin());
   } else {
      // si no tenemos polo sur, creamos la proyeccion de este
      // no hace falta eliminarlo porque no esta
      polo_norte(coord1) = 0;
      polo_norte(coord2) = 0;
   }

}
