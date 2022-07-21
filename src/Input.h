//
// Created by Seth H. on 12/24/2021.
//

#ifndef FLOODENGINE_INPUT_H
#define FLOODENGINE_INPUT_H

#include <string>
#include <vector>
#include "Platform.h"
#include "Window.h"

namespace engine {



    class Action {
    public:
        Action(std::string name);

        Action& addKey(int keyCode);

        // value between 0 and 1
        float getValue();
        void setValue(float value);

        std::vector<int>& getKeys();
        std::string getName();

    private:
        float m_value = 0;

        std::string m_name;
        std::vector<int> m_keys;
    };

    class Input {
    public:
        Input(Window* window);

        void addAction(Action action);
        float getActionValue(std::string name);

        void tick();
    private:
        Window* m_window;

        std::vector<Action> m_actions;
    };

}


#endif //FLOODENGINE_INPUT_H
