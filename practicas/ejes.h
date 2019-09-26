#ifndef _EJES_H
#define _EJES_H

class Ejes {

private:
	float axisSize;
	float vertexArray[18];
	float colorArray[18];

public:
	Ejes();
	void changeAxisSize( float newSize );
	void draw();

private:
	void createArrayData();
	
};
#endif
