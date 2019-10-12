#include "cilindro.h"


Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf, \
                    const float altura, const float radio, const bool tapa_sup,\
                    const bool tapa_inf){

   // cosas

   const float distancia_puntos = altura / num_vert_perfil;

   std::vector<Tupla3f> perfil;

   Tupla3f vertice;

   // ponemos los vertices del perfil, los polos los creará crearMalla
   for (int i = 0; i < num_vert_perfil; i++){

      vertice = {radio, i * distancia_puntos, 0};

      perfil.push_back(vertice);
   }


   crearMalla(perfil, num_instancias_perf, tapa_sup, tapa_inf);

}
