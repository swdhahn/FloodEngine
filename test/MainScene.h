//
// Created by Seth H. on 12/24/2021.
//

#ifndef FLOODENGINE_MAINSCENE_H
#define FLOODENGINE_MAINSCENE_H

#include <Scene.h>
#include <Terrain.h>
#include <Light.h>
#include <DeferredFramebuffer.h>
#include "FriendlyCube.h"
#include "PlayerCamera.h"

class MainScene : public engine::Scene {
public:
    void init() override;

    void destroy() override;

    void tick(float delta) override;

private:
    FriendlyCube* cube = nullptr;
    engine::Terrain* terrain = nullptr;
    engine::DeferredFramebuffer* framebuffer = nullptr;
    engine::Light* sun = nullptr;

};


#endif //FLOODENGINE_MAINSCENE_H
