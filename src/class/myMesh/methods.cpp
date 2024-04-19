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


    for (auto const& shape : shapes) {
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

    for (auto const& shape : shapes) {
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
    for (auto const& shape : shapes) {
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

    for (auto const& shape : shapes) {
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
    shapes.push_back(std::move(triangle));
}

void myMesh::computeBoundingBox(int depth) {
    printf("Computing bounding box at depth %d\n", depth);

    // Compute the bounding box of the mesh from all the shapes
    // The goals is to compute 5 parallelograms that will form the bounding box (ignoring the back face)
    
    if (computedBoundingBox) {
        return;
    }

    // Initialize the min and max values
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();

    // Find the min and max values
    for (auto const& shape : shapes) {
        auto triangle = dynamic_cast<myTriangle*>(shape.get());

        myVector3 A = triangle->A;
        myVector3 B = triangle->B;
        myVector3 C = triangle->C;

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

    if (shapes.size() > 100 && depth < 1) {
        // If the mesh has more than 1000 shapes, we will subdivide the bounding box into 8 smaller boxes following the octree principle
        // This will allow us to reduce the number of shapes we need to check for intersection

        // Compute the center of the bounding box
        myVector3 center = myVector3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);

        std::unique_ptr<myMesh> subdivideShapes[8];
        for (int i = 0; i < 8; i++) {
            subdivideShapes[i] = std::make_unique<myMesh>(this->getColor(), this->getDiffuse(), this->getFresnel(), this->getReflection(), this->getRefraction());
        }
        // If a shape as at least one vertex inside the bounding box, we will add it to the subdivideShapes vector (duplicating it if in multiple boxes)
        for (auto const& shape : shapes) {
            // Check if the shape is inside the bounding box (note that by default all shapes are myTriangle)
            auto triangle = dynamic_cast<myTriangle*>(shape.get());

            myVector3 A = triangle->A;
            myVector3 B = triangle->B;
            myVector3 C = triangle->C;

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[0]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[0]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[0]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[1]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[1]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[1]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[2]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[2]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[2]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[3]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[3]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[3]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[4]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[4]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[4]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[5]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[5]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[5]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[6]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[6]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[6]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));

            if (A.x >= minX && A.x <= maxX && A.y >= minY && A.y <= maxY && A.z >= minZ && A.z <= maxZ)
                subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (B.x >= minX && B.x <= maxX && B.y >= minY && B.y <= maxY && B.z >= minZ && B.z <= maxZ)
                subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
            if (C.x >= minX && C.x <= maxX && C.y >= minY && C.y <= maxY && C.z >= minZ && C.z <= maxZ)
                subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
        }

        for (int i = 0; i < 8; i++) {
            subdivideShapes[i]->computeBoundingBox(depth + 1);
        }

        // Add the subdivideShapes to the shapes, and remove everything else in it
        shapes.clear();
        for (int i = 0; i < 8; i++) {
            shapes.push_back(std::move(subdivideShapes[i]));
        }
    }

    computedBoundingBox = true;

    printf("Bounding box computed at depth %d\n", depth);
}