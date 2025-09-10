#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

//TODO: Revisar SCREEN_SIZE y INIT_PLAYER_PLACE
#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::init()
{
	//initShader()
	//crear mapa "ver en ejemplo Bubble"
	//player = new Player();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	//object->update(deltaTime)
	//player->update(deltaTime)
	//enemy->update(deltaTime)
	//bullet->update(deltaTime)
}

void Scene::render()
{
	glm::mat4 modelview;
	//mirar texturas
	modelview = glm::mat4(1.0f);
	//m�s texturas
	//map->render()
	//object->update(deltaTime)
	//player->update(deltaTime)
	//enemy->update(deltaTime)
	//bullet->update(deltaTime)
}

void Scene::initShaders()
{
	/*Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();*/
}