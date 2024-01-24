#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

class AABB {
public:

    // basic
    
    bool Intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x &&
            min.y <= other.max.y && max.y >= other.min.y);
    }

    bool IntersectPoint(const glm::vec2 point) const {
        return (min.x <= point.x && max.x >= point.x &&
                min.y <= point.y && max.y >= point.y);
    }

    // sides

    bool IntersectBottom(const AABB& other) {
        return (min.x <= other.max.x - 23.0f && max.x >= other.min.x + 23.0f &&
            max.y >= other.min.y && max.y <= other.min.y + 25.0f);
    }

    bool IntersectTop(const AABB& other) {
        return (min.x <= other.max.x - 23.0f && max.x >= other.min.x + 23.0f &&
            min.y <= other.max.y && min.y >= other.max.y - 25.0f);
    }

    bool IntersectLeft(const AABB& other) {
        return (min.x <= other.max.x && min.x >= other.max.x - 25.0f &&
            min.y <= other.max.y - 23.0f && max.y >= other.min.y + 23.0f);
    }

    bool IntersectRight(const AABB& other) {
        return (max.x <= other.min.x + 25.0f && max.x >= other.min.x &&
            min.y <= other.max.y - 23.0f && max.y >= other.min.y + 23.0f);
    }

    // Get/Set

    void SetBorder(const glm::vec2& newMin, const glm::vec2& newMax) {
        min = newMin;
        max = newMax;
    }

    glm::vec2 GetMin() { return this->min; }
    glm::vec2 GetMax() { return this->max; }

private:
    glm::vec2 min;
    glm::vec2 max;
};

#endif // !AABB_H