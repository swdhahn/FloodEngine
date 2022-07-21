//
// Created by Seth H. on 12/29/2021.
//

#ifndef FLOODENGINE_TEXTURE_H
#define FLOODENGINE_TEXTURE_H

#include "Platform.h"

namespace engine {

    class Texture {
    public:

        Texture(unsigned int* texture, int width, int height, int channels);
        ~Texture();

        void bind(const int& textureUnit);

        unsigned int* getTexture();
        int getWidth();
        int getHeight();

    private:
        unsigned int* m_texture;
        int m_width, m_height, m_channels;
    };

    extern Texture* DEFAULT_TEXTURE;

}

#endif //FLOODENGINE_TEXTURE_H
