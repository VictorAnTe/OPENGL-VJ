#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>

class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void initShaders();

private:
	
private:
	float currentTime;
	glm::mat4 projection;
};

#endif // _SCENE_INCLUDE