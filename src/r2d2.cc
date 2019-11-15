#include "r2d2.h"

R2D2::R2D2(){

   cuerpo = new Cuerpo();

   pierna_izq = new ObjPly("plys/modelo/pierna_izq_r2.ply");
   pierna_der = new ObjPly("plys/modelo/pierna_der_r2");

}

void R2D2::draw(const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();


         glTranslatef(0.0f, 19.0f, 0.0f);

         //AQUI VA UNA ROTACIÓN CON ARGUMENTO

         cuerpo->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         glTranslatef(7.5f, 0.0f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         pierna_izq->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(-7.5f, 0.0f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         pierna_der->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}
