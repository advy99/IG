#include "camara.h"

Camara::Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up,\
				   const TipoCamara & tipo, const float left, const float right,\
				   const float near, const float far){

	this->eye   = eye;
	this->at    = at;
	this->up    = up;

	this->tipo  = tipo;
	this->left  = left;
	this->right = right;

	this->bottom = left;
	this->top = top;

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
		//std::cout << near << " ";
		glFrustum( left, right, bottom, top, near, far );
	} else {
		glOrtho( left, right, bottom, top, near, far );
	}

}


void Camara::setUp(const Tupla3f & newUp){
	up = newUp;
}

void Camara::setAt(const Tupla3f & newAt){
	at = newAt;
}

void Camara::setEye(const Tupla3f & newEye){
	eye = newEye;
}

void Camara::setLeft(const float & newLeft){
	left = newLeft;
}

void Camara::setRight(const float & newRight){
	right = newRight;
}

void Camara::setBottom(const float & newBottom){
	bottom = newBottom;
}

void Camara::setTop(const float & newTop){
	top = newTop;
}


void Camara::setNear(const float & newNear){
	near = newNear;
}
void Camara::setFar(const float & newFar){
	far = newFar;
}

float Camara::getNear() const {
	return near;
}

float Camara::getFar() const {
	return far;
}


Tupla3f Camara::getEye() const{
	return eye;
}

Tupla3f Camara::getAt() const {
	return at;
}

Tupla3f Camara::getUp() const {
	return up;
}
