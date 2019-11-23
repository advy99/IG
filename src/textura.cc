#include "textura.h"
#include "jpg_imagen.hpp"



Textura::Textura(const std::string & archivo){
	jpg::Imagen * img = new jpg::Imagen(archivo);

	unsigned char * leidos = img->leerPixels();

	width = img->tamX();
	height = img->tamY();

	for (int i = 0; i < width * height; i++){
		// introducimos R
		data.push_back(*leidos);
		leidos++;

		// introducimos G
		data.push_back(*leidos);
		leidos++;

		// introducimos B
		data.push_back(*leidos);
		leidos++;

	}


	// inicializamos a valor nulo
	textura_id = -1;

}


void Textura::activar(){

	glEnable( GL_TEXTURE_2D );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// sin esta linea no funcionan
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	if (textura_id == -1){
		glGenTextures(1, &textura_id);
		glBindTexture(GL_TEXTURE_2D, textura_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

	}

	glBindTexture(GL_TEXTURE_2D, textura_id);



}
