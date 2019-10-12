#include "esfera.h"


Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf,\
                const float radio){

   // cosas


   std::vector<Tupla3f> perfil;

   // comenzamos con el punto superior
   Tupla3f vertice = {0, radio, 0};

   float n_x;
   float n_y;
   float n_z;

   float angulo = M_PI / num_vert_perfil;

   // rotamos el punto superior con respecto al eje Z
   for (int i = 0; i < num_vert_perfil; i++){
      n_x = vertice(0) * cos(angulo * i) - vertice(1) * sin(angulo * i);
      n_y = vertice(0) * sin(angulo * i) + vertice(1) * cos(angulo * i);
      n_z = vertice(2);

      perfil.push_back( {n_x, n_y, n_z} );
   }

   // cierro la esfera
   perfil.push_back({0, -radio, 0});





   crearMalla(perfil, num_instancias_perf, false, false);
}
