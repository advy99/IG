#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED


class LuzDireccional : public Luz{
   public:
      LuzDireccional(const Tupla2f direccion, const GLenum idLuzOpenGL, \
                     const Tupla4f colorAmbiente, const Tupla4f colorEspecular,\
                     const Tupla4f colorDifuso);
};




#endif
