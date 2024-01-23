#include "CharacterObject.h"

void CharacterObject::ProcessCollision(GameObject& other)
{
    if (BottomCollision(other)) position.y = other.GetPos().y - size.y - 0.5f;
    else if (LeftCollision(other)) position.x = other.GetPos().x + size.x + 0.5f;
    else if (RightCollision(other)) position.x = other.GetPos().x - size.x - 0.5f;
    else if (TopCollision(other)) position.y = other.GetPos().y + other.GetSize().y + 0.5f;
}
