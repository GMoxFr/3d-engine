#include "myMesh.hpp"

void myMesh::draw(myImage& I, std::vector<std::unique_ptr<myLight>> const& L) {
    // Not implemented

    (void)I;
    (void)L;
}

bool myMesh::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) {
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const& shape : boundingBox) {
        if (shape->intersect(origin, direction)) {
            bbHit = true;
            break;
        }
    }

    if (!bbHit) {
        return false;
    }

    // Check if the ray intersects the mesh
    myShape* closestShape = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;


    for (auto const& shape : triangles) {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON) {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr) {
        closestShape->intersect(origin, direction, intersection, normal, color, u, v);
        return true;
    }

    return false;
}

bool myMesh::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color) {
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const& shape : boundingBox) {
        if (shape->intersect(origin, direction)) {
            bbHit = true;
            break;
        }
    }

    if (!bbHit) {
        return false;
    }

    // Check if the ray intersects the mesh
    myShape* closestShape = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;

    for (auto const& shape : triangles) {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON) {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr) {
        closestShape->intersect(origin, direction, intersection, normal, color);
        return true;
    }

    return false;
}

bool myMesh::intersect(myVector3 const& origin, myVector3 const& direction) {
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const& shape : boundingBox) {
        if (shape->intersect(origin, direction)) {
            bbHit = true;
            break;
        }
    }

    if (!bbHit) {
        return false;
    }

    // Check if the ray intersects the mesh
    for (auto const& shape : triangles) {
        if (shape->intersect(origin, direction)) {
            return true;
        }
    }

    return false;
}

double myMesh::intersectDistance(myVector3 const& origin, myVector3 const& direction) {
    bool bbHit = false;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;

    // Check if the ray intersects the bounding box
    for (auto const& shape : boundingBox) {
        if (shape->intersect(origin, direction)) {
            bbHit = true;
            break;
        }
    }

    if (!bbHit) {
        return -1;
    }

    myShape* closestShape = nullptr;

    for (auto const& shape : triangles) {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON) {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr) {
        return minDistance;
    }

    return -1;
}

void myMesh::addTriangle(std::unique_ptr<myTriangle> triangle) {
    triangles.push_back(std::move(triangle));
}

void myMesh::computeBoundingBox() {
    // Compute the bounding box of the mesh from all the shapes
    // The goals is to compute 5 parallelograms that will form the bounding box (ignoring the back face)
    
    // Reset the bounding box to an empty vector
    boundingBox.clear();

    // Initialize the min and max values
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();

    // Find the min and max values
    for (auto const& shape : triangles) {
        myVector3 A = shape->A;
        myVector3 B = shape->B;
        myVector3 C = shape->C;

        if (A.x < minX) minX = A.x;
        if (A.y < minY) minY = A.y;
        if (A.z < minZ) minZ = A.z;

        if (A.x > maxX) maxX = A.x;
        if (A.y > maxY) maxY = A.y;
        if (A.z > maxZ) maxZ = A.z;

        if (B.x < minX) minX = B.x;
        if (B.y < minY) minY = B.y;
        if (B.z < minZ) minZ = B.z;

        if (B.x > maxX) maxX = B.x;
        if (B.y > maxY) maxY = B.y;
        if (B.z > maxZ) maxZ = B.z;

        if (C.x < minX) minX = C.x;
        if (C.y < minY) minY = C.y;
        if (C.z < minZ) minZ = C.z;

        if (C.x > maxX) maxX = C.x;
        if (C.y > maxY) maxY = C.y;
        if (C.z > maxZ) maxZ = C.z;
    }

    // Front face
    boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
    // Top face
    boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, maxY, minZ), myVector3(maxX, maxY, minZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
    // Right face
    boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(maxX, minY, minZ), myVector3(maxX, maxY, minZ), myVector3(maxX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
    // Left face
    boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(minX, maxY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
    // Bottom face
    boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
}