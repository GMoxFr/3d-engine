#pragma once

#include <iostream>

#include "myVector3.hpp"

class myPoint {
    private:

    public:
        // ATTRIBUTES
        int x;
        int y;

        // CONSTRUCTORS
        myPoint();
        myPoint(int x = 0, int y = 0);
        myPoint(myVector3 v);
        myPoint(const myPoint& p);
        ~myPoint();

        // OPERATORS
        myPoint& operator=(const myPoint& p);

        myPoint& operator+=(const myPoint& p);
        myPoint& operator-=(const myPoint& p);

        myPoint operator+(const myPoint& p) const;
        myPoint operator-(const myPoint& p) const;

        bool operator==(const myPoint& p) const;
        bool operator!=(const myPoint& p) const;
        bool operator<(const myPoint& p) const;
        bool operator>(const myPoint& p) const;
        bool operator<=(const myPoint& p) const;
        bool operator>=(const myPoint& p) const;

        myPoint operator-() const;

        friend std::ostream& operator<<(std::ostream& os, const myPoint& p);

        // METHODS
        double distance(const myPoint& p) const;
};