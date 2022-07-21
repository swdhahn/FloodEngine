//
// Created by Seth H. on 12/24/2021.
//

#ifndef FLOODENGINE_PLAYERCAMERA_H
#define FLOODENGINE_PLAYERCAMERA_H

#include <Camera.h>

class PlayerCamera : public engine::Camera {
public:
    void init() override;
    void destroy() override;

    void tick(const float& delta) override;


};


#endif //FLOODENGINE_PLAYERCAMERA_H
