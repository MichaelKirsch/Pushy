

#include "GameOver.h"


GameOver::GameOver(StateEssentials &es) : State(es),water(es),terrain(es),ammo(es),terrainGenerator(es),player(terrain,es) {
    essentials.camera.MovementSpeed = 20.f;
    int size = 700;
    timer.setTickrate(0.5);
    terrain.create({0.f,0.f,0.f},400,size,25.f,0.3f,0.005f);
    water.create(terrain,{-100.f,0.f,-100.f},1.0f,size+200,{0, 0.337, 0.921},0.06f,0.15f,0.1);
    ammo.create(terrain,700,1.0);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    player.respawn({10,10,10}, false);
}

void GameOver::updateFrame(float& elapsed) {
    essentials.windowManager.clearScreen();
    water.render();
    terrain.render();
    ammo.render();
    essentials.windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    player.update(elapsed);
    water.update(elapsed);

    for(auto& package:ammo.packages)
    {
        auto dist = glm::distance(package.position,essentials.camera.Position);

        if(dist<10.f)
        {
            if(m_Mouse.isButtonPressed(sf::Mouse::Left))
            {
                package.take();
                ammo.need_refactor = true;
            }
        }
    }
    float test= 0.05f;
    ammo.update(test);
}

void GameOver::processInputs(float& elapsed) {

    sf::Event ev;
    player.processInputs();
    essentials.camera.Position = glm::vec3(player.playerPos.x,player.playerPos.y+4,player.playerPos.z);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    }

    while(essentials.windowManager.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            essentials.shouldClose = true;
        }
        if(ev.type == sf::Event::MouseWheelMoved)
        {
            int deltamouse = ev.mouseWheel.delta;
            essentials.camera.ProcessMouseScroll(deltamouse,1.5f);
        }
    }
}


