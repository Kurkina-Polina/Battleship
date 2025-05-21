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
    //json j = json::parse(json_string); перенести из State
    //infile >> game;
}

void InteractionWithFile::close_writing(std::ifstream &infile)
{
    infile.close();
}

// Функция для сохранения GameState в файл
bool InteractionWithFile::Saving(const GameState& state) {
    // Имя файла для сохранения
    std::ofstream outFile(filename);

    // Проверяем, удалось ли открыть файл
    if (!outFile) {
        throw GameException("Error saving: Unable to open file.");
    }

    // Записываем GameState в файл
    outFile << state;

    // Закрываем файл
    outFile.close();

    // Проверяем, что файл был успешно записан
    std::ifstream inFile(filename);
    if (inFile) {
        inFile.close();
        return true;
    }
    else {
        throw GameException("Error saving: File verification failed.");
    }
}

// Функция для загрузки GameState из файла
GameState& InteractionWithFile::Loading(GameState& state) {
    // Открываем файл для чтения
    std::ifstream inFile(filename);

    // Проверяем, удалось ли открыть файл
    if (!inFile) {
        throw GameException("Error loading: File not found.");
    }

    // Считываем GameState из файла
    inFile >> state;

    // Закрываем файл
    inFile.close();

    // Восстанавливаем связи в игровом состоянии
    state.getCompGameField().restoreConnection(state.getCompShipManager());
    state.getUserGameField().restoreConnection(state.getUserShipManager());

    return state;
}
