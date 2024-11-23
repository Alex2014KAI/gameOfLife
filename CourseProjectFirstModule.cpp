#include <iostream>
#include <fstream>
#include <string.h>

int** readingFile(int& row, int& column); // Reading a file. Returns an array of the world, the element of the array is 1 if there is life there and 0 if there is no
void readingTwoDimensionalArray(int** array, int row, int column); // Reading an array
void deletingTwoDimensionalArray(int** array, int row, int column); // Deleting an array
void StateWorld(int** const array, int row, int column, int generation, int aliveCells); // Отрисовка состояния мира


int main()
{
    int** arrayOfTheUniverse = FP_ZERO;
    int row{ 0 }, column{ 0 };
    int generation{ 1 }, aliveCells{ 1 };
    arrayOfTheUniverse = readingFile(row, column);

    // readingTwoDimensionalArray(arrayOfTheUniverse, row, column);

    StateWorld(arrayOfTheUniverse, row, column, generation, aliveCells);








    deletingTwoDimensionalArray(arrayOfTheUniverse, row, column);
    std::cout << " *******************";
    return 0;
};


int** readingFile(int& row, int& column) {

    std::ifstream inputF{ "inputFile.txt" };
    if (inputF.is_open()) {
        inputF >> row;
        inputF >> column;
    };

    int** array{ new int* [row] };
    for (int i{ 0 }; i < row; i++) {
        array[i] = new int[column] {0};
    }

    /*for (int i{ 0 }; i < row; i++) {
        for (int j{ 0 }; j < column; j++) {
            inputF >> array[i][j];
        };
    };*/

    int coordinatesRow{ 0 }, coordinatesColumn{ 0 };
    while (true) {
        if (!(inputF >> coordinatesRow)) { break; };
        if (!(inputF >> coordinatesColumn)) { break; };
        array[static_cast<int>(coordinatesRow)][static_cast<int>(coordinatesColumn)] = 1;
    }
    

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

