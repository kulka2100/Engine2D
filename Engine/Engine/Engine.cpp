#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "PrimitiveRenderer.h"


int main()
{
    Engine& engine = Engine::getInstance(800, 600, false);
    engine.setLimit(2);
    engine.run();

    return 0;
}