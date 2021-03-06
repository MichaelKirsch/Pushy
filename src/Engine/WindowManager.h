

#pragma once

#include "SFML/Graphics.hpp"
#include "glad/glad.h"
#include <stdexcept>
#include "glm.hpp"

class WindowManager {
public:
    WindowManager();
    void create(sf::Vector2u resolution={1000,1000}, bool fullscreen= false, float fov = 60, float range = 1000.f);
    void setRange(float newrange);
    glm::vec4 getClearColor(){return clearColor;};
    void setClearColor(glm::vec4 color);
    void swapBuffers();
    void clearScreen();
    glm::mat4 perspectiveProjection;
    sf::Window& getWindow();
    ~WindowManager();

private:
    void refactorProjection();
    sf::Window m_Window;
    float m_fov, m_range;
    bool m_fullscreen;
    sf::Vector2u m_resolution;
    glm::vec4 clearColor;
protected:
};



