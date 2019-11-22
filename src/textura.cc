#include "textura.h"
#include "jpg_imagen.hpp"



Textura::Textura(const std::string & archivo){
	jpg::Imagen * img = new jpg::Imagen(archivo);

	unsigned char * leidos = img->leerPixels();

	int i = 0;

	width = img->tamX();
	height = img->tamY();

	for (int i = 0; i < width * height; i++){
		// introducimos R
		data.push_back(*leidos);
		leidos++;

		// introducimos R
		data.push_back(*leidos);
		leidos++;

		// introducimos R
		data.push_back(*leidos);
		leidos++;

	}



	// inicializamos a valor nulo
	textura_id = -1;

}


void Textura::activar(){

	//if (textura_id == -1){
		glEnable( GL_TEXTURE_2D );
		glGenTextures(1, &textura_id);
		glBindTexture(GL_TEXTURE_2D, textura_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,\
			          0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

	//}

	glBindTexture(GL_TEXTURE_2D, textura_id);



}
