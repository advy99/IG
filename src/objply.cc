#include "objply.h"
#include "ply_reader.h"



ObjPly::ObjPly(const std::string & nombre){
   ply::read(nombre, v, f);

   c.resize(v.size());
   c_diferido.resize(c.size());

   color_solido = {0, 0, 0};

   color_linea = {0, 1, 0};
   color_punto = {0, 0, 1};

   color_diferido = {0, 0, 1};
   colorear(color_solido);
   colorearDiferido(color_diferido);

   calcular_normales();
	calcularCentro();

}
