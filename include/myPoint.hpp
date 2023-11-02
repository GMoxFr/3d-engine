#pragma once

#include <iostream>

#include "myVector3.hpp"

class myPoint {
    public:
        // ATTRIBUTES
        int x;
        int y;

        // CONSTRUCTORS
        myPoint();
        myPoint(int x = 0, int y = 0);
        explicit myPoint(myVector3 v);

        // OPERATORS
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