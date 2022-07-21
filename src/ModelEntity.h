//
// Created by Count on 9/5/2021.
//

#ifndef FLOODENGINE_MODELENTITY_H
#define FLOODENGINE_MODELENTITY_H

#include "Entity.h"
#include "Model.h"
#include "StaticShader.h"
#include "SceneLoader.h"

namespace engine {

    extern SceneLoader* LOADER;

    class ModelEntity : public Entity {
    public:
        ModelEntity();
        ModelEntity(Model* model);
        ModelEntity(Model** model, int modelCount);
        ModelEntity(ModelArray models);
        ~ModelEntity();

        virtual void updateShaderParams(ShaderProgram* shader, Model* model) = 0;

        void setModel(Model** model);
        Model** getModel();
        int getModelCount();

    protected:
        Model** m_model = nullptr;
        unsigned int m_modelCount = 0;

        void tick(const float& delta);
    };


}

#endif //FLOODENGINE_MODELENTITY_H
