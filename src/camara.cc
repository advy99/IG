#include "camara.h"

Camara::Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up,\
				   const TipoCamara & tipo, const float left, const float right,\
					const float bottom, const float top, \
				   const float near, const float far){

	this->eye   = eye;
	this->at    = at;
	this->up    = up;

	this->tipo  = tipo;
	this->left  = left;
	this->right = right;

	this->near  = near;
	this->far   = far;

}

void Camara::setObserver(){
	gluLookAt(eye(0), eye(1), eye(2),
	          at(0), at(1), at(2),
			    up(0), up(1), up(2) );
}

void Camara::setProyeccion(){

	if (tipo == PERSPECTIVA){
		glFrustum( left, right, bottom, top, near, far );
	} else {
		glOrtho( left, right, bottom, top, near, far );
	}

}
