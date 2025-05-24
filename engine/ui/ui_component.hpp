#ifndef UI_COMPONENT_HPP
#define UI_COMPONENT_HPP
#include "rect.hpp"
#include "ui_type.hpp"

namespace ui {
class UIComponent {
public:
	UIComponent(int x, int y, int width, int height, int zindex, int vindex) : x_(x), y_(y), width_(width), height_(height), zindex_(zindex), vindex_(vindex) {}

    virtual ~UIComponent() = default;

    virtual void draw() const = 0;

    // Agrega estos métodos si los vas a sobrescribir:
    virtual int getX() const { return x_; };
    virtual int getY() const { return y_; };
    virtual int getWidth() const { return width_; };
    virtual int getHeight() const { return height_; };
	virtual Rect getBounds() {
		return Rect{getX(), getY(), getWidth(), getHeight()};
	}
	virtual void resize(int newWidth, int newHeight) = 0;
	virtual UIType getType() const = 0; 
    virtual int getZIndex() const { return zindex_; }
    virtual int getVIndex() const { return vindex_; }
	void clearArea() const;
protected:
	int x_, y_, width_, height_, zindex_, vindex_;

}; // class 
}; // namespace 
#endif // UI_COMPONENT_HPP
