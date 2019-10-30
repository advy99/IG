#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

class Material{

   private:
      Tupla4f ambiente;
      Tupla4f especular;
      Tupla4f difuso;
      float brillo;

   public:
      Material(const Tupla4f ambiente, const Tupla4f difuso,\
               const Tupla4f especular, const float brillo);

      void aplicar();

};

#endif
