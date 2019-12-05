#include "camara.h"

Camara::Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up,\
				   const TipoCamara & tipo, const float near, const float far){

	this->eye   = eye;
	this->at    = at;
	this->up    = up;

	this->tipo  = tipo;

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

float Camara::getLeft() const {
	return left;
}

float Camara::getRight() const {
	return right;
}

float Camara::getBottom() const {
	return bottom;
}

float Camara::getTop() const {
	return top;
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

void Camara::rotarXExaminar(const float angulo){


	eye(1) = cos(angulo)*eye(1) - sin(angulo) * eye(2);


   eye(2) = sin(angulo) * eye(1) + cos(angulo) * eye(2);
}



void Camara::rotarYExaminar(const float angulo){


	eye(0) = cos(angulo)*eye(0) + sin(angulo) * eye(2);


   eye(2) = -sin(angulo) * eye(0) + cos(angulo) * eye(2);
}

void Camara::rotarZExaminar(const float angulo){


	eye(0) = cos(angulo)*eye(0) - sin(angulo) * eye(1);


   eye(1) = sin(angulo) * eye(0) + cos(angulo) * eye(1);
}





void Camara::rotarXFirstPerson(const float angulo){


	at(1) = cos(angulo)*at(1) - sin(angulo) * at(2);


   at(2) = sin(angulo) * at(1) + cos(angulo) * at(2);
}



void Camara::rotarYFirstPerson(const float angulo){


	at(0) = cos(angulo)*at(0) + sin(angulo) * at(2);


   at(2) = -sin(angulo) * at(0) + cos(angulo) * at(2);
}

void Camara::rotarZFirstPerson(const float angulo){


	at(0) = cos(angulo)*at(0) - sin(angulo) * at(1);


   at(1) = sin(angulo) * at(0) + cos(angulo) * at(1);
}

void Camara::girar(int x, int y){
	rotarXFirstPerson(x);
	rotarYFirstPerson(y);

}


void Camara::zoom(const float factor){

	setLeft(getLeft() * factor);
	setRight(getRight() * factor);
	setBottom(getBottom() * factor);
	setTop(getTop() * factor);


}

void Camara::mover(const float x, const float y, const float z){

}
