#include "cuerpo.h"

Cuerpo::Cuerpo(){
   cabeza = new Cabeza();
   tronco = new ObjPly("plys/modelo/tronco-r2.ply");
}


void Cuerpo::draw(const dibujado modo_dibujado, const bool ajedrez,\
                  const GLenum sombreado){

   glPushMatrix();

      glPushMatrix();


         glTranslatef(0.0f, 3.3f, 0.0f);

         //AQUI VA UNA TRASLACION CON ARGUMENTO

         cabeza->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();


      glPushMatrix();

         //glTranslatef(0.0f, -4.5f, 0.0f);
         //glScalef(5.5f, 5.5f, 5.5f);
         tronco->draw(modo_dibujado, ajedrez, sombreado);

      glPopMatrix();

   glPopMatrix();


}
