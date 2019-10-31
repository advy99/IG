#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla3f direccion,\
                               const GLenum idLuzOpenGL, \
                               const Tupla4f colorAmbiente,\
                               const Tupla4f colorEspecular,\
                               const Tupla4f colorDifuso){

   id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;


   this->posicion = {direccion(0), direccion(1), direccion(2), 0};

   //TO-DO: Calcular alpha y beta segun la dirección


   Tupla3f ejeY = {0,1,0};
   Tupla3f ejeX = {1,0,0};
   Tupla3f direccionNormalizada = direccion.normalized();


};
