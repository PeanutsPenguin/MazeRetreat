#include "Physics/boudingBox.h"

bool Collision::AABBtoAABB(const Box& a, const Box& b)
{
    if (a.MinPos.x <= b.MaxPos.x &&
        a.MaxPos.x >= b.MinPos.x &&
        a.MinPos.y <= b.MaxPos.y &&
        a.MaxPos.y >= b.MinPos.y &&
        a.MinPos.z <= b.MaxPos.z &&
        a.MaxPos.z >= b.MinPos.z )
        return true; 
    
    return false;
}

LibMath::Vec3 Collision::getVectorMin(std::vector<LibMath::Vec3> vector)
{
    if (vector.empty())
    {
        std::cout << "getVectorMin(empty)" << '\n';
    }

    LibMath::Vec3 result = vector[0];

    for (const LibMath::Vec3& vec : vector)
    {
        if (vec.x < result.x)
            result.x = vec.x;
        if (vec.y < result.y)
            result.y = vec.y;
        if (vec.z < result.z)
            result.z = vec.z;
    }

    return result;
}

LibMath::Vec3 Collision::getVectorMax(std::vector<LibMath::Vec3> vector)
{
    if (vector.empty())
    {
        std::cout << "getVectorMax(empty)" << '\n';
    }

    LibMath::Vec3 result = vector[0];

    for (const LibMath::Vec3& vec : vector)
    {
        if (vec.x > result.x)
            result.x = vec.x;
        if (vec.y > result.y)
            result.y = vec.y;
        if (vec.z > result.z)
            result.z = vec.z;
    }

    return result;
}
