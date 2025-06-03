#ifndef OUTPUT_CONSOLE_HPP
#define OUTPUT_CONSOLE_HPP
#include "Field.h"

enum OutputStatus
{
    HIDDEN,
    OPENED
};

class OutputConsole
{
public:
    void printField(GameField gameField, OutputStatus status);

private:
    void setColor(int foreground, int background = 40, int attributes = 0);
    void resetColor();
};

#endif