#include "GUIEnvironment.hpp"

#include "GUIEntity.hpp"

#include <vector>
#include <algorithm>

namespace rekwarfare {

GUIEnvironment::GUIEnvironment() { }

GUIEnvironment::~GUIEnvironment() { }

void GUIEnvironment::addEntity(GUIEntity* g) {
    m_entities.push_back(g);
}

bool GUIEnvironment::removeEntity(GUIEntity* g) {
    for (auto& e : m_entities) {
        if (e == g) {
            m_entities.erase(std::remove(m_entities.begin(), m_entities.end(),
                e), m_entities.end());
            return true;
        }
    }
    return false;
}

bool GUIEnvironment::removeEntity(GID id) {
    for (auto& e : m_entities) {
        if (*e == id) {
            removeEntity(e);
        }
    }
    return false;
}

}
