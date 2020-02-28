

#include "WindowManager.h"

WindowManager::WindowManager(sf::Vector2i resolution, bool fullscreen) {
    sf::ContextSettings settings;
    settings.depthBits = 8;
    settings.antialiasingLevel = 4;
    settings.minorVersion = 3;
    settings.majorVersion = 4;
    if(!fullscreen)
        m_Window.create(sf::VideoMode(resolution.x,resolution.y),"Pushy", sf::Style::Default, settings);
    else
        m_Window.create(sf::VideoMode(resolution.x,resolution.y),"Pushy", sf::Style::Fullscreen , settings);

    m_Window.setActive();
    if(!gladLoadGL())
    {
        std::runtime_error("Glad is not loading");
    }
    glViewport(0, 0, m_Window.getSize().y,m_Window.getSize().y);
    glClearColor(0.027f, 0.7f, 0.9f, 1.0f);
}

WindowManager::~WindowManager() {
    m_Window.close();
}

void WindowManager::swapBuffers() {
    m_Window.display();
}

sf::Window &WindowManager::getWindow() {
    return m_Window;
}

void WindowManager::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


