//
// Created by Seth H. on 12/20/2021.
//

#ifndef FLOODENGINE_SCENE_H
#define FLOODENGINE_SCENE_H

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Entity.h"
#include "ModelEntity.h"
#include "Camera.h"
#include "Light.h"

namespace engine {

    class Scene {
    public:
        std::vector<Scene*> m_children;
        std::vector<Entity*> m_entities;
        std::vector<Light*> m_lights;
        std::unordered_map<Material*, std::unordered_map<ModelEntity*, Model*>> m_renderQueue;

        Scene* m_parent = nullptr;

        Scene();
        ~Scene();

        void _tick(float delta);

        virtual void init() = 0;
        virtual void destroy() = 0;
        virtual void tick(float delta) = 0;

        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);

        void addChild(Scene* scene);
        void removeChild(Scene* scene);

        unsigned long getID();
        void _setID(unsigned long _id);

    protected:
        unsigned long m_id = 0;

    };

}


#endif //FLOODENGINE_SCENE_H
