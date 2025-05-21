cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(game 
    main.cpp 
    Ship.cpp 
    ShipManager.cpp 
    Field.cpp 
    Abilities.cpp 
    AbilityManager.cpp 
    Game.cpp 
    State.cpp
    GameController.hpp
    Exeption.cpp
    Input.cpp 
    InteractionWithFile.cpp 
    Output.cpp 
    OutputConsole.cpp 
    
)