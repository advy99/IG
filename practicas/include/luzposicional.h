#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED


class LuzPosicional : public Luz{
   public:
      LuzPosicional(const Tupla3f posicion, const GLenum idLuzOpenGL, \
                    const Tupla4f colorAmbiente, const Tupla4f colorEspecular,\
                    const Tupla4f colorDifuso);
};




#endif
