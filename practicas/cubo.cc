#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // un cubo tiene 9 vertices
   v.resize(8);


   // y 6 caras, 12 trianguladas
   f.resize(12);

   // inicializar la tabla de vértices
   v[0] = {0.0f, 0.0f, 0.0f};
   v[1] = {lado, 0.0f, 0.0f};
   v[2] = {lado, lado, 0.0f};
   v[3] = {0.0f, lado, 0.0f};
   v[4] = {0.0f, 0.0f, lado};
   v[5] = {lado, 0.0f, lado};
   v[6] = {lado, lado, lado};
   v[7] = {0.0f, lado, lado};


   //v[8] = {lado, 0.0f, lado};


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f[0] = {0, 3, 2};
   f[1] = {0, 2, 1};

   f[2] = {7, 3, 0};
   f[3] = {4, 7, 0};

   f[4] = {4, 6, 7};
   f[5] = {4, 5, 6};

   f[6] = {5, 1, 6};
   f[7] = {6, 1, 2};

   f[8] = {7, 2, 3};
   f[9] = {7, 6, 2};

   f[10] = {0, 1, 4};
   f[11] = {4, 1, 5};


}
