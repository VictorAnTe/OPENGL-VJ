#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
}


void Scene::init()
{
	initShaders();
	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, program);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	const float WINDOW_WIDTH = 640.f; // Ancho de la ventana
	const float QUAD_WIDTH = 128.f;   // Ancho del cuadrado

	program.use();
	program.setUniformMatrix4f("projection", projection);
	program.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	// Calcula la posición horizontal basada en el tiempo
	float translateX = (currentTime / 10.0f) + 100.0f;
	translateX = fmod(translateX, WINDOW_WIDTH);

	// Normaliza la posición X para calcular el escalado
	float normalizedX = translateX / WINDOW_WIDTH;

	// Calcula el factor de escalado de 1.0 (izquierda) a 0.25 (derecha)
	float scaleValue = 1.0f + (0.25f - 1.0f) * normalizedX;
	scaleValue = glm::clamp(scaleValue, 0.25f, 1.0f);

	// Array de las posiciones iniciales de los cuatro quads
	glm::vec3 quadPositions[4] = {
		glm::vec3(128.f, 48.f, 0.f),
		glm::vec3(384.f, 48.f, 0.f),
		glm::vec3(128.f, 304.f, 0.f),
		glm::vec3(384.f, 304.f, 0.f)
	};

	// Bucle para renderizar cada quad
	for (int i = 0; i < 4; i++) {
		// 1. Crea la matriz de escala (se aplica primero)
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleValue, scaleValue, 1.0f));

		// 2. Crea la matriz de traslación (se aplica después)
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(quadPositions[i].x + translateX, quadPositions[i].y, 0.f));

		// 3. Multiplica las matrices en el orden correcto: Traslación * Escala
		glm::mat4 modelview = translationMatrix * scaleMatrix;

		program.setUniformMatrix4f("modelview", modelview);
		quad->render();
	}
}
void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

