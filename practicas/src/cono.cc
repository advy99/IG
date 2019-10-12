#include "cono.h"


Cono::Cono( const int num_vert_perfil, const int num_instancias_perf,\
            const float altura, const float radio){

   // cosas

   Tupla3f polo_norte;
   Tupla3f polo_sur;

   polo_sur   = {0, 0, 0};
   polo_norte = {0, altura, 0};

   const float longitud_perfil = sqrt( pow(altura, 2) + pow(radio, 2) );

   const float separacion_puntos_perfil = longitud_perfil / num_vert_perfil;


}
