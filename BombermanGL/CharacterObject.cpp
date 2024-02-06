#include "CharacterObject.h"

bool CharacterObject::ProcessCollision(GameObject& other, float dt)
{
    if (BottomCollision(other)) position.y -= speed * dt;
    else if (LeftCollision(other)) position.x += speed * dt;
    else if (RightCollision(other)) position.x -= speed * dt;
    else if (TopCollision(other)) position.y += speed * dt;
    else return false;

    return true;
}

bool CharacterObject::ProcessMapCollision(float dt)
{
    if (hBox.GetMin().x <= 145.0f) position.x += speed * dt;
    else if (hBox.GetMax().x >= 1455.0f) position.x -= speed * dt;
    else if (hBox.GetMin().y <= 145.0f) position.y += speed * dt;
    else if (hBox.GetMax().y >= 840.0f) position.y -= speed * dt;
    else return false;
    
    return true;
}

