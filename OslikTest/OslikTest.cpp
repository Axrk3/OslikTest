#include "Engine.h"
#include "Levels.h"

using namespace sf;

int main()
{
    Engine engine;
    engine.start();

    //Thread engineThread(&Engine::start, &engine);
    //engineThread.launch();
    //engineThread.wait();

    return 0;
}