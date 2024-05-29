#pragma once

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"
#include "myTriangle.hpp"
#include "myParallelogram.hpp"

class myMesh : public myShape
{
private:
    std::vector<std::unique_ptr<myShape>> shapes;
    std::vector<std::unique_ptr<myParallelogram>> boundingBox;
    bool computedBoundingBox = false;

public:
    myMesh(myColor const &clr, double diffuse, double fresnel, double reflection, double refraction);
    ~myMesh() override = default;

    void draw(myImage &I, std::vector<std::unique_ptr<myLight>> const &L) override;
    bool intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color, double &u, double &v) override;
    bool intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color) override;
    bool intersect(myVector3 const &origin, myVector3 const &direction) override;
    double intersectDistance(myVector3 const &origin, myVector3 const &direction) override;

    void addTriangle(std::unique_ptr<myTriangle> triangle);
    void computeBoundingBox(int depth = 0, bool octree = false);
};