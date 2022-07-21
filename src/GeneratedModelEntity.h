//
// Created by Seth H. on 12/26/2021.
//

#ifndef FLOODENGINE_GENERATEDMODELENTITY_H
#define FLOODENGINE_GENERATEDMODELENTITY_H

#include "ModelEntity.h"

namespace engine {

    class GeneratedModelEntity : public ModelEntity {
    public:
        GeneratedModelEntity();

        void startGeneration();

    protected:
        virtual Model* generate() = 0;
    };

}


#endif //FLOODENGINE_GENERATEDMODELENTITY_H
