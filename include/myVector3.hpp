#ifndef __MY_VECTOR_3_HPP__
#define __MY_VECTOR_3_HPP__

#include "3dengine.hpp"

class myVector3 {
    private:

    public:
        // ATTRIBUTES
        double x;
        double y;
        double z;

        // CONSTRUCTORS
        myVector3();
        myVector3(double x, double y, double z);
        myVector3(const myVector3& v);
        myVector3(const std::vector<double>& v);
        ~myVector3();

        // OPERATORS
        myVector3& operator=(const myVector3& v);
        
        myVector3& operator+=(const myVector3& v);
        myVector3& operator-=(const myVector3& v);
        myVector3& operator*=(const double& d);
        myVector3& operator/=(const double& d);
        
        myVector3 operator+(const myVector3& v) const;
        myVector3 operator-(const myVector3& v) const;
        myVector3 operator*(const double& d) const;
        myVector3 operator/(const double& d) const;

        bool operator==(const myVector3& v) const;
        bool operator!=(const myVector3& v) const;
        bool operator<(const myVector3& v) const;
        bool operator>(const myVector3& v) const;
        bool operator<=(const myVector3& v) const;
        bool operator>=(const myVector3& v) const;

        friend myVector3 operator*(const double& d, const myVector3& v);

        myVector3 operator-() const;

        friend std::ostream& operator<<(std::ostream& os, const myVector3& v);

        // METHODS
        double dot(const myVector3& v) const;
        myVector3 cross(const myVector3& v) const;

        double magnitude() const;
        double squaredMagnitude() const;

        bool isZero() const;

        void normalize();
        myVector3 normalized() const;

        double distanceTo(const myVector3& v) const;
        double squaredDistanceTo(const myVector3& v) const;

        double angleBetween(const myVector3& v) const;


};

#endif