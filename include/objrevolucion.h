#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

typedef enum {EJE_X, EJE_Y, EJE_Z} rotacion;

class ObjRevolucion: public Malla3D{
   public:
      ObjRevolucion();

      ObjRevolucion(const std::string & archivo, const int num_instancias,\
                    const bool tapa_sup = true, const bool tapa_inf = true,\
                    const rotacion eje = EJE_Y);

      ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_instancias,\
                    const bool tapa_sup = true, const bool tapa_inf = true,\
                    const rotacion eje = EJE_Y);


		void permutarTapaSuperior();

		void permutarTapaInferior();

      bool tieneTapaSuperior() const;
      bool tieneTapaInferior() const;


   protected:
      void crearMalla(const std::vector<Tupla3f> & perfil_original);

      int num_instancias = 0;
      //Tupla3f polo_norte;
      //Tupla3f polo_sur;
      bool tapa_inf = false;
      bool tapa_sup = false;

      void addTapaInferior();
      void addTapaSuperior();
      std::vector<Tupla3f> perfil;

      rotacion eje_rotacion = EJE_Y;



   private:
      bool sentidoAscendente(const std::vector<Tupla3f> & perfil) const;

      // calcular los polos de los ejes
      // CUIDADO!!!!! Si los polos existen en perfil, los elimina
      void calcularPolos(std::vector<Tupla3f> & perfil, const bool tapa_inf, \
                         const bool tapa_sup, Tupla3f & polo_sur,\
                         Tupla3f & polo_norte);


};






#endif
