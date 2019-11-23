#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

typedef enum {EJE_X, EJE_Y, EJE_Z} rotacion;
typedef enum {CILINDRICA, ESFERICA} modoTextura;

class ObjRevolucion: public Malla3D{
   public:
      ObjRevolucion();

      ObjRevolucion(const std::string & archivo, const int num_instancias,\
                    const bool con_tapas = true,\
                    const rotacion eje = EJE_Y);

      ObjRevolucion(const std::vector<Tupla3f> & perfil, const int num_instancias,\
                    const bool con_tapas = true,\
                    const rotacion eje = EJE_Y);



      bool tieneTapas() const;
      void setTapas(const bool & con_tapas);
		void setTextura(const std::string & n);


   protected:
      void crearMalla(const std::vector<Tupla3f> & perfil_original);

      int num_instancias = 0;
      bool tapas = false;

      void addTapaInferior();
      void addTapaSuperior();
      std::vector<Tupla3f> perfil;

      rotacion eje_rotacion = EJE_Y;

      void pintar() override;

		void asignarPuntosTextura(const modoTextura & modo);

		modoTextura modo_textura = CILINDRICA;




   private:
      bool sentidoAscendente(const std::vector<Tupla3f> & perfil) const;

      // calcular los polos de los ejes
      // CUIDADO!!!!! Si los polos existen en perfil, los elimina
      void calcularPolos(std::vector<Tupla3f> & perfil, Tupla3f & polo_sur,\
                         Tupla3f & polo_norte);

      void crearObjeto(const bool con_tapas);

};






#endif
