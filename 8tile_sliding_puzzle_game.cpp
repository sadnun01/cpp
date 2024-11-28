#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <ctime>

void clearConsole() {
    std::cout << "\033[2J\033[H";
}

char getKey() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int** createGrid(int rows, int cols) {
    int** grid = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
    }
    int totalTiles = rows * cols;
    int* tiles = new int[totalTiles];
    for (int i = 0; i < totalTiles - 1; ++i) {
        tiles[i] = i + 1;
    }
    tiles[totalTiles - 1] = 0;
    std::srand(std::time(0));
    for (int i = 0; i < totalTiles; ++i) {
        std::swap(tiles[i], tiles[std::rand() % totalTiles]);
    }
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = tiles[k++];
        }
    }
    delete[] tiles;
    return grid;
}

void deleteGrid(int** grid, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

int countSortedTiles(int** grid, int rows, int cols) {
    int count = 0, expected = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == expected) {
                count++;
                expected++;
            } else {
                return count;
            }
        }
    }
    return count;
}

void displayGrid(int** grid, int rows, int cols, const std::string& lastKey) {
    clearConsole();
    std::cout << "Last Key: " << lastKey << "\n\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 0) std::cout << std::setw(3) << " ";
            else std::cout << std::setw(3) << grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\nCount: " << countSortedTiles(grid, rows, cols) << "\n";
}

bool isSorted(int** grid, int rows, int cols) {
    int expected = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == rows - 1 && j == cols - 1) return true;
            if (grid[i][j] != expected++) return false;
        }
    }
    return true;
}

bool moveTile(int** grid, int rows, int cols, char direction, int& emptyRow, int& emptyCol) {
    int newRow = emptyRow, newCol = emptyCol;
    if (direction == 'A') newRow--;
    else if (direction == 'B') newRow++;
    else if (direction == 'D') newCol--;
    else if (direction == 'C') newCol++;
    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
        std::swap(grid[emptyRow][emptyCol], grid[newRow][newCol]);
        emptyRow = newRow;
        emptyCol = newCol;
        return true;
    }
    return false;
}

int main() {
    const int rows = 3, cols = 3;
    int** grid = createGrid(rows, cols);
    int emptyRow, emptyCol;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                break;
            }
        }
    }
    std::string lastKey = "None";
    while (true) {
        displayGrid(grid, rows, cols, lastKey);
        if (isSorted(grid, rows, cols)) {
            std::cout << "Congratulations! You've solved the puzzle.\n";
            break;
        }
        char key = getKey();
        if (key == '\033') {
            getKey();
            char direction = getKey();
            switch (direction) {
                case 'A': lastKey = "Up"; break;
                case 'B': lastKey = "Down"; break;
                case 'D': lastKey = "Left"; break;
                case 'C': lastKey = "Right"; break;
                default: continue;
            }
            moveTile(grid, rows, cols, direction, emptyRow, emptyCol);
        }
    }
    deleteGrid(grid, rows);
    return 0;
}
