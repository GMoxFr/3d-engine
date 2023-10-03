#ifndef __MY_VECTOR_2_HPP__
#define __MY_VECTOR_2_HPP__

#include "3dengine.hpp"

class myVector2 {
    private:

    public:
        // ATTRIBUTES
        double x;
        double y;

        // CONSTRUCTORS
        myVector2();
        myVector2(double x, double y);
        myVector2(const myVector2& v);
        myVector2(const std::vector<double>& v);
        ~myVector2();

        // OPERATORS
        myVector2& operator=(const myVector2& v);
        
        myVector2& operator+=(const myVector2& v);
        myVector2& operator-=(const myVector2& v);
        myVector2& operator*=(const double& d);
        myVector2& operator/=(const double& d);
        
        myVector2 operator+(const myVector2& v) const;
        myVector2 operator-(const myVector2& v) const;
        myVector2 operator*(const double& d) const;
        myVector2 operator/(const double& d) const;

        bool operator==(const myVector2& v) const;
        bool operator!=(const myVector2& v) const;
        bool operator<(const myVector2& v) const;
        bool operator>(const myVector2& v) const;
        bool operator<=(const myVector2& v) const;
        bool operator>=(const myVector2& v) const;

        friend myVector2 operator*(const double& d, const myVector2& v);

        myVector2 operator-() const;

        friend std::ostream& operator<<(std::ostream& os, const myVector2& v);

        // METHODS
        double dot(const myVector2& v) const;

        double magnitude() const;
        double squaredMagnitude() const;

        bool isZero() const;

        void normalize();
        myVector2 normalized() const;

        double distanceTo(const myVector2& v) const;
        double squaredDistanceTo(const myVector2& v) const;

        double angleBetween(const myVector2& v) const;
};

#endif
