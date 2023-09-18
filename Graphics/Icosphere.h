#pragma once
#include "../main/LinaMath.h"
#include <vector>
#include <array>
namespace Lina{ namespace Graphics{ namespace Shapes{
    class Icosphere{
    public:
        Icosphere(float radius);
        std::vector<Point3D> getVertices() const;
        std::vector<unsigned int> getIndices() const;
        std::vector<std::array<float, 2> > getTexCoords() const {return mTextureCoordinates;};
        std::vector<float> getFullVertex() const {return mFullVertices;};
        void subdivide(unsigned int layers);
    private:
        float mRadius;
        std::vector<Point3D> mVertices;
        std::vector<unsigned int> mIndices;
        std::vector<std::array<float, 2> > mTextureCoordinates;
        std::vector<float> mFullVertices;
        int subdivisions;
        void addVertices(float v1, float v2, float v3);
        void addIndices();
        void computeMidPoint(Point3D& v1,
                             Point3D& v2, Point3D& newV);
        void computeMidPointUV(std::array<float, 2>& t0, std::array<float ,2>& t1,
                                std::array<float, 2>& newT);
        void addFullVertex(Point3D& position,
                std::array<float,2>& texture);
        void computeFullVertices();
        void fixSeam();
        std::vector<int> getWinded();
        void fixPoles();
    };
}}}
