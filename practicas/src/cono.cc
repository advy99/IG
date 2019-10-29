#include "cono.h"


Cono::Cono( const int num_vert_perfil, const int num_instancias_perf,\
            const float altura, const float radio, const bool tapa_inferior){

   // cosas



   Tupla3f polo_norte;
   Tupla3f polo_sur;

   polo_sur   = {0, 0, 0};
   polo_norte = {0, altura, 0};

   num_instancias = num_instancias_perf;


   const float separacion_horizontal = radio / num_vert_perfil;
   const float separacion_vertical = altura / num_vert_perfil;

   for (int i = 0; i <= num_vert_perfil; i++){
      perfil.push_back({separacion_horizontal * ( num_vert_perfil - i) , separacion_vertical * i, 0});
   }

   tapa_sup = true;
   tapa_inf = tapa_inferior;

   crearMalla(perfil);


   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0.2, 0.2, 0};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

}
