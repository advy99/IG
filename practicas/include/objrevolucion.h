#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"


class ObjRevolucion: public Malla3D{
   public:
      ObjRevolucion(const std::string & archivo, const int num_instancias,\
                    const bool tapa_sup = true, const bool tapa_inf = true);

      ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_instancias,\
                    const bool tapa_sup = true, const bool tapa_inf = true);

   private:
      void crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias);


};






#endif
