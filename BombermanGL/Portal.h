#ifndef PORTAL_H
#define PORTAL_H

#include "GameObject.h"
class Portal : public GameObject
{
public:

	Portal(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		SetTexture(ResourceManager::GetTexture("portal"));
	};

	~Portal() {};

private:

};

#endif // !PORTAL_H