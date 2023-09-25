#include "Renderable.h"

namespace Lina{ namespace Graphics{
    void Renderable::computeFullVertices()
    {
        for (int i = 0; i < mVertices.size(); i++)
        {
            mFullVertices.emplace_back(mVertices[i].x);
            mFullVertices.emplace_back(mVertices[i].y);
            mFullVertices.emplace_back(mVertices[i].z);
            mFullVertices.emplace_back(mTextureCoordinates[i].u);
            mFullVertices.emplace_back(mTextureCoordinates[i].v);
        }
    }
}}
