#include <iostream>
#include <fstream>
#include "windows.h"

int** readingFile(int& row, int& column); // Reading a file. Returns an array of the world, the element of the array is 1 if there is life there and 0 if there is no
void readingTwoDimensionalArray(int** array, int row, int column); // Reading an array
void deletingTwoDimensionalArray(int** array, int row, int column); // Deleting an array
void StateWorld(int** const array, int row, int column, int generation, int aliveCells); // Rendering the state of the world
bool EndGameLife(int** const array, int** const prevArray, int row, int column, int generation); // End of game, returns true if the game is over and false if not
int** creatingTwoDimensionalArray(int row, int column); // Creating a 2D Array
void copyingStateWorld(int** const array, int** prevArray, int row, int column); // Copying the state of the world, the first argument stores the real value of the world, the second argument is a copy
int sumAdjacentElements(int** prevArray, int row, int column, int currentRow, int currentColumn); // returns the sum of adjacent elements in an array
void birthLife(int** array, int** prevArray, int row, int column); // In the first argument, based on the second argument, creates a "new life"
void deathLife(int** array, int** prevArray, int row, int column); //  In the first argument based on the second argument "destroys life"
int CalculationNumberLivingCells(int** const array, int row, int column); // Calculates the number of living cells


int main()
{
    int** arrayOfTheUniverse = FP_ZERO;
    int** prevArrayOfTheUniverse = FP_ZERO;
    int row{ 0 }, column{ 0 };
    int generation{ 1 }, aliveCells{ 0 };

    arrayOfTheUniverse = readingFile(row, column);
    prevArrayOfTheUniverse = creatingTwoDimensionalArray(row, column);


    while (true) {

        if (EndGameLife(arrayOfTheUniverse, prevArrayOfTheUniverse, row, column, generation)) {
           break;
        };

        aliveCells = CalculationNumberLivingCells(arrayOfTheUniverse, row, column);

        copyingStateWorld(arrayOfTheUniverse, prevArrayOfTheUniverse, row, column);
        StateWorld(arrayOfTheUniverse, row, column, generation, aliveCells);
        birthLife(arrayOfTheUniverse, prevArrayOfTheUniverse, row, column);
        deathLife(arrayOfTheUniverse, prevArrayOfTheUniverse, row, column);
        generation++;

        Sleep(1000);
    };


    deletingTwoDimensionalArray(arrayOfTheUniverse, row, column);
    deletingTwoDimensionalArray(prevArrayOfTheUniverse, row, column);
    return 0;
};


int** readingFile(int& row, int& column) {

    std::ifstream inputF{ "inputFile.txt" };
    if (inputF.is_open()) {
        inputF >> row;
        inputF >> column;
    };

    if (row > 100) {
        std::cout << "You entered a large number of strings into the array, it automatically changed to 100!" << std::endl;
        row = 100;
    };
    
    if (column > 100) {
        std::cout << "You entered a large number of columns into the array, it automatically changed to 100!" << std::endl;
        column = 100;
    }

    int** array{ new int* [row] };
    for (int i{ 0 }; i < row; i++) {
        array[i] = new int[column] {0};
    }

    int coordinatesRow{ 0 }, coordinatesColumn{ 0 };
    while (true) {
        if (!(inputF >> coordinatesRow)) { break; };
        if (!(inputF >> coordinatesColumn)) { break; };
        if (coordinatesRow >= row) {
            std::cout << "Error. You entered incorrect data for a “live” cell along the y-axis, the value was assigned to the maximum row!" << std::endl;
            coordinatesRow = row - 1;
        };
        if (coordinatesColumn >= column) {
            std::cout << "Error.You entered incorrect data for a “live” cell along the x - axis, the value was assigned to the maximum column!" << std::endl;
            coordinatesColumn = column - 1;
        };
        array[static_cast<int>(coordinatesRow)][static_cast<int>(coordinatesColumn)] = 1;
    };
    

    inputF.close();

    return array;
};
//

void readingTwoDimensionalArray(int** array, int row, int column) {
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            std::cout << array[i][j] << " ";
        };
        std::cout << std::endl;
    }
}
//

void deletingTwoDimensionalArray(int** array, int row, int column) {
    for (int i{ 0 }; i < row; i++) {
        delete[] array[i];
    };
    delete[] array;
}
//

void StateWorld(int** const array, int row, int column, int generation, int aliveCells) {
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            if (array[i][j] == 1) {
                std::cout << "* ";
            }
            else {
                std::cout << "- ";
            }
            
        };
        std::cout << std::endl;
    };
    std::cout << "Generation: " << generation << ". ";
    std::cout << "Alive cells: " << aliveCells << std::endl;
}
//

bool EndGameLife(int** const array, int** const prevArray, int row, int column, int generation) {
    bool endGameLife{ true };
    int aliveCells{ 0 };
    aliveCells = CalculationNumberLivingCells(array, row, column);

    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            array[i][j] == 0 ? (endGameLife = endGameLife && true) : (endGameLife = endGameLife && false);
        };
    };
    if (endGameLife) {
        StateWorld(array, row, column, generation++, aliveCells);
        std::cout << "All cells are dead.Game over!" << std::endl;
        return true;
    };


    endGameLife = true;
     for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            array[i][j] == prevArray[i][j] ? (endGameLife = endGameLife && true) : (endGameLife = endGameLife && false);
        };
    };
    if (endGameLife) {
        StateWorld(array, row, column, generation++, aliveCells);
        std::cout << "The world has stagnated. Game over!" << std::endl;
        return true;
    }
}
//

int** creatingTwoDimensionalArray(int row, int column) {
    int** array{ new int* [row] };
    for (int i{ 0 }; i < row; i++) {
        array[i] = new int[column] {0};
    };
    return array;
}
//

void copyingStateWorld(int** const array, int** prevArray, int row, int column) {
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            prevArray[i][j] = array[i][j];
        };
    };
}
//

int sumAdjacentElements(int** prevArray, int row, int column, int currentRow, int currentColumn) {
    int counter{ 0 };
    for (int i{ -1 }; i <= 1; i++) {
        for (int j{ -1 }; j <= 1; j++) {
            if ( ( (currentRow + i) < 0 ) || ( (currentRow + i) > (row - 1) ) ) continue;
            if (((currentColumn + j) < 0) || ((currentColumn + j) > (column - 1))) continue;
            if (((currentRow + i) == currentRow) && ((currentColumn + j) == currentColumn)) continue;

            counter += prevArray[currentRow + i][currentColumn + j];
        };
    };

    return counter;
}
//

void birthLife(int** array, int** prevArray, int row, int column) {
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {  
            int counter{ 0 };           
            counter = sumAdjacentElements(prevArray, row, column, i, j);
            if (counter == 3) { 
            array[i][j] = 1; 
            };
        }
    }
}
//

void deathLife(int** array, int** prevArray, int row, int column) {
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            int counter{ 0 };
            counter = sumAdjacentElements(prevArray, row, column, i, j);
            if ((counter < 2) || (counter > 3)) {
                array[i][j] = 0;
            };
        }
    }
}
//

int CalculationNumberLivingCells(int** const array, int row, int column) {
    int counter{ 0 };
    for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            counter += array[i][j];
        };
    };

    return counter;
}
//