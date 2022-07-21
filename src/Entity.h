#ifndef FLOODENGINE_ENTITY_H
#define FLOODENGINE_ENTITY_H

#include "Platform.h"
#include "WorldManager.h"
#include "Input.h"

namespace engine {

    extern WorldManager* WORLD;
    extern Input* INPUT;

	class Entity {
	public:
		Entity();
        Entity(unsigned long id);
		~Entity();

		void _tick(const float& delta);

        virtual void init() = 0;

		glm::vec3& getPosition();
		glm::vec3& getRotation();
		glm::vec3& getScale();

		void setPosition(glm::vec3 position);
		void setRotation(glm::vec3 rotation);
		void setScale(glm::vec3 scale);
		void setScale(float scale);
		glm::mat4x4 getTransformationMatrix();

        unsigned long getID();
        void _setID(unsigned long _id);

	protected:
        unsigned long m_id = 0;
		glm::vec3 m_position, m_rotation, m_scale;
		glm::mat4x4 m_transformationMatrix;

		virtual void tick(const float& delta) = 0;
        virtual void destroy() = 0;
	};
}

#endif // FLOODENGINE_ENTITY_H