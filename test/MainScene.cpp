//
// Created by Seth H. on 12/24/2021.
//

#include "MainScene.h"

void MainScene::init() {
    engine::INPUT->addAction(engine::Action("move_forward").addKey(KEY_W));
    engine::INPUT->addAction(engine::Action("move_backward").addKey(KEY_S));
    engine::INPUT->addAction(engine::Action("move_left").addKey(KEY_A));
    engine::INPUT->addAction(engine::Action("move_right").addKey(KEY_D));
    engine::INPUT->addAction(engine::Action("move_up").addKey(KEY_SPACE));
    engine::INPUT->addAction(engine::Action("move_down").addKey(KEY_LEFT_SHIFT));

    engine::INPUT->addAction(engine::Action("look_up").addKey(KEY_UP));
    engine::INPUT->addAction(engine::Action("look_down").addKey(KEY_DOWN));
    engine::INPUT->addAction(engine::Action("look_left").addKey(KEY_LEFT));
    engine::INPUT->addAction(engine::Action("look_right").addKey(KEY_RIGHT));



    engine::WORLD->changeCamera(new PlayerCamera());
    framebuffer = new engine::DeferredFramebuffer(engine::WORLD->getCamera()->getWindowWidth(), engine::WORLD->getCamera()->getWindowHeight());

    engine::WORLD->addFramebuffer(framebuffer);

    sun = new engine::Light();

    sun->setColor(glm::vec3(1, 1, 1));
    sun->setPosition(glm::vec3(0.2, -1, 1));

    addEntity(sun);

    cube = new FriendlyCube();
    terrain = new engine::Terrain(100, 100, 10, 10);
    terrain->startGeneration();

    addEntity(cube);
    addEntity(terrain);

}

void MainScene::destroy() {
    delete terrain;
    delete cube;
    delete sun;
    delete framebuffer;
}

void MainScene::tick(float delta) {

}
