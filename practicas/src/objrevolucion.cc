#include "aux.h"
#include "objrevolucion.h"

ObjRevolucion::ObjRevolucion(const std::string & archivo, const int num_instancias,\
                             const bool tapa_sup, const bool tapa_inf){


   //cosas
   std::vector<Tupla3f> perfil;

   ply::read_vertices(archivo, perfil);

   crearMalla(perfil, num_instancias);


}


ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_instancias,\
                             const bool tapa_sup, const bool tapa_inf){


   //cosas
   crearMalla(perfil, num_instancias);

}


void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original,\
                               const int num_instancias){

   //cosas

   Tupla3f vertice;
   float angulo;

   float n_x;
   float n_y;
   float n_z;

   for (int i = 0; i < num_instancias; i++){
      for(int j = 0; j < perfil_original.size(); j++){


         angulo = 2*M_PI*i/num_instancias;
         std::cout << angulo << std::endl;

         n_x = perfil_original[j](0) * cos(angulo) + perfil_original[j](2) * sin(angulo);
         n_y = perfil_original[j](1);
         n_z = perfil_original[j](0) * -sin(angulo) + perfil_original[j](2) * cos(angulo);

         vertice = { n_x , n_y, n_z };

         std::cout << vertice << std::endl;
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


}
