#include "cono.h"


Cono::Cono( const int num_instancias_perf,\
            const float altura, const float radio, const bool tapa_inferior,\
            const rotacion eje){

   // cosas

   eje_rotacion = eje;
   const int num_vert_perfil = 1;

   Tupla3f polo_norte;
   Tupla3f polo_sur;

   polo_sur   = {0, 0, 0};
   polo_norte = {0, altura, 0};

   num_instancias = num_instancias_perf;


   const float separacion_horizontal = radio / num_vert_perfil;
   const float separacion_vertical = altura / num_vert_perfil;

   switch(eje_rotacion){
      case EJE_X:
         perfil.push_back({0, radio, 0});
         perfil.push_back({altura, 0, 0});

         break;

      case EJE_Y:
         perfil.push_back({radio, 0, 0});
         perfil.push_back({0, altura, 0});
         break;

      case EJE_Z:
         perfil.push_back({0, radio, 0});
         perfil.push_back({0, 0, altura});

         break;


   }

   tapas = true;

   crearMalla(perfil);

   tapas = tapa_inferior;


   c.resize(v.size());
   c_diferido.resize(v.size());

   color_solido = {0.2, 0.2, 0};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

}
