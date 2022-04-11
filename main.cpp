#include <queue>
#include <iostream>

#include <chrono>
#include <thread>

struct coords {
    int i;
    int j;

    int n;
};

int matrix[7][7] = {
    { 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 0, 1, 1 },
    { 1, 0, 0, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 1, 1, 1 }
};

void showMatrix() {

    for (int i = 0; i < 7; i++) {

        for (int j = 0; j < 7; j++) {

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

int main() {

    std::queue<int> paths[1024];

    coords firstPos = { 0, 0, 0 };

    std::queue<coords> myQueue;

    myQueue.push(firstPos);

    while (!myQueue.empty()) {

        coords firstItem = myQueue.front();

        int n = firstItem.n - 1;

        matrix[firstItem.i][firstItem.j] = n;

        std::cout << firstItem.i << "," << firstItem.j << ":" << n << std::endl;

        myQueue.pop();

        if (firstItem.i -1 >= 0 && getTop(firstItem) == 1) {

            // top -> (i-1, j)
            coords topCoords = { firstItem.i -1 , firstItem.j, n };
            myQueue.push(topCoords);
        }

        if (firstItem.j + 1 <= 7 && getRight(firstItem) == 1) {

            // right -> (i, j+1)
            coords rightCoords = { firstItem.i, firstItem.j + 1, n };
            myQueue.push(rightCoords);
        }

        if (firstItem.i + 1 <= 7 && getBottom(firstItem) == 1) {

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

    for (int i = 0; i < 7; i++) {

        for (int j = 0; j < 7; j++) {
            
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }

    system("pause");
    return 0;
}