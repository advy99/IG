#include "modelojerarquico.h"

R2D2::R2D2(){

   cuerpo = new Cuerpo();

   pierna_izq = new ObjPly("plys/modelo/pierna_izq_r2.ply");
   pierna_der = new ObjPly("plys/modelo/pierna_der_r2");


}
