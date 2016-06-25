#pragma once

#include "GUIEntity.hpp"
#include "graphics/Drawer.hpp"

#include <string>

namespace rekwarfare {

class Button : public GUIEntity {
public:
    Button(std::string title);
    ~Button();
    /*
    * Set button state.
    */
    void setPressed(bool);
    void setTitle(std::string);
    // void setListener(Listener);

private:
    friend class GUIEntity;
    bool m_pressed = false;

protected:
    std::string m_title = "Button";
    Font* m_font = nullptr;

    virtual void update() override;
    virtual void render() const override;
};

}
