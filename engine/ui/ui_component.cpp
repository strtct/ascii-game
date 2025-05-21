#include "rect.hpp"
#include "../ascii_renderer.hpp"
class UIComponent {

	public:
    	virtual ~UIComponent() = default;

    	// Posición y tamaño
	    virtual int getX() const = 0;
    	virtual int getY() const = 0;
	    virtual int getWidth() const = 0;
    	virtual int getHeight() const = 0;

	    // Función para dibujar el componente
    	virtual void draw() const = 0;

	    // De momento innecesario
    	virtual void handleInput(char key) {}

	    // Métodos comunes, como limpiar el área, podrían ser implementados aquí
		virtual Rect getBounds() const {
            return Rect{getX(), getY(), getWidth(), getHeight()};
        }

protected:
    void clearArea() const {
        for (int y = getY(); y < getY() + getHeight(); ++y) {
            for (int x = getX(); x < getX() + getWidth(); ++x) {
                ascii::draw_char(x, y, ' ');
            }
        }
    }
};

