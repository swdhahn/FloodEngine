//
// Created by Seth H. on 7/4/2022.
//

#ifndef FLOODENGINE_UNIFORMBUFFEROBJECT_H
#define FLOODENGINE_UNIFORMBUFFEROBJECT_H

#include "Platform.h"

namespace engine {
    class UniformBufferObject {
    public:
        /**
         * @param index : the index at which the UniformBufferObject binds to internally, must be unique and greater than 0
         * @param size : the size of the buffer in floats
         */
        UniformBufferObject(const uint32_t& index, const uint32_t& size);
        /**
         * @param buffer : new buffer to be sent to gpu
         * @param size : the size of the buffer in floats
         */
        void update(float* buffer, const uint32_t& size);
        /**
         * @param offset : offset into the buffer
         * @param buffer : new buffer to be sent to gpu
         * @param size : the size of the buffer in floats
         */
        void update(const uint32_t& offset, float* buffer, const uint32_t& size);

        int getIndex();

        static int getMaxUniformBufferBindings();
    private:
        bool first = true;
        unsigned int m_ubo = 0;
        int m_index;
        static int m_uboMaxSize;
    };
}


#endif //FLOODENGINE_UNIFORMBUFFEROBJECT_H
