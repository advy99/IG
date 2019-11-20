#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"


class Textura{
   private:
      GLuint textura_id = 0;
      std::vector<unsigned char> data;
      int width;
      int height;

   public:
      Textura(const std::string & archivo);
      void activar();
};



#endif
