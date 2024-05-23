#include "myMesh.hpp"

void myMesh::draw(myImage &I, std::vector<std::unique_ptr<myLight>> const &L)
{
    // Not implemented

    (void)I;
    (void)L;
}

bool myMesh::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color, double &u, double &v)
{
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const &shape : boundingBox)
    {
        if (shape->intersect(origin, direction))
        {
            bbHit = true;
            break;
        }
    }

    if (!bbHit)
    {
        return false;
    }

    // Check if the ray intersects the mesh
    myShape *closestShape = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;

    for (auto const &shape : shapes)
    {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON)
        {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr)
    {
        closestShape->intersect(origin, direction, intersection, normal, color, u, v);
        return true;
    }

    return false;
}

bool myMesh::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color)
{
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const &shape : boundingBox)
    {
        if (shape->intersect(origin, direction))
        {
            bbHit = true;
            break;
        }
    }

    if (!bbHit)
    {
        return false;
    }

    // Check if the ray intersects the mesh
    myShape *closestShape = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;

    for (auto const &shape : shapes)
    {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON)
        {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr)
    {
        closestShape->intersect(origin, direction, intersection, normal, color);
        return true;
    }

    return false;
}

bool myMesh::intersect(myVector3 const &origin, myVector3 const &direction)
{
    bool bbHit = false;

    // Check if the ray intersects the bounding box
    for (auto const &shape : boundingBox)
    {
        if (shape->intersect(origin, direction))
        {
            bbHit = true;
            break;
        }
    }

    if (!bbHit)
    {
        return false;
    }

    // Check if the ray intersects the mesh
    for (auto const &shape : shapes)
    {
        if (shape->intersect(origin, direction))
        {
            return true;
        }
    }

    return false;
}

double myMesh::intersectDistance(myVector3 const &origin, myVector3 const &direction)
{
    bool bbHit = false;
    double minDistance = std::numeric_limits<double>::max();
    double d = 0;

    // Check if the ray intersects the bounding box
    for (auto const &shape : boundingBox)
    {
        if (shape->intersect(origin, direction))
        {
            bbHit = true;
            break;
        }
    }

    if (!bbHit)
    {
        return -1;
    }

    myShape *closestShape = nullptr;

    for (auto const &shape : shapes)
    {
        d = shape->intersectDistance(origin, direction);
        if (d < minDistance && d > EPSILON)
        {
            minDistance = d;
            closestShape = shape.get();
        }
    }

    if (closestShape != nullptr)
    {
        return minDistance;
    }

    return -1;
}

void myMesh::addTriangle(std::unique_ptr<myTriangle> triangle)
{
    shapes.push_back(std::move(triangle));
}

bool isPointInsideBox(const myVector3 &point, const myVector3 &min, const myVector3 &max)
{
    return (point.x >= min.x && point.x <= max.x &&
            point.y >= min.y && point.y <= max.y &&
            point.z >= min.z && point.z <= max.z);
}

