#include "./include/LayerManager.h"
namespace Lina { namespace Manager{


    b8 Layer::init()
    {
        mGuiLayer = new Lina::Layer::GUI();
        mLayers.push_back(mGuiLayer);
        return true;
    }
    void Layer::addLayer(Core::Layer *layer)
    {
        mLayers.push_back(layer);
    }
    b8 Layer::popLayer()
    {
        if (mLayers.empty())
        {
            return false;
        }
        else
        {
            mLayers.pop_back();
            return true;
        }
    }
    void Layer::spreadEvent(Events::Event& e)
    {
        for (auto l : mLayers)
        {
            l->onEvent(e);
        }
    }
}}
