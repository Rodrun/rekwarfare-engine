#include "Button.hpp"

#include "system/Input.hpp"

namespace rekwarfare {

Button::Button(std::string title)
    : GUIEntity(x, y, w, h), m_title(title) { }

Button::~Button() {

}

void Button::setPressed(bool f) {
    m_pressed = f;
}

void Button::update() {
    
}

void Button::render() const { }

}
