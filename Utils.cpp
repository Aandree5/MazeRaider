#include "Utils.h"

int** Utils::create2DIntArray(unsigned width, unsigned height, int value) {

    // Initialise 2D array.
    int** array2D = 0;
    array2D = new int*[width];

    for(int w = 0; w < width; w++) {

        // For every width element, insert another array for heights.
        array2D[w] = new int[height];

        for(int h = 0; h < height; h++) {

            // Fill 2D array with given value.
            array2D[w][h] = value;
        }
    }

    return array2D;
}

void delete2DIntArray(unsigned width, int** &array2D) {

    for(int w = 0; w < width; w++) {
        delete [] array2D[w];
    }

    delete [] array2D;
    array2D = 0;
}
