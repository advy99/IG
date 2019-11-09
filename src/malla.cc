#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

  glEnableClientState( GL_VERTEX_ARRAY );

  glEnableClientState( GL_COLOR_ARRAY );

  glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;

  if (glIsEnabled(GL_LIGHTING)){
     glEnableClientState(GL_NORMAL_ARRAY);
     glNormalPointer(GL_FLOAT,0, nv.data() );

     m.aplicar();
 }




  glColorPointer(3, GL_FLOAT, 0, c.data() );

  glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );


  glDisableClientState( GL_COLOR_ARRAY );

  glDisableClientState( GL_VERTEX_ARRAY );

  glDisableClientState(GL_NORMAL_ARRAY);

  if (glIsEnabled(GL_LIGHTING)){
     glDisableClientState(GL_NORMAL_ARRAY);

 }


}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   if (id_vbo_tri == 0){
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int) , f.data() );
   }

   if (id_vbo_ver == 0){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * 3 * sizeof(float) ,v.data() );
   }

   if(id_vbo_nv == 0){
      id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, nv.size() * 3 * sizeof(float) ,nv.data() );
   }

   if (id_vbo_col == 0){
      id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c_diferido.size() * 3 * sizeof(float) ,c_diferido.data() );
   }

   glEnableClientState(GL_VERTEX_ARRAY);

   glEnableClientState(GL_COLOR_ARRAY);


   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);


   if (glIsEnabled(GL_LIGHTING)){
      glEnableClientState(GL_NORMAL_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);
      glNormalPointer(GL_FLOAT,0, 0 );
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      m.aplicar();

   }



   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);



   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);

   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );

   if (glIsEnabled(GL_LIGHTING)){
      glDisableClientState( GL_LIGHTING );
   }


}


void Malla3D::draw_ModoAjedrez(){


   std::vector<Tupla3i> f_par ;
   std::vector<Tupla3i> f_impar ;


   std::vector<Tupla3f> c_impar (c.size(), color_diferido) ;

   for (int i = 0; i < f.size(); i++){
      if (i % 2 == 0){
         f_par.push_back(f[i]);
      } else {
         f_impar.push_back(f[i]);
      }
   }


   glEnableClientState( GL_VERTEX_ARRAY );

   glEnableClientState( GL_COLOR_ARRAY );

   glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;

   glColorPointer(3, GL_FLOAT, 0, c.data() );

   glDrawElements( GL_TRIANGLES, f_par.size()*3, GL_UNSIGNED_INT, f_par.data() );



   glColorPointer(3, GL_FLOAT, 0, c_impar.data() );

   glDrawElements( GL_TRIANGLES, f_impar.size()*3, GL_UNSIGNED_INT, f_impar.data() );


   glDisableClientState( GL_COLOR_ARRAY );

   glDisableClientState( GL_VERTEX_ARRAY );



}

void Malla3D::colorear(const Tupla3f color){

   // rellenamos el color
   for (auto it = c.begin(); it != c.end(); ++it){
      (*it) = color;
   }

}

void Malla3D::colorearDiferido(const Tupla3f color_dif){

   // rellenamos el color
   for (auto it = c_diferido.begin(); it != c_diferido.end(); ++it){
      (*it) = color_dif;
   }

}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(const dibujado modo_dibujado, const bool ajedrez, const GLenum sombreado)
{
   // completar .....(práctica 1)


   if ( esVisible() ){

      glShadeModel(sombreado);

      if (ajedrez)
         draw_ModoAjedrez();
      else if (modo_dibujado == INMEDIATO)
         draw_ModoInmediato();
      else if (modo_dibujado == DIFERIDO)
         draw_ModoDiferido();

   }


}

Tupla3f Malla3D::getColorSolido() const{
   return color_solido;
}

Tupla3f Malla3D::getColorLinea() const{
   return color_linea;
}

Tupla3f Malla3D::getColorPunto() const{
   return color_punto;
}

Tupla3f Malla3D::getColorDiferido() const {
   return color_diferido;
}

bool Malla3D::esVisible() const{
   return visible;
}

void Malla3D::setVisible(const bool & es_visible){
   visible = es_visible;
}


GLuint Malla3D::CrearVBO( const GLuint tipo_vbo, const GLuint tamanio_bytes,
                          const GLvoid * puntero_ram){

   GLuint id_vbo;
   glGenBuffers(1, &id_vbo);
   glBindBuffer(tipo_vbo, id_vbo);

   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0);

   return id_vbo;
}



void Malla3D::colorearModo(const GLenum modo){
   switch(modo){
      case GL_FILL:
         colorear(getColorSolido());
         break;

      case GL_LINE:
         colorear(getColorLinea());
         break;

      case GL_POINT:
         colorear(getColorPunto());
         break;
   }
}




void Malla3D::calcular_normales(){

   Tupla3f vectorA;
   Tupla3f vectorB;

   Tupla3f perpendicular;
   Tupla3f normal;

   // para cada cara calculamos los vectores, si por ejemplo la cara esta formada
   // por los puntos p, q y r, A = q - p y B = r - p
   // tendremos una normal por cada vertice
   nv.resize(v.size());

   for (auto it = nv.begin(); it != nv.end(); ++it){
      (*it) = {0, 0, 0};
   }

   for (auto it = f.begin(); it != f.end(); ++it){
      vectorA = v.at((*it)(1)) - v.at((*it)(0)) ;
      vectorB = v.at((*it)(2)) - v.at((*it)(0)) ;


      // calculamos la permendicular haciendo el producto vectorial
      perpendicular = vectorA.cross(vectorB);

      // lo normalizamos
      normal = perpendicular.normalized();

      nv[(*it)(0)] = nv[(*it)(0)] + normal;
      nv[(*it)(1)] = nv[(*it)(1)] + normal;
      nv[(*it)(2)] = nv[(*it)(2)] + normal;


   }


   for (auto it = nv.begin(); it != nv.end(); ++it){
      if ((*it).lengthSq() > 0)
         (*it) = (*it).normalized();
   }


}


void Malla3D::setMaterial(const Material & material){
   m = material;
}