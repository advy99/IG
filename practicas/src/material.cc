#include "material.h"

Material::Material(){
   // material por defecto :
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMaterial.xml
   ambiente = {0.2, 0.2, 0.2, 1.0f};
   difuso = {0.8, 0.8, 0.8, 1.0f};
   especular = {0.0, 0.0, 0.0, 1.0f};
   brillo = 0;
   emision = {0.0, 0.0, 0.0, 1.0};
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
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}
