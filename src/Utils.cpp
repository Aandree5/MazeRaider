#include "Utils.h"

/**
 * A class of static utility functions.
 *
 * @author Jesse Prescott.
 */

 /**
  * Creates a 2D integer array of given width, height and initial values.
  */
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

/**
 * Deletes a given 2D integer array to clear memory.
 */
void Utils::delete2DIntArray(unsigned width, int** &array2D) {

    // For every inner array.
    for(int w = 0; w < width; w++) {

        // Delete it.
        delete [] array2D[w];
    }

    // Delete parent array.
    delete [] array2D;

    // Set to 0.
    array2D = 0;
}
