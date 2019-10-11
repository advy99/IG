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

   Tupla3f tapa_superior;
   Tupla3f tapa_inferior;

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

   if (orden_ascendente){
      tapa_inferior = perfil_original.front();
      tapa_superior = perfil_original.back();
   }
   else {
      tapa_inferior = perfil_original.back();
      tapa_superior = perfil_original.front();
   }


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
               n_y = perfil_original[j](1) * cos(angulo) - perfil_original[j](2) * sin(angulo) ;
               n_z = perfil_original[j](1) * sin(angulo) + perfil_original[j](2) * cos(angulo);
               break;

            case EJE_Z:
               n_x = perfil_original[j](0) * cos(angulo) - perfil_original[j](1) * sin(angulo);
               n_y = perfil_original[j](0) * sin(angulo) + perfil_original[j](1) * cos(angulo) ;
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
