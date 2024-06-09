#include "myMesh.hpp"

void myMesh::draw(myImage &I, std::vector<std::unique_ptr<myLight>> const &L)
{
	// Not implemented

	(void)I;
	(void)L;
}

bool myMesh::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color, double &u, double &v)
{
	bool bbHit = true;

	// Check if the ray intersects the bounding box
	if (computedBoundingBox)
	{
		bbHit = false;
		for (auto const &shape : boundingBox)
		{
			if (shape->intersect(origin, direction))
			{
				bbHit = true;
				break;
			}
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
		// color *= boundingBox[0]->getColor();
		return true;
	}

	return false;
}

bool myMesh::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color)
{
	bool bbHit = true;

	// Check if the ray intersects the bounding box
	if (computedBoundingBox)
	{
		bbHit = false;
		// Check if the ray intersects the bounding box
		for (auto const &shape : boundingBox)
		{
			if (shape->intersect(origin, direction))
			{
				bbHit = true;
				break;
			}
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
	bool bbHit = true;

	// Check if the ray intersects the bounding box
	if (computedBoundingBox)
	{
		bbHit = false;
		for (auto const &shape : boundingBox)
		{
			if (shape->intersect(origin, direction))
			{
				bbHit = true;
				break;
			}
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
	// Check if the mesh as a bounding box
	bool bbHit = true;

	// If there is a bounding box, check if the ray intersects it
	if (computedBoundingBox)
	{
		bbHit = false;
		// Check if the ray intersects the bounding box
		for (auto const &shape : boundingBox)
		{
			if (shape->intersect(origin, direction))
			{
				bbHit = true;
				break;
			}
		}
	}

	// If the ray does not intersect the bounding box (if there is no bounding box, it will always be true)
	if (!bbHit)
	{
		return -1;
	}

	double minDistance = std::numeric_limits<double>::max();
	double d = 0;
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

// bool isPointInsideBox(const myVector3 &point, const myVector3 &min, const myVector3 &max)
// {
// 	return (point.x >= min.x - EPSILON && point.x <= max.x + EPSILON &&
// 			point.y >= min.y - EPSILON && point.y <= max.y + EPSILON &&
// 			point.z >= min.z - EPSILON && point.z <= max.z + EPSILON);
// }

// bool isPointInTriangle(const myVector3 &p, const myVector3 &a, const myVector3 &b, const myVector3 &c)
// {
// 	myVector3 v0 = c - a;
// 	myVector3 v1 = b - a;
// 	myVector3 v2 = p - a;

// 	double dot00 = v0.dot(v0);
// 	double dot01 = v0.dot(v1);
// 	double dot02 = v0.dot(v2);
// 	double dot11 = v1.dot(v1);
// 	double dot12 = v1.dot(v2);

// 	double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
// 	double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
// 	double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

// 	return (u >= 0) && (v >= 0) && (u + v < 1);
// }

// bool segmentPlaneCollision(const myVector3 &p0, const myVector3 &p1, const myVector3 &p2, const myVector3 &s0, const myVector3 &s1)
// {
// 	// Calculate the plane normal
// 	myVector3 u = p1 - p0;
// 	myVector3 v = p2 - p0;
// 	myVector3 n = u.cross(v);

// 	// Check if the segment is parallel to the plane
// 	myVector3 dir = s1 - s0;
// 	double denom = n.dot(dir);
// 	if (std::abs(denom) < 1e-6)
// 	{
// 		// Segment is parallel to the plane
// 		return false;
// 	}

// 	// Calculate the parameter t for the intersection point
// 	double t = n.dot(p0 - s0) / denom;

// 	// Check if the intersection point lies within the segment
// 	if (t < 0.0 || t > 1.0)
// 	{
// 		return false;
// 	}

// 	// Calculate the intersection point
// 	myVector3 intersection = s0 + dir * t;

// 	return isPointInTriangle(intersection, p0, p1, p2);
// }

// bool isTriangleInsideBox(const myTriangle &triangle, const myVector3 &min, const myVector3 &max)
// {
// 	if (isPointInsideBox(triangle.A, min, max) ||
// 		isPointInsideBox(triangle.B, min, max) ||
// 		isPointInsideBox(triangle.C, min, max))
// 	{
// 		return true;
// 	}

// 	// For each edge of the box (12 edges), we will check if the triangle intersects it
// 	//// First edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, min, myVector3(min.x, max.y, min.z)))
// 		return true;
// 	//// Second edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, min, myVector3(max.x, min.y, min.z)))
// 		return true;
// 	//// Third edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, min, myVector3(min.x, min.y, max.z)))
// 		return true;
// 	//// Fourth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(max.x, max.y, min.z), myVector3(max.x, min.y, min.z)))
// 		return true;
// 	//// Fifth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(max.x, max.y, min.z), myVector3(min.x, max.y, min.z)))
// 		return true;
// 	//// Sixth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(max.x, max.y, min.z), myVector3(max.x, max.y, max.z)))
// 		return true;
// 	//// Seventh edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(min.x, max.y, min.z), myVector3(min.x, max.y, max.z)))
// 		return true;
// 	//// Eighth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(min.x, max.y, min.z), myVector3(min.x, min.y, min.z)))
// 		return true;
// 	//// Ninth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(min.x, max.y, max.z), myVector3(min.x, min.y, max.z)))
// 		return true;
// 	//// Tenth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(min.x, max.y, max.z), myVector3(max.x, max.y, max.z)))
// 		return true;
// 	//// Eleventh edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(max.x, max.y, max.z), myVector3(max.x, min.y, max.z)))
// 		return true;
// 	//// Twelfth edge
// 	if (segmentPlaneCollision(triangle.A, triangle.B, triangle.C, myVector3(max.x, max.y, max.z), myVector3(max.x, max.y, min.z)))
// 		return true;

// 	return false;
// }

// const double epsilon = 1e-6;

// bool tR(const myVector3 &point, const myVector3 &center) { return (point.x - center.x) > epsilon; }
// bool tL(const myVector3 &point, const myVector3 &center) { return (point.x - center.x) < -epsilon; }
// bool tU(const myVector3 &point, const myVector3 &center) { return (point.y - center.y) > epsilon; }
// bool tD(const myVector3 &point, const myVector3 &center) { return (point.y - center.y) < -epsilon; }
// bool tF(const myVector3 &point, const myVector3 &center) { return (point.z - center.z) > epsilon; }
// bool tB(const myVector3 &point, const myVector3 &center) { return (point.z - center.z) < -epsilon; }

// void myMesh::computeBoundingBox(int depth, bool octree)
// {
// 	// Compute the bounding box of the mesh from all the shapes
// 	// The goal is to compute 6 parallelograms that will form the bounding box

// 	// Initialize the min and max values
// 	double minX = std::numeric_limits<double>::max();
// 	double minY = std::numeric_limits<double>::max();
// 	double minZ = std::numeric_limits<double>::max();

// 	double maxX = std::numeric_limits<double>::min();
// 	double maxY = std::numeric_limits<double>::min();
// 	double maxZ = std::numeric_limits<double>::min();

// 	if (!computedBoundingBox)
// 	{
// 		for (auto const &shape : shapes)
// 		{
// 			auto triangle = dynamic_cast<myTriangle *>(shape.get());

// 			myVector3 A = triangle->A;
// 			myVector3 B = triangle->B;
// 			myVector3 C = triangle->C;

// 			minX = std::min({minX, A.x, B.x, C.x});
// 			minY = std::min({minY, A.y, B.y, C.y});
// 			minZ = std::min({minZ, A.z, B.z, C.z});

// 			maxX = std::max({maxX, A.x, B.x, C.x});
// 			maxY = std::max({maxY, A.y, B.y, C.y});
// 			maxZ = std::max({maxZ, A.z, B.z, C.z});
// 		}

// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Front face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, maxY, minZ), myVector3(maxX, maxY, minZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Top face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(maxX, minY, minZ), myVector3(maxX, maxY, minZ), myVector3(maxX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Right face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(minX, maxY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Left face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Bottom face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, maxZ), myVector3(maxX, minY, maxZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Back face

// 		computedBoundingBox = true;
// 	}
// 	else
// 	{
// 		minX = boundingBox[0]->A.x;
// 		minY = boundingBox[0]->A.y;
// 		minZ = boundingBox[0]->A.z;

// 		maxX = boundingBox[0]->B.x;
// 		maxY = boundingBox[0]->C.y;
// 		maxZ = boundingBox[5]->C.z;
// 	}

// 	if (shapes.size() > 750 && depth < 25 && octree)
// 	{
// 		// Calcul du centre de la bounding box
// 		myVector3 center = myVector3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);

// 		// Création des sous-meshes pour les 8 sous-régions
// 		std::unique_ptr<myMesh> subdivideShapes[8];
// 		for (int i = 0; i < 8; i++)
// 		{
// 			subdivideShapes[i] = std::make_unique<myMesh>(this->getColor(), this->getDiffuse(), this->getFresnel(), this->getReflection(), this->getRefraction());
// 			subdivideShapes[i]->computedBoundingBox = true;
// 		}

// 		std::array<std::pair<myVector3, myVector3>, 8> boxBounds = {
// 			std::make_pair(myVector3(minX, minY, minZ), myVector3(center.x, center.y, center.z)), // Left Down Front
// 			std::make_pair(myVector3(minX, minY, center.z), myVector3(center.x, center.y, maxZ)), // Left Down Back
// 			std::make_pair(myVector3(minX, center.y, minZ), myVector3(center.x, maxY, center.z)), // Left Up Front
// 			std::make_pair(myVector3(minX, center.y, center.z), myVector3(center.x, maxY, maxZ)), // Left Up Back
// 			std::make_pair(myVector3(center.x, minY, minZ), myVector3(maxX, center.y, center.z)), // Right Down Front
// 			std::make_pair(myVector3(center.x, minY, center.z), myVector3(maxX, center.y, maxZ)), // Right Down Back
// 			std::make_pair(myVector3(center.x, center.y, minZ), myVector3(maxX, maxY, center.z)), // Right Up Front
// 			std::make_pair(myVector3(center.x, center.y, center.z), myVector3(maxX, maxY, maxZ))  // Right Up Back
// 		};

// 		for (int i = 0; i < 8; i++)
// 		{
// 			const auto &[minCorner, maxCorner] = boxBounds[i];
// 			myVector3 centerX = myVector3(maxCorner.x, minCorner.y, minCorner.z);
// 			myVector3 centerY = myVector3(minCorner.x, maxCorner.y, minCorner.z);
// 			myVector3 centerZ = myVector3(minCorner.x, minCorner.y, maxCorner.z);

// 			myColor randColor = myColor::getRandColor();

// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));
// 		}

// 		for (auto const &shape : shapes)
// 		{
// 			auto triangle = dynamic_cast<myTriangle *>(shape.get());
// 			myVector3 A = triangle->A;
// 			myVector3 B = triangle->B;
// 			myVector3 C = triangle->C;

// 			// Conditions booléennes pour chaque sous-espace
// 			bool _Left = tL(A, center) && tL(B, center) && tL(C, center);
// 			bool _Right = tR(A, center) && tR(B, center) && tR(C, center);
// 			bool _Up = tU(A, center) && tU(B, center) && tU(C, center);
// 			bool _Down = tD(A, center) && tD(B, center) && tD(C, center);
// 			bool _Front = tF(A, center) && tF(B, center) && tF(C, center);
// 			bool _Back = tB(A, center) && tB(B, center) && tB(C, center);

// 			bool putSomeWhere = false;

// 			// Ajout du triangle aux sous-meshes appropriés en fonction de leur position
// 			if (_Left && _Down && _Front)
// 			{
// 				subdivideShapes[0]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Left && _Down && _Back)
// 			{
// 				subdivideShapes[1]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Left && _Up && _Front)
// 			{
// 				subdivideShapes[2]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Left && _Up && _Back)
// 			{
// 				subdivideShapes[3]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Right && _Down && _Front)
// 			{
// 				subdivideShapes[4]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Right && _Down && _Back)
// 			{
// 				subdivideShapes[5]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Right && _Up && _Front)
// 			{
// 				subdivideShapes[6]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}
// 			if (_Right && _Up && _Back)
// 			{
// 				subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 				putSomeWhere = true;
// 			}

// 			if (!putSomeWhere)
// 			{
// 				std::cout << "Triangle not put anywhere" << std::endl;
// 				std::cout << "Left: " << _Left << " Right: " << _Right << " Up: " << _Up << " Down: " << _Down << " Front: " << _Front << " Back: " << _Back << std::endl;
// 			}
// 		}

// 		// Calcul récursif des bounding boxes pour chaque sous-mesh
// 		for (int i = 0; i < 8; i++)
// 		{
// 			subdivideShapes[i]->computeBoundingBox(depth + 1, octree);
// 		}

// 		// Réinitialisation et stockage des nouvelles subdivisions
// 		shapes.clear();
// 		for (int i = 0; i < 8; i++)
// 		{
// 			shapes.push_back(std::move(subdivideShapes[i]));
// 		}
// 	}
// }

// void myMesh::computeBoundingBox(int depth, bool octree)
// {
// 	// Compute the bounding box of the mesh from all the shapes
// 	// Initialize the min and max values
// 	double minX = std::numeric_limits<double>::max();
// 	double minY = std::numeric_limits<double>::max();
// 	double minZ = std::numeric_limits<double>::max();
// 	double maxX = std::numeric_limits<double>::min();
// 	double maxY = std::numeric_limits<double>::min();
// 	double maxZ = std::numeric_limits<double>::min();

// 	if (!computedBoundingBox)
// 	{
// 		for (auto const &shape : shapes)
// 		{
// 			auto triangle = dynamic_cast<myTriangle *>(shape.get());
// 			if (!triangle)
// 				continue; // Safety check for casting

// 			myVector3 A = triangle->A;
// 			myVector3 B = triangle->B;
// 			myVector3 C = triangle->C;

// 			minX = std::min({minX, A.x, B.x, C.x});
// 			minY = std::min({minY, A.y, B.y, C.y});
// 			minZ = std::min({minZ, A.z, B.z, C.z});
// 			maxX = std::max({maxX, A.x, B.x, C.x});
// 			maxY = std::max({maxY, A.y, B.y, C.y});
// 			maxZ = std::max({maxZ, A.z, B.z, C.z});
// 		}

// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Front face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, maxY, minZ), myVector3(maxX, maxY, minZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Top face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(maxX, minY, minZ), myVector3(maxX, maxY, minZ), myVector3(maxX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Right face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(minX, maxY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Left face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Bottom face
// 		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, maxZ), myVector3(maxX, minY, maxZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Back face

// 		computedBoundingBox = true;
// 	}
// 	else
// 	{
// 		minX = boundingBox[0]->A.x;
// 		minY = boundingBox[0]->A.y;
// 		minZ = boundingBox[0]->A.z;
// 		maxX = boundingBox[0]->B.x;
// 		maxY = boundingBox[0]->C.y;
// 		maxZ = boundingBox[5]->C.z;
// 	}

// 	if (shapes.size() > 750 && depth < 25 && octree)
// 	{
// 		myVector3 center = myVector3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
// 		std::unique_ptr<myMesh> subdivideShapes[8]; // Array for 8 sub-meshes

// 		// Define boundaries for each sub-mesh based on center calculations
// 		std::array<std::pair<myVector3, myVector3>, 8> boxBounds = {
// 			std::make_pair(myVector3(minX, minY, minZ), myVector3(center.x, center.y, center.z)), // Left Down Front
// 			std::make_pair(myVector3(minX, minY, center.z), myVector3(center.x, center.y, maxZ)), // Left Down Back
// 			std::make_pair(myVector3(minX, center.y, minZ), myVector3(center.x, maxY, center.z)), // Left Up Front
// 			std::make_pair(myVector3(minX, center.y, center.z), myVector3(center.x, maxY, maxZ)), // Left Up Back
// 			std::make_pair(myVector3(center.x, minY, minZ), myVector3(maxX, center.y, center.z)), // Right Down Front
// 			std::make_pair(myVector3(center.x, minY, center.z), myVector3(maxX, center.y, maxZ)), // Right Down Back
// 			std::make_pair(myVector3(center.x, center.y, minZ), myVector3(maxX, maxY, center.z)), // Right Up Front
// 			std::make_pair(myVector3(center.x, center.y, center.z), myVector3(maxX, maxY, maxZ))  // Right Up Back
// 		};

// 		for (auto &subMesh : subdivideShapes)
// 		{
// 			subMesh = std::make_unique<myMesh>(this->getColor(), this->getDiffuse(), this->getFresnel(), this->getReflection(), this->getRefraction());
// 			subMesh->computedBoundingBox = true;
// 		}

// 		// Create bounding boxes for each sub-mesh
// 		for (int i = 0; i < 8; i++)
// 		{
// 			const auto &[minCorner, maxCorner] = boxBounds[i];
// 			myVector3 centerX = myVector3(maxCorner.x, minCorner.y, minCorner.z);
// 			myVector3 centerY = myVector3(minCorner.x, maxCorner.y, minCorner.z);
// 			myVector3 centerZ = myVector3(minCorner.x, minCorner.y, maxCorner.z);

// 			myColor randColor = myColor::getRandColor();

// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
// 			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));
// 		}

// 		for (auto const &shape : shapes)
// 		{
// 			auto triangle = dynamic_cast<myTriangle *>(shape.get());
// 			if (!triangle)
// 				continue; // Safety check for casting

// 			myVector3 A = triangle->A;
// 			myVector3 B = triangle->B;
// 			myVector3 C = triangle->C;

// 			// Determine positions relative to center, using a small epsilon for boundary cases
// 			const double epsilon = 1e-6;
// 			bool left = A.x < center.x + epsilon || B.x < center.x + epsilon || C.x < center.x + epsilon;
// 			bool right = A.x > center.x - epsilon || B.x > center.x - epsilon || C.x > center.x - epsilon;
// 			bool down = A.y < center.y + epsilon || B.y < center.y + epsilon || C.y < center.y + epsilon;
// 			bool up = A.y > center.y - epsilon || B.y > center.y - epsilon || C.y > center.y - epsilon;
// 			bool front = A.z < center.z + epsilon || B.z < center.z + epsilon || C.z < center.z + epsilon;
// 			bool back = A.z > center.z - epsilon || B.z > center.z - epsilon || C.z > center.z - epsilon;

// 			// Add triangle to all matching sub-meshes
// 			if (left && down && front)
// 				subdivideShapes[0]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (left && down && back)
// 				subdivideShapes[1]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (left && up && front)
// 				subdivideShapes[2]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (left && up && back)
// 				subdivideShapes[3]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (right && down && front)
// 				subdivideShapes[4]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (right && down && back)
// 				subdivideShapes[5]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (right && up && front)
// 				subdivideShapes[6]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 			if (right && up && back)
// 				subdivideShapes[7]->addTriangle(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
// 		}

// 		// Recurse for each sub-mesh
// 		for (auto &subMesh : subdivideShapes)
// 		{
// 			subMesh->computeBoundingBox(depth + 1, octree);
// 		}

// 		// Clear and repopulate shapes list
// 		shapes.clear();
// 		for (auto &subMesh : subdivideShapes)
// 		{
// 			shapes.push_back(std::move(subMesh));
// 		}
// 	}
// }

bool intersectsSubregion(const myVector3 &A, const myVector3 &B, const myVector3 &C, const myVector3 &minCorner, const myVector3 &maxCorner)
{
	myVector3 triMin(std::min({A.x, B.x, C.x}), std::min({A.y, B.y, C.y}), std::min({A.z, B.z, C.z}));
	myVector3 triMax(std::max({A.x, B.x, C.x}), std::max({A.y, B.y, C.y}), std::max({A.z, B.z, C.z}));
	return (triMin.x <= maxCorner.x && triMax.x >= minCorner.x) &&
		   (triMin.y <= maxCorner.y && triMax.y >= minCorner.y) &&
		   (triMin.z <= maxCorner.z && triMax.z >= minCorner.z);
}

void myMesh::computeBoundingBox(int depth, bool octree)
{
	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double minZ = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::min();
	double maxY = std::numeric_limits<double>::min();
	double maxZ = std::numeric_limits<double>::min();

	if (!computedBoundingBox)
	{
		for (auto const &shape : shapes)
		{
			auto triangle = dynamic_cast<myTriangle *>(shape.get());
			if (!triangle)
				continue;

			myVector3 A = triangle->A;
			myVector3 B = triangle->B;
			myVector3 C = triangle->C;

			minX = std::min({minX, A.x, B.x, C.x});
			minY = std::min({minY, A.y, B.y, C.y});
			minZ = std::min({minZ, A.z, B.z, C.z});
			maxX = std::max({maxX, A.x, B.x, C.x});
			maxY = std::max({maxY, A.y, B.y, C.y});
			maxZ = std::max({maxZ, A.z, B.z, C.z});
		}

		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, maxY, minZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Front face
		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, maxY, minZ), myVector3(maxX, maxY, minZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Top face
		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(maxX, minY, minZ), myVector3(maxX, maxY, minZ), myVector3(maxX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Right face
		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(minX, maxY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Left face
		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, minZ), myVector3(maxX, minY, minZ), myVector3(minX, minY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Bottom face
		boundingBox.push_back(std::make_unique<myParallelogram>(myVector3(minX, minY, maxZ), myVector3(maxX, minY, maxZ), myVector3(minX, maxY, maxZ), myColor::WHITE, 0.0, 0.0, 0.0, 0.0)); // Back face

		computedBoundingBox = true;
	}
	else
	{
		minX = boundingBox[0]->A.x;
		minY = boundingBox[0]->A.y;
		minZ = boundingBox[0]->A.z;
		maxX = boundingBox[0]->B.x;
		maxY = boundingBox[0]->C.y;
		maxZ = boundingBox[5]->C.z;
	}

	if (shapes.size() > 750 && depth < 25 && octree)
	{
		myVector3 center((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
		std::unique_ptr<myMesh> subdivideShapes[8];

		std::array<std::pair<myVector3, myVector3>, 8> boxBounds = {
			std::make_pair(myVector3(minX, minY, minZ), myVector3(center.x, center.y, center.z)), // Left Down Front
			std::make_pair(myVector3(minX, minY, center.z), myVector3(center.x, center.y, maxZ)), // Left Down Back
			std::make_pair(myVector3(minX, center.y, minZ), myVector3(center.x, maxY, center.z)), // Left Up Front
			std::make_pair(myVector3(minX, center.y, center.z), myVector3(center.x, maxY, maxZ)), // Left Up Back
			std::make_pair(myVector3(center.x, minY, minZ), myVector3(maxX, center.y, center.z)), // Right Down Front
			std::make_pair(myVector3(center.x, minY, center.z), myVector3(maxX, center.y, maxZ)), // Right Down Back
			std::make_pair(myVector3(center.x, center.y, minZ), myVector3(maxX, maxY, center.z)), // Right Up Front
			std::make_pair(myVector3(center.x, center.y, center.z), myVector3(maxX, maxY, maxZ))  // Right Up Back
		};

		for (int i = 0; i < 8; i++)
		{
			subdivideShapes[i] = std::make_unique<myMesh>(this->getColor(), this->getDiffuse(), this->getFresnel(), this->getReflection(), this->getRefraction());

			// myVector3 bottomLeftFront = boxBounds[i].first;
			// myVector3 topRightBack = boxBounds[i].second;

			// myVector3 bottomRightFront = myVector3(topRightBack.x, bottomLeftFront.y, bottomLeftFront.z);
			// myVector3 topRightFront = myVector3(topRightBack.x, topRightBack.y, bottomLeftFront.z);
			// myVector3 topLeftFront = myVector3(bottomLeftFront.x, topRightBack.y, bottomLeftFront.z);
			// myVector3 bottomLeftBack = myVector3(bottomLeftFront.x, bottomLeftFront.y, topRightBack.z);
			// myVector3 bottomRightBack = myVector3(topRightBack.x, bottomLeftFront.y, topRightBack.z);
			// myVector3 topLeftBack = myVector3(bottomLeftFront.x, topRightBack.y, topRightBack.z);

			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(bottomLeftFront, bottomRightFront, topRightFront, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0)); // Front face
			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(bottomLeftFront, topLeftFront, topLeftBack, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0));		 // Left face
			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(bottomLeftFront, bottomLeftBack, bottomRightBack, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0)); // Bottom face
			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(topRightFront, topRightBack, bottomRightBack, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0));	 // Right face
			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(topLeftFront, topRightFront, topRightBack, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0));		 // Top face
			// subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(bottomLeftBack, bottomRightBack, topRightBack, myColor::getRandColor(), 0.0, 0.0, 0.0, 0.0));	 // Back face

			// subdivideShapes[i]->computedBoundingBox = true;

			const auto &[minCorner, maxCorner] = boxBounds[i];
			myVector3 centerX = myVector3(maxCorner.x, minCorner.y, minCorner.z);
			myVector3 centerY = myVector3(minCorner.x, maxCorner.y, minCorner.z);
			myVector3 centerZ = myVector3(minCorner.x, minCorner.y, maxCorner.z);

			myColor randColor = myColor::getRandColor();

			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(minCorner, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));
			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerZ, centerY, randColor, 0.0, 0.0, 0.0, 0.0));
			subdivideShapes[i]->boundingBox.push_back(std::make_unique<myParallelogram>(center, centerX, centerZ, randColor, 0.0, 0.0, 0.0, 0.0));

			subdivideShapes[i]->computedBoundingBox = true;

			for (auto &shape : shapes)
			{
				auto triangle = dynamic_cast<myTriangle *>(shape.get());
				if (!triangle)
					continue;

				if (intersectsSubregion(triangle->A, triangle->B, triangle->C, boxBounds[i].first, boxBounds[i].second))
				{
					subdivideShapes[i]->shapes.push_back(std::make_unique<myTriangle>(triangle->A, triangle->B, triangle->C, triangle->getColor(), triangle->getDiffuse(), triangle->getFresnel(), triangle->getReflection(), triangle->getRefraction()));
				}
			}
			if (!subdivideShapes[i]->shapes.empty())
			{
				subdivideShapes[i]->computeBoundingBox(depth + 1, octree);
				// 	shapes.push_back(std::move(subdivideShapes[i]));
			}
		}

		shapes.clear();
		for (int i = 0; i < 8; i++)
		{
			if (!subdivideShapes[i]->shapes.empty())
			{
				shapes.push_back(std::move(subdivideShapes[i]));
			}
		}
	}
}