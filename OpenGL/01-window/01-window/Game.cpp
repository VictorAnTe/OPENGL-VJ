#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	color[0] = 0.5f;
	color[1] = 0.5f;
	color[2] = 0.5f;
	color[3] = 1.0f;
	glClearColor(color[0], color[1], color[2], color[3]);
}

bool Game::update(int deltaTime)
{
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;

	// Change clear color based on key pressed
	else if (key == GLFW_KEY_1) {
		color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f; // Red
	}
	else if (key == GLFW_KEY_2) {
		color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; color[3] = 1.0f; // Green
	}
	else if (key == GLFW_KEY_3) {
		color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f; color[3] = 1.0f; // Blue
	}
	glClearColor(color[0], color[1], color[2], color[3]);

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}



