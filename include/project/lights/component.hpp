#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Component {
    public:
        float r, g, b;

        // reflection components should be in range (0 ... 1)
        Component(float r, float g, float b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        Component() {
            this->r = 0;
            this->g = 0;
            this->b = 0;
        }
};

Component reflectionFromRGB(int r, int g, int b) {
    return Component(r / 255.0, g / 255.0, b / 255.0);
}

#endif