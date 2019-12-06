#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(const float lado)
{

   // un cubo tiene 9 vertices
   v.resize(8);


   // y 6 caras, 12 trianguladas
   f.resize(12);

   c.resize(8);
   c_diferido.resize(8);

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



   // cara trasera
   f[0] = {3, 2, 1}; // par
   f[1] = {1, 0, 3}; // impar

   //cara inferior
   f[2] = {0, 1, 4}; // par
   f[3] = {4, 1, 5}; // impar

   // cara derecha
   f[4] = {5, 1, 6}; // par
   f[5] = {1, 2, 6}; // impar

   //cara superior
   f[6] = {6, 2, 7}; // par
   f[7] = {7, 2, 3}; // impar


   //cara izquierda
   f[8] = {7, 3, 0}; // par
   f[9] = {4, 7, 0}; // impar

   //cara delantera
   f[10] = {5, 7, 4}; // par
   f[11] = {5, 6, 7}; // impar



   color_solido = {0, 0, 0};
   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {1, 0, 0};

   colorear(color_solido);
   colorearDiferido(color_diferido);

   calcular_normales();

	textura = new Textura("./img/text-madera.jpg");


	ct.resize(v.size());

	ct[0] = {0.0f, 0.0f};
	ct[1] = {1.0f, 0.0f};
	ct[2] = {0.0f, 1.0f};
	ct[3] = {1.0f, 1.0f};
	ct[4] = {0.0f, 0.0f};
	ct[5] = {1.0f, 0.0f};
	ct[6] = {0.0f, 1.0f};
	ct[7] = {1.0f, 1.0f};

	calcularCentro();

}
