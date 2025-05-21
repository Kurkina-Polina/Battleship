#ifndef INTERACTION_WITH_FILE_HPP
#define INTERACTION_WITH_FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "State.h"
#include "Exceptions.h"
#include "json.hpp"

using json = nlohmann::json;
class GameState;

class InteractionWithFile
{
public:
    InteractionWithFile(const std::string &filename);
    ~InteractionWithFile();
    std::ofstream open_for_save();
    void save(std::ofstream &outfile, const GameState &gameState);
    void close_saving(std::ofstream &outfile);
    std::ifstream open_for_writing();
    void write(std::ifstream &infile, GameState &game);
    void close_writing(std::ifstream &infile);

    bool Saving(const GameState& state);
    GameState& Loading(GameState& state);

private:
    std::string filename;
    std::ifstream infile;
    std::ofstream outfile;
};

#endif
