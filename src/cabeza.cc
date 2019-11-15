#include "cabeza.h"

Cabeza::Cabeza(){
   cabeza_ply = new ObjPly("plys/modelo/cabeza-r2.ply");
   cuerpo_movil = new Cilindro(30, 1, 1);

}


void Cabeza::draw(const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();

         //AQUI VA UNA ROTACION CON ARGUMENTO

         cabeza_ply->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         glTranslatef(0.0f, -4.5f, 0.0f);
         glScalef(5.5f, 5.5f, 5.5f);
         cuerpo_movil->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}
