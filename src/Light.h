//
// Created by Seth H. on 1/1/2022.
//

#ifndef FLOODENGINE_LIGHT_H
#define FLOODENGINE_LIGHT_H

#include "Entity.h"

namespace engine {

    class Light : public Entity {
    public:
        Light();

        void init();

        glm::vec3& getAttenuation();
        void setAttenuation(glm::vec3 attenuation);
        glm::vec3& getColor();
        void setColor(glm::vec3 color);
        float& getStrength();
        void setStrength(float strength);

    protected:
        glm::vec3 m_color;
        glm::vec3 m_attenuation;
        float m_strength;

        void tick(const float& delta);
        void destroy();

    };

}


#endif //FLOODENGINE_LIGHT_H
