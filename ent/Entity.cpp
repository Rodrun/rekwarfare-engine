#include "Entity.hpp"

namespace rekwarfare {

Entity::Entity(float x, float y, float w, float h) :
    x(x), y(y), w(w), h(h) { }

bool Entity::collides(Entity e) {
    if (x < e.x + e.w && x + w > e.x &&
		y < e.y + e.h && h + y > e.y)
        return true;
    return false;
}

}
