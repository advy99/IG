#include "cilindro.h"


Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf, \
                    const float altura, const float radio){

   // cosas

   Tupla3f polo_norte;
   Tupla3f polo_sur;

   polo_sur = {0, 0, 0};
   polo_norte = {0, altura, 0};


   const float distancia_puntos = altura / num_vert_perfil;

   std::vector<Tupla3f> perfil;

   Tupla3f vertice;

   for (int i = 0; i < num_vert_perfil; i++){

      vertice = {radio, i * distancia_puntos, 0};

      perfil.push_back(vertice);
   }


   crearMalla(perfil, num_instancias_perf);

}
