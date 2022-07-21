//
// Created by Seth H. on 12/24/2021.
//

#ifndef FLOODENGINE_FRIENDLYCUBE_H
#define FLOODENGINE_FRIENDLYCUBE_H

#include <ModelEntity.h>

class FriendlyCube : public engine::ModelEntity {
public:
    FriendlyCube();

    void init() override;
    void tick(const float& delta) override;
    void destroy() override;
    void updateShaderParams(engine::ShaderProgram* shader, engine::Model* model) override;

};


#endif //FLOODENGINE_FRIENDLYCUBE_H
