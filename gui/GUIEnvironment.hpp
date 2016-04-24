#pragma once

#include "GUIEntity.hpp"

#include <vector>

namespace rekwarfare {

class GUIEnvironment {
public:
    GUIEnvironment();
    ~GUIEnvironment();
    void addEntity(GUIEntity*);
    /*
    * Removes an entity.
    * returns: true if entity was found and removed.
    */
    bool removeEntity(GUIEntity*);
    bool removeEntity(GID id);

private:
    std::vector<GUIEntity*> m_entities;
};

}
