#include "./core/headers/EntryPoint.h"
namespace Lina{
    class Client : public Core::Application
    {
        Client()
        {

        }

        ~Client()
        {

        }
    };
    Core::Application* CreateApplication()
    {
        return new Client();
    }
}
