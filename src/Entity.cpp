#include "Entity.hpp"

namespace rekwarfare {

Entity::Entity(double x, double y, double w, double h, double r) :
    x(x), y(y), w(w), h(h), rotation(r) { }

bool Entity::collides(Entity e) {
    if (x < e.x + e.w && x + w > e.x &&
		y < e.y + e.h && h + y > e.y)
        return true;
    return false;
}

}
