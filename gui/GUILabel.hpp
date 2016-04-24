#pragma once

#include "GUIEntity.hpp"
#include "graphics/Drawer.hpp"

#include <string>

namespace rekwarfare {

class GUILabel : public GUIEntity {
public:
    GUILabel(std::string l);
    GUILabel(std::string l, Color c);
    virtual void update() override;
    virtual void render() const override;

protected:
    std::string m_label;
    Color m_labelcolor;
};

}
