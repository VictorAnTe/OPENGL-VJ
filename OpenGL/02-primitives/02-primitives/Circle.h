#ifndef _CIRCLE_INCLUDE
#define _CIRCLE_INCLUDE


#include "ShaderProgram.h"


// Given a point (x, y) and a size (width, height) in pixels Quad creates 
// a VBO with two triangles. Vertices in the VBO have only a position
// attribute (no colors or texture coordinates)


class Circle
{

private:
	Circle(float x, float y, float radius, int num_seg, ShaderProgram& program);

public:
	// Circle can only be created inside an OpenGL context
	static Circle* createCircle(float x, float y, float radius, int num_seg, ShaderProgram& program); //Le estamos dando la esquina izquierda superior del cuadrado

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;

	int num_seg;

};


#endif // _CIRCLE_INCLUDE

