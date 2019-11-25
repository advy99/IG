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
		Camara();

		void rotarXExaminar(const float angulo);
		void rotarYExaminar(const float angulo);
		void rotarZExaminar(const float angulo);

		void rotarXFirstPerson(const floar angulo);
		void rotarYFirstPerson(const floar angulo);
		void rotarZFirstPerson(const floar angulo);

		void mover(const float x, const float y, const float z);
		void zoom(const float factor);


		void setObserver();
		void setProyeccion();

};

#endif