void myMesh::computeBoundingBox(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("\t");
    printf("Computing bounding box at depth %d\n", depth);

    // Compute the bounding box of the mesh from all the shapes
    // The goals is to compute 6 parallelograms that will form the bounding box

    // Initialize the min and max values
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();

    // Find the min and max values
    for (auto const &shape : shapes)
    {
        auto triangle = dynamic_cast<myTriangle *>(shape.get());

        myVector3 A = triangle->A;
        myVector3 B = triangle->B;
        myVector3 C = triangle->C;

        // if (A.x < minX)
        //     minX = A.x;
        // if (A.y < minY)
        //     minY = A.y;
        // if (A.z < minZ)
        //     minZ = A.z;

        // if (A.x > maxX)
        //     maxX = A.x;
        // if (A.y > maxY)
        //     maxY = A.y;
        // if (A.z > maxZ)
        //     maxZ = A.z;

        // if (B.x < minX)
        //     minX = B.x;
        // if (B.y < minY)
        //     minY = B.y;
        // if (B.z < minZ)
        //     minZ = B.z;

        // if (B.x > maxX)
        //     maxX = B.x;
        // if (B.y > maxY)
        //     maxY = B.y;
        // if (B.z > maxZ)
        //     maxZ = B.z;

        // if (C.x < minX)
        //     minX = C.x;
        // if (C.y < minY)
        //     minY = C.y;
        // if (C.z < minZ)
        //     minZ = C.z;

        // if (C.x > maxX)
        //     maxX = C.x;
        // if (C.y > maxY)
        //     maxY = C.y;
        // if (C.z > maxZ)
        //     maxZ = C.z;

        minX = std::min({minX, A.x, B.x, C.x});
        minY = std::min({minY, A.y, B.y, C.y});
        minZ = std::min({minZ, A.z, B.z, C.z});

        maxX = std::max({maxX, A.x, B.x, C.x});
        maxY = std::max({maxY, A.y, B.y, C.y});
        maxZ = std::max({maxZ, A.z, B.z, C.z});
    }

    if (!computedBoundingBox)
    {
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
        // Back face
        boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, maxZ), myVector3(maxX, minY, maxZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
    }

    if (shapes.size() > 1000 && depth < 8)
    {
        // If the mesh has more than 1000 shapes, we will subdivide the bounding box into 8 smaller boxes following the octree principle
        // This will allow us to reduce the number of shapes we need to check for intersection

        // Compute the center of the bounding box
        myVector3 center = myVector3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);

        // // Compute the center of each face
        // myVector3 centerFront = myVector3((minX + maxX) / 2, maxY, (minZ + maxZ) / 2);
        // myVector3 centerBack = myVector3((minX + maxX) / 2, minY, (minZ + maxZ) / 2);
        // myVector3 centerLeft = myVector3(minX, (minY + maxY) / 2, (minZ + maxZ) / 2);
        // myVector3 centerRight = myVector3(maxX, (minY + maxY) / 2, (minZ + maxZ) / 2);
        // myVector3 centerBottom = myVector3((minX + maxX) / 2, (minY + maxY) / 2, minZ);
        // myVector3 centerTop = myVector3((minX + maxX) / 2, (minY + maxY) / 2, maxZ);

        // // Compute the center of each edge
        // myVector3 centerFrontLeft = myVector3(minX, maxY, (minZ + maxZ) / 2);
        // myVector3 centerFrontRight = myVector3(maxX, maxY, (minZ + maxZ) / 2);
        // myVector3 centerFrontBottom = myVector3((minX + maxX) / 2, maxY, minZ);
        // myVector3 centerFrontTop = myVector3((minX + maxX) / 2, maxY, maxZ);
        // myVector3 centerBackLeft = myVector3(minX, minY, (minZ + maxZ) / 2);
        // myVector3 centerBackRight = myVector3(maxX, minY, (minZ + maxZ) / 2);
        // myVector3 centerBackBottom = myVector3((minX + maxX) / 2, minY, minZ);
        // myVector3 centerBackTop = myVector3((minX + maxX) / 2, minY, maxZ);
        // myVector3 centerLeftBottom = myVector3(minX, (minY + maxY) / 2, minZ);
        // myVector3 centerLeftTop = myVector3(minX, (minY + maxY) / 2, maxZ);
        // myVector3 centerRightBottom = myVector3(maxX, (minY + maxY) / 2, minZ);
        // myVector3 centerRightTop = myVector3(maxX, (minY + maxY) / 2, maxZ);

        std::unique_ptr<myMesh> subdivideShapes[8];
        for (int i = 0; i < 8; i++)
        {
            subdivideShapes[i] = std::make_unique<myMesh>(this->getColor(), this->getDiffuse(), this->getFresnel(), this->getReflection(), this->getRefraction());
            subdivideShapes[i]->computedBoundingBox = true;
        }

        // //// Compute the 8 smaller bounding boxes
        // // First box (front bottom left)
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), centerFrontBottom, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), centerLeftBottom, centerLeft, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), centerFrontBottom, centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFrontLeft, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBottom, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[0]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerLeft, centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Second box (front bottom right)
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontBottom, myVector3(maxX, minY, minZ), centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontBottom, myVector3(maxX, minY, minZ), centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(centerRightBottom, myVector3(maxX, minY, minZ), centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFrontRight, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBottom, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[1]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerRight, centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Third box (front top left)
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontTop, centerFront, myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontTop, centerTop, myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(centerLeftTop, centerLeft, myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFrontLeft, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFront, centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[2]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerTop, centerLeft, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Fourth box (front top right)
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontTop, myVector3(maxX, minY, maxZ), centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(centerFrontTop, myVector3(maxX, minY, maxZ), centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(centerRightTop, myVector3(maxX, minY, maxZ), centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFrontRight, centerFront, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerFront, centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[3]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerTop, centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Fifth box (back bottom left)
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackBottom, centerBack, myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackBottom, centerBottom, myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(centerLeftBottom, centerLeft, myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBackLeft, centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBack, centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[4]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBottom, centerLeft, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Sixth box (back bottom right)
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackBottom, myVector3(maxX, maxY, minZ), centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackBottom, myVector3(maxX, maxY, minZ), centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(centerRightBottom, myVector3(maxX, maxY, minZ), centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBackRight, centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBack, centerBottom, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[5]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBottom, centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Seventh box (back top left)
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackTop, centerBack, myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackTop, centerTop, myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(centerLeftTop, centerLeft, myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBackLeft, centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBack, centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[6]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerTop, centerLeft, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // // Eighth box (back top right)
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackTop, myVector3(maxX, maxY, maxZ), centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(centerBackTop, myVector3(maxX, maxY, maxZ), centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(centerRightTop, myVector3(maxX, maxY, maxZ), centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBackRight, centerBack, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerBack, centerTop, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        // subdivideShapes[7]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerTop, centerRight, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));

        std::array<std::pair<myVector3, myVector3>, 8> boxBounds = {
            std::make_pair(myVector3(minX, minY, minZ), myVector3(center.x, center.y, center.z)), // Front bottom left
            std::make_pair(myVector3(center.x, minY, minZ), myVector3(maxX, center.y, center.z)), // Front bottom right
            std::make_pair(myVector3(minX, center.y, minZ), myVector3(center.x, maxY, center.z)), // Front top left
            std::make_pair(myVector3(center.x, center.y, minZ), myVector3(maxX, maxY, center.z)), // Front top right
            std::make_pair(myVector3(minX, minY, center.z), myVector3(center.x, center.y, maxZ)), // Back bottom left
            std::make_pair(myVector3(center.x, minY, center.z), myVector3(maxX, center.y, maxZ)), // Back bottom right
            std::make_pair(myVector3(minX, center.y, center.z), myVector3(center.x, maxY, maxZ)), // Back top left
            std::make_pair(myVector3(center.x, center.y, center.z), myVector3(maxX, maxY, maxZ))  // Back top right
        };

        for (int i = 0; i < 8; i++)
        {
            const auto &[minCorner, maxCorner] = boxBounds[i];
            myVector3 centerX = myVector3(maxCorner.x, minCorner.y, minCorner.z);
            myVector3 centerY = myVector3(minCorner.x, maxCorner.y, minCorner.z);
            myVector3 centerZ = myVector3(minCorner.x, minCorner.y, maxCorner.z);

            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerY, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerZ, centerY, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerZ, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerY, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerZ, centerY, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
            subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerZ, myColor::WHITE, 0.0, 0.0, 0.0, 0.0));
        }

        // If a shape as at least one vertex inside the bounding box, we will add it to the subdivideShapes vector (duplicating it if in multiple boxes)
        for (auto const &shape : shapes)
        {
            // Check if the shape is inside the bounding box (note that by default all shapes are myTriangle)
            auto triangle = dynamic_cast<myTriangle *>(shape.get());

            myVector3 A = triangle->A;
            myVector3 B = triangle->B;
            myVector3 C = triangle->C;

            // If at least one vertex is inside the bounding box, we will add the shape to the subdivideShapes vector
            for (int i = 0; i < 8; i++)
            {
                if (isPointInsideBox(A, boxBounds[i].first, boxBounds[i].second) ||
                    isPointInsideBox(B, boxBounds[i].first, boxBounds[i].second) ||
                    isPointInsideBox(C, boxBounds[i].first, boxBounds[i].second))
                {
                    subdivideShapes[i]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
                }
            }
        }

        for (int i = 0; i < 8; i++)
            subdivideShapes[i]->computeBoundingBox(depth + 1);

        // Add the subdivideShapes to the shapes, and remove everything else in it
        shapes.clear();
        for (int i = 0; i < 8; i++)
            shapes.push_back(std::move(subdivideShapes[i]));
    }

    computedBoundingBox = true;

    for (int i = 0; i < depth; i++)
        printf("\t");
    printf("Bounding box computed at depth %d\n", depth);
}

//     subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(A, B, C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));