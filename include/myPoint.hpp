#ifndef __MY_POINT_HPP__
#define __MY_POINT_HPP__

#include "3dengine.hpp"

class myPoint {
    private:

    public:
        // ATTRIBUTES
        int x;
        int y;

        // CONSTRUCTORS
        myPoint();
        myPoint(int x, int y);
        myPoint(myVector2 v);
        myPoint(myVector3 v);
        ~myPoint();
};

#endif
