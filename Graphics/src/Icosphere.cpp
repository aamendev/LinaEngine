#include <iostream>
#include <map>
#include "../Icosphere.h"
#include <cmath>
namespace Lina{ namespace Graphics { namespace Shapes {
    Icosphere::Icosphere(float radius): mRadius(radius){
        const float PI = 3.1415926f;
        const float H_ANGLE = PI / 180 * 72;
        const float V_ANGLE = atanf(1.0f / 2);

        mVertices.resize(12);
        mTextureCoordinates.resize(12);
        int i1, i2;
        float z, xy;
        float hAngle1 = - PI / 2 - H_ANGLE/2;
        float hAngle2 = - PI / 2;
        mVertices[0].x = 0;
        mVertices[0].y = 0;
        mVertices[0].z = mRadius;
        mTextureCoordinates[0][0] = 0.5f + atan2f(mVertices[0].normalise().z, mVertices[0].normalise().x) / (2 * PI);
        mTextureCoordinates[0][1] = acosf(mVertices[0].normalise().y) / PI;
        for (int i = 1; i < 6; i++){
            i1 = i;
            i2 = (i+5);
            z = mRadius * sinf(V_ANGLE);
            xy = mRadius * cosf(V_ANGLE);

            mVertices[i1].x = xy * cosf(hAngle1);
            mVertices[i2].x = xy * cosf(hAngle2);
            mVertices[i1].y = xy * sinf(hAngle1);
            mVertices[i2].y = xy * sinf(hAngle2);
            mVertices[i1].z = z;
            mVertices[i2].z = -z;
            mTextureCoordinates[i1][0] = 0.5f + atan2f(mVertices[i1].normalise().z, mVertices[i1].normalise().x) / (2 * PI);
            mTextureCoordinates[i2][0] = 0.5f + atan2f(mVertices[i2].normalise().z, mVertices[i2].normalise().x) / (2 * PI);
            mTextureCoordinates[i1][1] = acosf(mVertices[i1].normalise().y) / PI;
            mTextureCoordinates[i2][1] = acosf(mVertices[i2].normalise().y) / PI;
            hAngle1 += H_ANGLE;
            hAngle2 += H_ANGLE;
        }
        i1 = 11;
        mVertices[i1].x = 0;
        mVertices[i1].y = 0;
        mVertices[i1].z = -mRadius;
        mTextureCoordinates[i1][0] = 0.5f + atan2f(mVertices[i1].normalise().z, mVertices[i1].normalise().x) / (2 * PI);
        mTextureCoordinates[i1][1] = acosf(mVertices[i1].normalise().y) / PI;
        mIndices.resize(20 * 3);
        mIndices = {
        0, 1, 2,
        0, 2 ,3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 1,
        1, 6, 2,
        2, 7, 3,
        3, 8, 4,
        4, 9, 5,
        5, 10, 1,
        6, 7, 2,
        7, 8, 3,
        8 ,9, 4,
        9, 10 ,5,
        10, 6, 1,
        10, 11, 6,
        6, 11, 7,
        7, 11, 8,
        8, 11, 9,
        9, 11, 10
        };
        fixSeam();
        fixPoles();
        computeFullVertices();
    }
    void Icosphere::fixSeam(){
        std::vector<int> windedIndices = getWinded();
        std::array<int, 12> duplicated;
        duplicated.fill(-1);
        int vertexIndex = mVertices.size() - 1;
        for (int i = 0; i < windedIndices.size(); i+=4){
            int ii = windedIndices[i];
            int ii1 = windedIndices[i + 1];
            int ii2 = windedIndices[i + 2];
            int ii3 = windedIndices[i + 3];
            Point3D A = mVertices[ii1];
            Point3D B = mVertices[ii2];
            Point3D C = mVertices[ii3];
            if (mTextureCoordinates[ii1][0] < 0.25f){
            if (duplicated[ii1] == -1)
            {
                mTextureCoordinates.push_back({mTextureCoordinates[ii1][0] + 1,
                    mTextureCoordinates[ii1][1]});
                mVertices.emplace_back(mVertices[ii1]);
                mIndices[ii * 3] = ++vertexIndex;
                duplicated[ii1] = vertexIndex;
            }else{
                mIndices[ii * 3] = duplicated[ii1];
            }
            }
            if (mTextureCoordinates[ii2][0] < 0.25f){
            if (duplicated[ii2] == -1)
            {
                mTextureCoordinates.push_back({mTextureCoordinates[ii2][0] + 1,
                    mTextureCoordinates[ii2][1]});
                mVertices.emplace_back(mVertices[ii2]);
                mIndices[ii * 3 + 1] = ++vertexIndex;
                duplicated[ii2] = vertexIndex;
            }else{
                mIndices[ii * 3 + 1] = duplicated[ii2];
            }
            }
            if (mTextureCoordinates[ii3][0] < 0.25f){
            if (duplicated[ii3] == -1)
            {
                mTextureCoordinates.push_back({mTextureCoordinates[ii3][0]+ 1,
                    mTextureCoordinates[ii3][1]});
                mVertices.emplace_back(mVertices[ii3]);
                mIndices[ii * 3 + 2] = ++vertexIndex;
                duplicated[ii3] = vertexIndex;
            }else{
                mIndices[ii * 3 + 2] = duplicated[ii3];
            }
            }
        }
    }
    std::vector<int> Icosphere::getWinded()
    {
        std::vector<int> windedIndices;
        for (int i = 0; i < mIndices.size(); i+= 3)
        {
            int ii1 = mIndices[i];
            int ii2 = mIndices[i + 1];
            int ii3 = mIndices[i + 2];
            Vector3D temp1(mTextureCoordinates[ii1][0], mTextureCoordinates[ii1][1], 0);
            Vector3D temp2(mTextureCoordinates[ii2][0], mTextureCoordinates[ii2][1], 0);
            Vector3D temp3(mTextureCoordinates[ii3][0], mTextureCoordinates[ii3][1], 0);
            Vector3D norm = (temp2 - temp1).cross(temp3 - temp1);
            if (norm.z < 0)
            {
                windedIndices.emplace_back(i / 3);
                windedIndices.emplace_back(ii1);
                windedIndices.emplace_back(ii2);
                windedIndices.emplace_back(ii3);
            }
        }
        return windedIndices;
    }
    void Icosphere::fixPoles()
    {
        float yMax = -99999.0f;
        float yMin = -yMax;
        int iMax = -1;
        int iMin = -1;
        for (int i = 0; i < mVertices.size(); i++)
        {

            iMax = i * (mVertices[i].y > yMax) + iMax * !(mVertices[i].y > yMax);
            yMax = mVertices[iMax].y;
            iMin = i * (mVertices[i].y < yMin) + iMin * !(mVertices[i].y < yMin);
            yMin = mVertices[iMin].y;
        }

        Point3D sPole = mVertices[iMin];
        Point3D nPole = mVertices[iMax];
        int currentIndex = mVertices.size() - 1;
        for (int i = 0; i < mIndices.size(); i +=3)
        {
            int ii1 = mIndices[i];
            int ii2 = mIndices[i + 1];
            int ii3 = mIndices[i + 2];
            if (ii1 == iMax || ii2 == iMax || ii3 == iMax)
            {
                std::array<float, 2>& u1 = mTextureCoordinates[ii1];
                std::array<float, 2>& u2 = mTextureCoordinates[ii2];
                std::array<float, 2>& u3 = mTextureCoordinates[ii3];
                float newU = (ii1 == iMax) * (u2[0] + u3[0]) / 2
                            + (ii2 == iMax) * (u1[0] + u3[0]) / 2
                            + (ii3 == iMax) * (u1[0] + u2[0]) / 2;
                float newV = (ii1 == iMax) * u1[1] + (ii2 == iMax) * u2[1]
                            + (ii3 == iMax) * u3[1];

                mTextureCoordinates.push_back({newU,newV});
                mVertices.emplace_back(nPole);
                int removeIndex = i * (ii1 == iMax) + (i + 1) * (ii2 == iMax)
                                        + (i + 2) * (ii3 == iMax);
                mIndices[removeIndex] = ++currentIndex;
            }
            else if (ii1 == iMin || ii2 == iMin || ii3 == iMin)
            {
                std::array<float, 2>& u1 = mTextureCoordinates[ii1];
                std::array<float, 2>& u2 = mTextureCoordinates[ii2];
                std::array<float, 2>& u3 = mTextureCoordinates[ii3];
                float newU = (ii1 == iMin) * (u2[0] + u3[0]) / 2
                            + (ii2 == iMin) * (u1[0] + u3[0]) / 2
                            + (ii3 == iMin) * (u1[0] + u2[0]) / 2;
                float newV = (ii1 == iMin) * u1[1] + (ii2 == iMin) * u2[1]
                            + (ii3 == iMin) * u3[1];
                mTextureCoordinates.push_back({newU, newV});
                mVertices.emplace_back(sPole);
                int removeIndex = i * (ii1 == iMin) + (i + 1) * (ii2 == iMin)
                                        + (i + 2) * (ii3 == iMin);
                mIndices[removeIndex] = ++currentIndex;
            }
        }
    }
    std::vector<unsigned int> Icosphere::getIndices() const{
        return mIndices;
    }
    std::vector<Point3D> Icosphere::getVertices() const{
        return mVertices;
    }
    void Icosphere::subdivide(unsigned int layers){
        if (layers == 0)
            return;
        std::vector<Point3D> tmpVerts;
        std::vector<unsigned int> tmpIndices;
        std::vector<std::array<float, 2> > tmpTexCoords;
        std::vector<Point3D> triangleVerts;
        std::vector<std::array<float,2> > triangleTex;
        std::vector<Point3D> midPoints;
        std::vector<std::array<float, 2> > midUV;
        int index;
        subdivide(layers - 1);
        tmpVerts = mVertices;
        tmpIndices = mIndices;
        tmpTexCoords = mTextureCoordinates;
        mVertices.clear();
        mIndices.clear();
        mTextureCoordinates.clear();
        mFullVertices.clear();
        index = 0;
        for (int currentIndex = 0; currentIndex < tmpIndices.size(); currentIndex +=3){
        triangleVerts.reserve(3);
        triangleTex.reserve(3);
        for (int i = 0; i < 3; i++){
            triangleVerts[i] = tmpVerts[tmpIndices[currentIndex + i]];
            triangleTex[i] = tmpTexCoords[tmpIndices[currentIndex + i]];
        }
        midPoints.reserve(3);
        midUV.reserve(3);
        computeMidPoint(triangleVerts[0], triangleVerts[1], midPoints[0]);
        computeMidPoint(triangleVerts[1], triangleVerts[2], midPoints[1]);
        computeMidPoint(triangleVerts[0], triangleVerts[2], midPoints[2]);

        computeMidPointUV(triangleTex[0], triangleTex[1], midUV[0]);
        computeMidPointUV(triangleTex[1], triangleTex[2], midUV[1]);
        computeMidPointUV(triangleTex[0], triangleTex[2], midUV[2]);

        mVertices.emplace_back(triangleVerts[0]);
        mTextureCoordinates.push_back(triangleTex[0]);

        mVertices.emplace_back(midPoints[0]);
        mTextureCoordinates.push_back(midUV[0]);

        mVertices.emplace_back(midPoints[2]);
        mTextureCoordinates.push_back(midUV[2]);

        mVertices.emplace_back(midPoints[0]);
        mTextureCoordinates.push_back(midUV[0]);

        mVertices.emplace_back(triangleVerts[1]);
        mTextureCoordinates.push_back(triangleTex[1]);

        mVertices.emplace_back(midPoints[1]);
        mTextureCoordinates.push_back(midUV[1]);

        mVertices.emplace_back(midPoints[0]);
        mTextureCoordinates.push_back(midUV[0]);

        mVertices.emplace_back(midPoints[1]);
        mTextureCoordinates.push_back(midUV[1]);

        mVertices.emplace_back(midPoints[2]);
        mTextureCoordinates.push_back(midUV[2]);

        mVertices.emplace_back(midPoints[2]);
        mTextureCoordinates.push_back(midUV[2]);

        mVertices.emplace_back(midPoints[1]);
        mTextureCoordinates.push_back(midUV[1]);

        mVertices.emplace_back(triangleVerts[2]);
        mTextureCoordinates.push_back(triangleTex[2]);
        for (int i = 0; i < 12; i++)
            mIndices.emplace_back(index + i);
        index += 12;
        }
        computeFullVertices();
    }
    void Icosphere::computeMidPoint(Point3D& v1,
                             Point3D& v2, Point3D& newV){
        newV.x = v1.x + v2.x;
        newV.y = v1.y + v2.y;
        newV.z = v1.z + v2.z;
        newV = (newV.normalise() * mRadius).toPoint();
    }
    void Icosphere::computeMidPointUV(std::array<float, 2>& t0, std::array<float, 2>& t1,
            std::array<float, 2>& newT){
       newT[0] = (t0[0] + t1[0]) / 2.0f;
       newT[1] = (t0[1] + t1[1]) / 2.0f;
    }
    void Icosphere::addFullVertex(Point3D& position,
                std::array<float,2>& texture){
        mFullVertices.emplace_back(position.x);
        mFullVertices.emplace_back(position.y);
        mFullVertices.emplace_back(position.z);
        mFullVertices.emplace_back(texture[0]);
        mFullVertices.emplace_back(texture[1]);
    }
    void Icosphere::computeFullVertices(){
        for(int i =0 ; i < mVertices.size(); i++){
            mFullVertices.emplace_back(mVertices[i].x);
            mFullVertices.emplace_back(mVertices[i].y);
            mFullVertices.emplace_back(mVertices[i].z);
            mFullVertices.emplace_back(mTextureCoordinates[i][0]);
            mFullVertices.emplace_back(mTextureCoordinates[i][1]);
        }
    }
}}}
