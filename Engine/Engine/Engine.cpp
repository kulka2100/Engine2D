﻿#include <SFML/Graphics.hpp>
#include "Engine.h"


int main()
{
    Engine& engine = Engine::getInstance(800, 600);
    engine.setLimit(2);
    engine.run();

    return 0;
}