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

   posicion_original = posicion;

   //TO-DO: Calcular alpha y beta segun la dirección


   // la latitud es el arco cuyo coseno = el valor del eje y / el modulo, es decir,
   // el angulo entre el eje x y la direccion



   //beta = asin( direccion(1)/sqrt(direccion.lengthSq()) );
   alpha = abs(atan2f( direccion(0), direccion(2) ));

   beta = asin( direccion(1)/ sqrt(direccion.lengthSq()) );


   if (direccion(0) < 0){
      alpha += M_PI ;
   }


   /*
   std::cout << alpha * RAD_TO_SEXA << std::endl;
   std::cout << beta  * RAD_TO_SEXA << std::endl;
   std::cout << direccion << std::endl;
   */


};


void LuzDireccional::variarAnguloAlpha(const float incremento){


   alpha += incremento;

   if (alpha > M_PI*2.0 ){
      alpha -= M_PI*2.0;

   } else if (alpha < 0){
      alpha += M_PI*2.0;
   }

   posicion(0) = sin(alpha) * cos(beta) * sqrt(posicion_original.lengthSq());

   posicion(1) = sin(beta) * sqrt(posicion_original.lengthSq());

   posicion(2) = cos(alpha) * cos(beta) * sqrt(posicion_original.lengthSq());

   //std::cout << posicion << " " << alpha * RAD_TO_SEXA << " " << beta * RAD_TO_SEXA << std::endl;


}

void LuzDireccional::variarAnguloBeta(const float incremento){

   beta += incremento;

   // si puedo incrementar beta (esta entre PI/2 y -PI/2)
   if (beta > M_PI/2 ){
      beta = M_PI/2;

   } else if (beta < -(M_PI/2)){
      beta = -(M_PI/2);
   }

   posicion(0) = sin(alpha) * cos(beta) * sqrt(posicion_original.lengthSq());


   posicion(1) = sin(beta) * sqrt(posicion_original.lengthSq());

   posicion(2) = cos(beta) * cos(alpha) * sqrt(posicion_original.lengthSq());


   //std::cout << posicion << " " << alpha * RAD_TO_SEXA << " " << beta * RAD_TO_SEXA << std::endl;


   // PROBAR SI HACER MODULO AL PASARSE O MANTENER AL TOPE

}
