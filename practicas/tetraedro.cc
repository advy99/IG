#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(const float lado)
{

   // inicializar la tabla de vértices

   v.resize(4);

   c.resize(4);

   float l_mediana = sqrt( pow(lado,2) - pow(lado/2, 2) );

   float altura = sqrt( pow(lado,2) - pow(l_mediana/3, 2) );

   // base en plano x, z
   v[0]= {0.0f, 0.0f, 0.0f}; // punto en origen
   v[1]= {lado, 0.0f, 0.0f}; // punto en eje x
   v[2]= {lado/2, 0, l_mediana};

   // vertice superior
   v[3]= {lado/2, altura, l_mediana/3};

   f.resize(4);

   f[0]= {0, 2, 3};
   f[1]= {1, 3, 2};
   f[2]= {0, 1, 2};
   f[3]= {0, 3, 1};
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


   for (auto it = c.begin(); it != c.end(); ++it){
      (*it) = {0, 1, 0};
   }
}
