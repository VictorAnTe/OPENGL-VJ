#include <GL/glew.h>
#include <GL/gl.h>
#include "Circle.h"


Circle* Circle::createCircle(float x, float y, float radius, int num_seg, ShaderProgram& program)
{
	Circle* circle = new Circle(x, y, radius, num_seg, program);

	return circle;
}


Circle::Circle(float x, float y, float radius, int num_seg, ShaderProgram& program)
{
	float pi = 3.14159265359f;
	float suma_angulo = 2.0f * pi / num_seg;

	float* vertices = new float[num_seg * 3 * 2];

	for (int i = 0; i < num_seg; i++) {
		int indice = i * 6;

		vertices[indice] = x;
		vertices[indice + 1] = y;

		float angulo_actual = i * suma_angulo;

		vertices[indice + 2] = x + radius * cos(angulo_actual);
		vertices[indice + 3] = y + radius * sin(angulo_actual);

		float angulo_siguiente = (i + 1) * suma_angulo;
		vertices[indice + 4] = x + radius * cos(angulo_siguiente);
		vertices[indice + 5] = y + radius * sin(angulo_siguiente);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_seg * 3 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);

	delete[] vertices;
}

void Circle::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, num_seg * 3);
}

void Circle::free()
{
	glDeleteBuffers(1, &vbo);
}

