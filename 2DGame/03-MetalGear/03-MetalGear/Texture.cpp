#include <SOIL.h>
#include "Texture.h"


using namespace std;

//Inicializa los atributos de la textura
Texture::Texture()
{
	wrapS = GL_REPEAT;
	wrapT = GL_REPEAT;
	minFilter = GL_LINEAR_MIPMAP_LINEAR;
	magFilter = GL_LINEAR_MIPMAP_LINEAR;
}

// Carga una imagen desde archivo y la crea como textura en la GPU
bool Texture::loadFromFile(const string& filename, PixelFormat format)
{
	unsigned char* image = NULL;

	//Modos RGB y RGBA
	switch (format)
	{
	case TEXTURE_PIXEL_FORMAT_RGB:
		image = SOIL_load_image(filename.c_str(), &widthTex, &heightTex, 0, SOIL_LOAD_RGB);
		break;
	case TEXTURE_PIXEL_FORMAT_RGBA:
		image = SOIL_load_image(filename.c_str(), &widthTex, &heightTex, 0, SOIL_LOAD_RGBA);
		break;
	}
	if (image == NULL)
		return false;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	switch (format)
	{
	case TEXTURE_PIXEL_FORMAT_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTex, heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		break;
	case TEXTURE_PIXEL_FORMAT_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTex, heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

// Crea una textura en escala de grises a partir de un buffer de glifos
void Texture::loadFromGlyphBuffer(unsigned char* buffer, int width, int height)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

// Crea una textura vacía en la GPU con las dimensiones dadas
void Texture::createEmptyTexture(int width, int height)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

// Actualiza una parte de la textura con datos de un buffer de glifos
void Texture::loadSubtextureFromGlyphBuffer(unsigned char* buffer, int x, int y, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

// Genera los mipmaps de la textura actual
void Texture::generateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenerateMipmap(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

//Modo repeticion en S y T y filtros min y mag
void Texture::setWrapS(GLint value)
{
	wrapS = value;
}

void Texture::setWrapT(GLint value)
{
	wrapT = value;
}

void Texture::setMinFilter(GLint value)
{
	minFilter = value;
}

void Texture::setMagFilter(GLint value)
{
	magFilter = value;
}

// Activa la textura y aplica sus parámetros para renderizar
void Texture::use() const
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}