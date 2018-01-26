#ifndef UTILS_H
#define UTILS_H

class Utils
{
    public:
        static int** create2DIntArray(unsigned width, unsigned height, int value);
        void delete2DIntArray(unsigned width, int** &array2D);

    protected:

    private:
};

#endif // UTILS_H
