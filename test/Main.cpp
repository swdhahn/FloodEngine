#include <Application.h>
#include "MainScene.h"

using namespace engine;

int main() {

    engine::ApplicationData appData;
    appData.m_windowTitle = "Test Game";
    appData.m_windowWidth = 1920;
    appData.m_windowHeight = 1080;
    appData.m_versionMajor = 1;
    appData.m_versionMinor = 0;
    appData.m_versionPatch = 0;
    appData.m_windowResizable = true;
    appData.m_scene = new MainScene();

    engine::Application app(appData);

    delete appData.m_scene;

    // i'm thinkin framebuffer stuff now, shader stuff, lights
    // physics

    // TODO: Finish deferred Shader
    // TODO: Finish remove entities function in Scene.cpp

    return 0;
}