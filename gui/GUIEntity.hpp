#pragma once

#include "ent/Entity.hpp"

#include "SDL2/SDL.h"

namespace rekwarfare {

typedef unsigned int GID;

class GUIEntity : public Entity {
public:
    using Entity::Entity;
    bool operator==(const GUIEntity&) const;
    bool operator==(const GID&) const;

private:
    friend class GUIEnvironment;
    GID m_id; // Will be set by the environment
};

}
