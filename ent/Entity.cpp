#include "Entity.hpp"

namespace rekwarfare {

Entity::Entity(float x, float y, float w, float h) :
    x(x), y(y), w(w), h(h) { }

bool Entity::collides(Entity e) {
    // could possibly do the opposite and check if not touching
    if ((e.x >= x && e.x <= x + w && e.y >= y && e.y <= y + h) ||
        (e.x + e.w >= x && e.x + e.w <= x + w &&
            e.y + e.h >= y && e.y + e.h <= y + h)) // TODO: Fix this.
        return true;
    return false;
}

}
