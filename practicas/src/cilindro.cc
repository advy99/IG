#include "cilindro.h"


Cilindro::Cilindro( const int num_instancias_perf, \
                    const float altura, const float radio, const bool tapa_superior,\
                    const bool tapa_inferior){

   // cosas

   const int num_vert_perfil = 2;

   const float distancia_puntos = altura / num_vert_perfil;

   //std::vector<Tupla3f> perfil_n;

   num_instancias = num_instancias_perf;

   Tupla3f vertice;

   // ponemos los vertices del perfil, los polos los creará crearMalla
   for (int i = 0; i < num_vert_perfil; i++){

      vertice = {radio, i * distancia_puntos, 0};

      perfil.push_back(vertice);
   }

   tapa_sup = tapa_superior;
   tapa_inf = tapa_inferior;

   crearMalla(perfil);

   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0.7, 0, 0.7};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

}
