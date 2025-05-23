#ifndef UI_COMPONENT_HPP
#define UI_COMPONENT_HPP
#include "rect.hpp"
#include "ui_type.hpp"

namespace ui {
class UIComponent {
public:
    virtual ~UIComponent() = default;

    virtual void draw() const = 0;

    // Agrega estos métodos si los vas a sobrescribir:
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
	virtual Rect getBounds() const = 0;
	virtual void resize(int newWidth, int newHeight) = 0;
	virtual UIType getType() const = 0; 

};

} // namespace ui

#endif // UI_COMPONENT_HPP
