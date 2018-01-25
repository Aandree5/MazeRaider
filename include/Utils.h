#ifndef UTILS_H
#define UTILS_H

class Utils
{
    public:
        static bool** create2DBoolArray(unsigned width, unsigned height, bool value);
        void delete2DBoolArray(unsigned width, int** &array2D);

    protected:

    private:
};

#endif // UTILS_H
