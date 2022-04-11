#include <windows.h>

#include <queue>
#include <iostream>

#include <chrono>
#include <thread>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct coords {
    int i;
    int j;

    int n;
};

const int matrixRows = 7;
const int matrixColumns = 7;

int matrix[matrixRows][matrixColumns] = {
    { 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 0, 1, 1 },
    { 1, 0, 0, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 1, 1, 1 }
};

const coords matrixStartIn = { 0, 0, 0 };
const coords matrixEndsIn = { 6, 6, 0 };

void showMatrix() {

    for (int i = 0; i < matrixRows; i++) {

        for (int j = 0; j < matrixColumns; j++) {

            if (matrix[i][j] != 1 && matrix[i][j] != 0)
                std::cout << char(219) << char(219);
            else 
                std::cout << char(32) << char(32);
            
        }

        std::cout << std::endl;
    }
}

int getTop(coords c) {

    return matrix[c.i - 1][c.j];
}
int getRight(coords c) {

    return matrix[c.i][c.j + 1];
}
int getBottom(coords c) {

    return matrix[c.i + 1][c.j];
}
int getLeft(coords c) {

    return matrix[c.i][c.j - 1];
}

void showNumericMatrix() {

    for (int i = 0; i < matrixRows; i++) {

        for (int j = 0; j < matrixColumns; j++) {
            
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void drawMatrixPath() {

    for (int i = 0; i < matrixRows; i++) {

        for (int j = 0; j < matrixColumns; j++) {
            
            if (matrix[i][j] == 0)
                std::cout << (char)32 << (char)32;
            
            if (matrix[i][j] == 32) {
                
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << (char)219 << (char)219;
                SetConsoleTextAttribute(hConsole, 7);
            }

            if (matrix[i][j] != 0 && matrix[i][j] != 32) {

                std::cout << (char)219 << (char)219;
            }

        }

        std::cout << std::endl;
    }
}

int main() {

    // SHOW MATRIX WITH 0 AND 1
    showNumericMatrix();

    // CREATE QUEUE
    std::queue<coords> myQueue;

    // PUSH FIRST POSTIION IN QUEUE
    myQueue.push(matrixStartIn);

    while (!myQueue.empty()) {

        coords firstItem = myQueue.front();

        int n = firstItem.n - 1;

        matrix[firstItem.i][firstItem.j] = n;

        myQueue.pop();

        if (firstItem.i -1 >= 0 && getTop(firstItem) == 1) {

            // top -> (i-1, j)
            coords topCoords = { firstItem.i -1 , firstItem.j, n };
            myQueue.push(topCoords);
        }

        if (firstItem.j + 1 <= matrixColumns && getRight(firstItem) == 1) {

            // right -> (i, j+1)
            coords rightCoords = { firstItem.i, firstItem.j + 1, n };
            myQueue.push(rightCoords);
        }

        if (firstItem.i + 1 <= matrixRows && getBottom(firstItem) == 1) {

            // bottom -> (i+1, j)
            coords bottomCoords = { firstItem.i + 1, firstItem.j, n };
            myQueue.push(bottomCoords);
        }

        if (firstItem.j - 1 >= 0 && getLeft(firstItem) == 1) {

            // left -> (i, j -1)
            coords leftCoords = { firstItem.i, firstItem.j - 1, n };
            myQueue.push(leftCoords);
        }
    }
    
    std::cout << std::endl << std::endl;

    // SHOW MATRIX WITH DIFFERENT PATHS
    showNumericMatrix();

    std::cout << std::endl << std::endl;

    // start -> matrixStartsIn
    // end -> matrixEndsIn

    std::queue<coords> drawQueue;
    drawQueue.push(matrixEndsIn);    

    while (!drawQueue.empty()) {

        coords firstItem = drawQueue.front();

        int firstItemValue = matrix[firstItem.i][firstItem.j];
        matrix[firstItem.i][firstItem.j] = 32;

        drawQueue.pop();

        if (firstItem.i -1 >= 0 && getTop(firstItem) == firstItemValue + 1) {

            // top -> (i-1, j)
            coords topCoords = { firstItem.i -1 , firstItem.j, 0 };
            drawQueue.push(topCoords);
        }

        if (firstItem.j + 1 <= matrixColumns && getRight(firstItem) == firstItemValue + 1) {

            // right -> (i, j+1)
            coords rightCoords = { firstItem.i, firstItem.j + 1, 0 };
            drawQueue.push(rightCoords);
        }

        if (firstItem.i + 1 <= matrixRows && getBottom(firstItem) == firstItemValue + 1) {

            // bottom -> (i+1, j)
            coords bottomCoords = { firstItem.i + 1, firstItem.j, 0 };
            drawQueue.push(bottomCoords);
        }

        if (firstItem.j - 1 >= 0 && getLeft(firstItem) == firstItemValue + 1) {

            // left -> (i, j -1)
            coords leftCoords = { firstItem.i, firstItem.j - 1, 0 };
            drawQueue.push(leftCoords);
        }
    }
    std::cout << std::endl << std::endl;

    // SHOW MATRIX WITH DIFFERENT PATHS AND MINIMUM PATH
    showNumericMatrix();
    std::cout << std::endl << std::endl;

    // DRAW MATRIX AND MINIMUM PATH
    drawMatrixPath();

    system("pause");
    return 0;
}