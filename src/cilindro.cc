#include "cilindro.h"


Cilindro::Cilindro( const int num_instancias_perf, \
                    const float altura, const float radio, const bool tapa_superior,\
                    const bool tapa_inferior, const rotacion eje){

   // cosas
   eje_rotacion = eje;

   //std::vector<Tupla3f> perfil_n;

   num_instancias = num_instancias_perf;

   Tupla3f vertice;

   // ponemos los vertices del perfil, los polos los creará crearMalla

   switch(eje){
      case EJE_X:

         vertice = {0, radio, 0};

         perfil.push_back(vertice);

         vertice = {altura, radio, 0};

         perfil.push_back(vertice);


         break;


      case EJE_Y:

         vertice = {radio, 0 , 0};

         perfil.push_back(vertice);

         vertice = {radio, altura, 0};

         perfil.push_back(vertice);

         break;

      case EJE_Z:


         vertice = {0, radio , 0};

         perfil.push_back(vertice);

         vertice = {0, radio, altura};

         perfil.push_back(vertice);

         break;
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
