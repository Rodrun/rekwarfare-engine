#include "GUIEntity.hpp"

namespace rekwarfare {

GUIEntity::GUIEntity(float x, float y, float w, float h)
    : Entity(x, y, w, h) { }

bool GUIEntity::operator==(const GUIEntity& o) const {
    if (o.m_id == m_id) return true;
    return false;
}

bool GUIEntity::operator==(const GID& g) const {
    if (m_id == g) return true;
    return false;
}

}
