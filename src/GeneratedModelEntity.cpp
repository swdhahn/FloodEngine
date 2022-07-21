//
// Created by Seth H. on 12/26/2021.
//

#include "GeneratedModelEntity.h"


engine::GeneratedModelEntity::GeneratedModelEntity() {

}

void engine::GeneratedModelEntity::startGeneration() {
    m_model = new Model*[1]{generate()};
    m_modelCount = 1;
}
