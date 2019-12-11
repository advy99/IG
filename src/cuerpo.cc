#include "cuerpo.h"

Cuerpo::Cuerpo(){
   cabeza = new Cabeza();
   tronco = new ObjPly("plys/modelo/tronco-r2.ply");

   alturaCuello = 0;

	color_seleccion = {0.2, 0.2, 0.2};

}

void Cuerpo::setColorSeleccion(const Tupla3f & c){
	color_seleccion = c;
	tronco->setColorSeleccion(c);
	cabeza->setColorSeleccion(c);
}

Tupla3f Cuerpo::getColorSeleccion() const{
	return color_seleccion;
}

Tupla3f Cuerpo::getCentro() const {
	return tronco->getCentro();
}


void Cuerpo::draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();


         glTranslatef(0.0f, 3.3f, 0.0f);

         //AQUI VA UNA TRASLACION CON ARGUMENTO
         glTranslatef(0.0f, alturaCuello, 0.0f);
         cabeza->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         //glTranslatef(0.0f, -4.5f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         tronco->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}

void Cuerpo::modificarAlturaCuello(const float incremento){
   alturaCuello += incremento;

   if (alturaCuello < 0 ){
      alturaCuello = 0;
   } else if (alturaCuello > tope_cuello){
      alturaCuello = tope_cuello;
   }

}

void Cuerpo::modificarGiroCabeza(const float incremento){
   cabeza->modificarGiroCabeza(incremento);
}

void Cuerpo::animarModeloJerarquico(){
   if (alturaCuello == 0 || alturaCuello == tope_cuello){
      incrementoVelocidad *= -1;
   }

   modificarAlturaCuello(incrementoVelocidad);

   cabeza->animarModeloJerarquico();
}

void Cuerpo::modificarVelocidadAnimacion(const float factor){
   incrementoVelocidad *= factor;

   cabeza->modificarVelocidadAnimacion(factor);
}

void Cuerpo::colorearModo(const GLenum modo){

	tronco->colorearModo(modo);

   cabeza->colorearModo(modo);
}

void Cuerpo::setMaterialUso(const Material & m){
	tronco->setMaterialUso(m);

	cabeza->setMaterialUso(m);
}
