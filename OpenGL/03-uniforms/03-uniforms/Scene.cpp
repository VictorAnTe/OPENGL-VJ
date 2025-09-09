#include <iostream>
#include <cmath>
#include "Scene.h"


Scene::Scene()
{
	for(int i = 0; i < 4; i++)
		quads[i] = NULL;
}

Scene::~Scene()
{
	for(int i = 0; i < 4; i++)
		if(quads[i] != NULL)
			delete quads[i];
}


void Scene::init()
{
	initShaders();
	for(int i = 0; i < 4; i++)
		quads[i] = Quad::createQuad(-0.75f + (i % 2), -0.75f + (i / 2), 0.5f, 0.5f, program);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	// Calculamos un valor de escalado que dependera del tiempo para darle animación a los rectangulos
	// Estelor oscilará entre 0.0 i 1.0
	float scaleValue = (sin(currentTime / 1000.f) + 1.0f) / 2.0f;
	
	// Change quad colors using elapsed time
	float value = (sin(currentTime / 1000.f) + 1.0f) / 2.0f;

	// Este valor oscila entre 1 (blanco) y 0 (negro)
	float inverted_value = 1.0f - value;

	program.use();
	program.setUniform2f("scale", scaleValue, scaleValue);

	// Gray to white
	program.setUniform4f("color", inverted_value, inverted_value, inverted_value, 1.0f);
	quads[0]->render();

	// Red to white
	program.setUniform4f("color", 1.0f, inverted_value, inverted_value, 1.0f);
	quads[1]->render();

	// Green to white
	program.setUniform4f("color", inverted_value, 1.0f, inverted_value, 1.0f);
	quads[2]->render();

	// Blue to white
	program.setUniform4f("color", inverted_value, inverted_value, 1.0f, 1.0f);
	quads[3]->render();

	//Al empezar desde el 1, 1, 1 en cada color hasta el 1, 0, 0 (por ejemplo el rojo) estamos haciendo que la conversión sea desde el blanco al color original.
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

