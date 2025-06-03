#include "InteractionWithFile.h"
#include "Exceptions.h"
#include "State.h"
#include "Exceptions.h"
#include "json.hpp"

InteractionWithFile::InteractionWithFile(const std::string &filename) : filename(filename) {}

InteractionWithFile::~InteractionWithFile()
{
    outfile.close();
    infile.close();
}

std::ofstream InteractionWithFile::open_for_save()
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        throw FileError("Unable to open file for reading");
    }
    return outfile;
}

void InteractionWithFile::close_saving(std::ofstream &outfile)
{
    outfile.close();
}

std::ifstream InteractionWithFile::open_for_writing()
{
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        throw FileError("Unable to open file for writing");
    }
    return infile;
}

void InteractionWithFile::write(std::ifstream &infile, GameState &game)
{
    std::string json_string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
}

void InteractionWithFile::close_writing(std::ifstream &infile)
{
    infile.close();
}

bool InteractionWithFile::Saving(const GameState& state) {
    std::ofstream outFile(filename);

    if (!outFile) {
        throw GameException("Error saving: Unable to open file.");
    }

    outFile << state;

    outFile.close();

    std::ifstream inFile(filename);
    if (inFile) {
        inFile.close();
        return true;
    }
    else {
        throw GameException("Error saving: File verification failed.");
    }
}

GameState& InteractionWithFile::Loading(GameState& state) {
    std::ifstream inFile(filename);

    if (!inFile) {
        throw GameException("Error loading: File not found.");
    }

    inFile >> state;

    inFile.close();

    state.getCompGameField().restoreConnection(state.getCompShipManager());
    state.getUserGameField().restoreConnection(state.getUserShipManager());

    return state;
}
