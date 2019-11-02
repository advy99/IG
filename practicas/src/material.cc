#include "material.h"

Material::Material(){
}

Material::Material(const Tupla4f amb, const Tupla4f dif, \
                   const Tupla4f esp, const float bri){


   // clase material
   ambiente = amb;
   difuso = dif;
   especular = esp;
   brillo = bri;

}


void Material::aplicar(){
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &brillo);
}
