#include "cabeza.h"

Cabeza::Cabeza(){
   cabeza_ply = new ObjPly("plys/modelo/cabeza-r2.ply");
   cuerpo_movil = new Cilindro(30, 1, 1);

   giroCabeza        = 0;

}


void Cabeza::draw(const GLenum modo, const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();

         //AQUI VA UNA ROTACION CON ARGUMENTO
         glRotatef(giroCabeza, 0.0f, 1.0f, 0.0f);
         cabeza_ply->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         glTranslatef(0.0f, -4.5f, 0.0f);
         glScalef(5.5f, 5.5f, 5.5f);
         cuerpo_movil->draw(modo, modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}

void Cabeza::modificarGiroCabeza(const float incremento){
   giroCabeza += incremento;

   giroCabeza = fmod(giroCabeza, 360);
}

void Cabeza::animarModeloJerarquico(){
   if (giroCabeza == 0){
      incrementoVelocidad *= -1;
   }

   modificarGiroCabeza(incrementoVelocidad);

}


void Cabeza::modificarVelocidadAnimacion(const float factor){
   incrementoVelocidad *= factor;
}
