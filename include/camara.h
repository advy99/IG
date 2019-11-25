#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {ORTOGONAL, PERSPECTIVA} TipoCamara;

class Camara{
	private:
		Tupla3f eye;
		Tupla3f at;
		Tupla3f up;

		TipoCamara tipo;

		float left, right, near, far;

	public:

		Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up);

		void rotarXExaminar(const float angulo);
		void rotarYExaminar(const float angulo);
		void rotarZExaminar(const float angulo);

		void rotarXFirstPerson(const float angulo);
		void rotarYFirstPerson(const float angulo);
		void rotarZFirstPerson(const float angulo);

		void mover(const float x, const float y, const float z);
		void zoom(const float factor);


		void setObserver();
		void setProyeccion();

};

#endif
