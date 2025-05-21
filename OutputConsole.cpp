#include "OutputConsole.hpp"

void OutputConsole::setColor(int foreground, int background, int attributes)
{
    std::cout << "\033[" << attributes << ";" << foreground << ";" << background << "m";
}

void OutputConsole::resetColor()
{
    std::cout << "\033[0m";
}

void OutputConsole::printField(GameField gameField, OutputStatus status)
{
    int rows = gameField.GetRow();
    int columns = gameField.GetCol();
    std::cout << "   ";
    for (int i = 0; i < columns; ++i)
    {
        setColor(36);
        std::cout << "  " << i << " ";
        resetColor();
    }
    std::cout << '\n';
    for (int y = 0; y < rows; ++y)
    {
        std::cout << "   ";
        for (int i = 0; i < columns; ++i)
            std::cout << "----";
        std::cout << '\n';

        setColor(36);
        std::cout << " " << y << " ";
        resetColor();
        for (int x = 0; x < columns; ++x)
        {
            std::cout << "|";
            CellStatus cellState = gameField.GetStatus(x, y); // Получаем состояние ячейки
            SegmentState segmentState = SegmentState::Intact;
            if (cellState == CellStatus::Ship) {
                segmentState = gameField.GetSegmentState(x, y);
            }
        
              
            //cellState == CellStatus::Ship &&
            if ((cellState == CellStatus::Unknown) || (status == OutputStatus::HIDDEN && segmentState == SegmentState::Intact))
            {
                setColor(37, 40);   // Белый текст на черном фоне
                std::cout << "   ";
            }
            else if (cellState == CellStatus::Empty)
            {
                setColor(32, 40); // Зеленый текст на черном фоне
                std::cout << " - ";
            }
            else
            {
                if (segmentState == SegmentState::Damaged)
                {
                    setColor(33, 40); // Желтый текст на черном фоне
                    std::cout << " . ";
                }
                else if (segmentState == SegmentState::Destroyed)
                {
                    setColor(31, 40); // Красный текст на черном фоне
                    std::cout << " x ";
                }
                else
                {
                    setColor(34, 40); // Синий текст на черном фоне
                    std::cout << " 0 ";
                }
            }
            resetColor();
        }
        std::cout << "|\n";
    }
    std::cout << "   ";
    for (int i = 0; i < columns; ++i)
        std::cout << "----";
    std::cout << '\n';
}
