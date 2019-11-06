#include "aux.h"
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


   // la latitud es el arco cuyo coseno = el valor del eje y / el modulo, es decir,
   // el angulo entre el eje x y la direccion



   beta = asin( direccion(1)/sqrt(direccion.lengthSq()) );

   alpha = acos( direccion(2)/ sqrt(direccion.lengthSq()) );

   if (direccion(0) < 0){
      alpha *= -1;
   }


   std::cout << alpha * RAD_TO_SEXA << std::endl;
   std::cout << beta * RAD_TO_SEXA << std::endl;
   std::cout << direccion << std::endl;


};


void LuzDireccional::variarAnguloAlpha(const float incremento){

   alpha += incremento;

   // PROBAR SI HACER MODULO AL PASARSE O MANTENER AL TOPE

}

void LuzDireccional::variarAnguloBeta(const float incremento){

   beta += incremento;

   // PROBAR SI HACER MODULO AL PASARSE O MANTENER AL TOPE

}
