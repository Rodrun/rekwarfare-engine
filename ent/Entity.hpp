#pragma once

namespace rekwarfare {

class Entity {
public:
    Entity(float x, float y, float w, float h, float r=0);
    virtual ~Entity() { }
    virtual void update() { }
    virtual void render() const { }
    bool collides(Entity);

    float x;
    float y;
    float w;
    float h;
    float rotation;

};

}
