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
		float left, right, near, far, bottom, top;

	public:

		Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up,
			    const TipoCamara & tipo, const float near, const float far);

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

		void setEye(const Tupla3f & newEye);
		void setAt(const Tupla3f & newAt);
		void setUp(const Tupla3f & newUp);

		void setLeft(const float & left);
		void setRight(const float & right);
		void setNear(const float & near);
		void setFar(const float & far);

		void setBottom(const float & newBottom);
		void setTop(const float & newTop);

		Tupla3f getEye() const;
		Tupla3f getAt() const;
		Tupla3f getUp() const;

		float getNear() const;
		float getFar() const;
		float getLeft() const;
		float getRight() const;
		float getBottom() const;
		float getTop() const;

		void girar(int x, int y);

};

#endif
