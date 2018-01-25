#include "Utils.h"

bool** Utils::create2DBoolArray(unsigned width, unsigned height, bool value) {

    // Initialise 2D array.
    bool** array2D = 0;
    array2D = new bool*[width];

    for(int w = 0; w < width; w++) {

        // For every width element, insert another array for heights.
        array2D[w] = new bool[height];

        for(int h = 0; h < height; h++) {

            // Fill 2D array with given value.
            array2D[w][h] = value;
        }
    }

    return array2D;
}

void delete2DBoolArray(unsigned width, int** &array2D) {

    for(int w = 0; w < width; w++) {
        delete [] array2D[w];
    }

    delete [] array2D;
    array2D = 0;
}
