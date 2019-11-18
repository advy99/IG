#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"


class Textura{
   private:
      GLuint textura_id = 0;
      std::vector<unsigned char> data;
      int width, Height;

   public:
      Textura(const string & archivo);
      void activar();
}



#endif
