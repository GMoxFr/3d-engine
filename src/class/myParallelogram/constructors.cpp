#include "myParallelogram.hpp"

myParallelogram::myParallelogram(myVector3 A, myVector3 B, myVector3 C, myColor clr, double diffuse) : 
    myShape(clr, diffuse),
    A(A),
    B(B),
    C(C)
{};

myParallelogram::myParallelogram(myVector3 A, myVector3 B, myVector3 C, std::string texture, double diffuse) : 
    myShape(texture, diffuse),
    A(A),
    B(B),
    C(C)
{};

myParallelogram::~myParallelogram() {};