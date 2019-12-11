#include "r2d2.h"

R2D2::R2D2(){

   cuerpo = new Cuerpo();

   pierna_izq = new ObjPly("plys/modelo/pierna_izq_r2.ply");
   pierna_der = new ObjPly("plys/modelo/pierna_der_r2");

   inclinacionCuerpo = 0;

	color_seleccion = {0.2, 0.2 , 0.2};
	setColorSeleccion(color_seleccion);

}

void R2D2::setColorSeleccion(const Tupla3f & c){
	color_seleccion = c;
	pierna_der->setColorSeleccion(c);
	pierna_izq->setColorSeleccion(c);
	cuerpo->setColorSeleccion(c);
}

Tupla3f R2D2::getColorSeleccion() const{
	return color_seleccion;
}

Tupla3f R2D2::getCentro() const{
	return cuerpo->getCentro();
}

void R2D2::draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();


         glTranslatef(0.0f, 19.0f, 0.0f);

         //AQUI VA UNA ROTACIÓN CON ARGUMENTO

         glRotatef(inclinacionCuerpo, 1.0f, 0.0f, 0.0f);
         cuerpo->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         glTranslatef(7.5f, 0.0f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         pierna_izq->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(-7.5f, 0.0f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         pierna_der->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}

void R2D2::modificarInclunacionCuerpo(const float incremento){
   inclinacionCuerpo += incremento;

   if (inclinacionCuerpo > 90){
      inclinacionCuerpo = 90;
   } else if (inclinacionCuerpo < -90) {
      inclinacionCuerpo = -90;
   }

}

void R2D2::modificarGiroCabeza(const float incremento){
   cuerpo->modificarGiroCabeza(incremento);
}

void R2D2::modificarAlturaCuello(const float incremento){
   cuerpo->modificarAlturaCuello(incremento);
}

void R2D2::animarModeloJerarquico(){
   if (inclinacionCuerpo == 90 || inclinacionCuerpo == -90){
      incrementoVelocidad *= -1;
   }

   modificarInclunacionCuerpo(incrementoVelocidad);

   cuerpo->animarModeloJerarquico();
}


void R2D2::modificarVelocidadAnimacion(const float factor){
   incrementoVelocidad *= factor;

   cuerpo->modificarVelocidadAnimacion(factor);
}

void R2D2::colorearModo(const GLenum modo){

	pierna_der->colorearModo(modo);
	pierna_izq->colorearModo(modo);

   cuerpo->colorearModo(modo);
}
