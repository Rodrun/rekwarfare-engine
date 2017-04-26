#pragma once

#include "Texture.hpp"

#include <memory>

namespace rekwarfare {

class Entity {
public:
    /*
    * Entity constructor.
    * r: rotation.
    */
    Entity(double x, double y, double w, double h, double r=0);
    virtual ~Entity() { };
    virtual void update(double delta) { };
    virtual void render() const { };
    /*
    * Check if entity intersects with another (quadrilateral).
    */
    bool collides(Entity);

    double x;
    double y;
    double w;
    double h;
    double rotation;

protected:
    std::shared_ptr<Texture> m_texture;

};

}
