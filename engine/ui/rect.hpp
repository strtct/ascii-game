#ifndef RECT_HPP
#define RECT_HPP

struct Rect {
    int x, y, width, height;
    bool contains(int px, int py) const {
        return px >= x && px < x + width &&
               py >= y && py < y + height;
    }
};
#endif // RECT_HPP
