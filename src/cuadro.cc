#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(const float lado)
{

   // un cubo tiene 9 vertices
   v.resize(4);


   // y 6 caras, 12 trianguladas
   f.resize(2);

   c.resize(v.size());
   c_diferido.resize(v.size());

   // inicializar la tabla de vértices
   v[0] = {0.0f, 0.0f, 0.0f};
   v[1] = {lado, 0.0f, 0.0f};
   v[2] = {0.0f, lado, 0.0f};
	v[3] = {lado, lado, 0.0f};


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)



   // cara trasera
   f[0] = {0, 1, 3}; // par
   f[1] = {3, 2, 0}; // impar




   color_solido = {0.9f, 0.9f, 0.9f};
   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {1, 0, 0};

   colorear(color_solido);
   colorearDiferido(color_diferido);

   calcular_normales();

	modo_textura = PLANA;


	ct.resize(v.size());

	ct[0] = {0.0f, 0.0f};
	ct[1] = {1.0f, 0.0f};
	ct[2] = {0.0f, 1.0f};
	ct[3] = {1.0f, 1.0f};


}
