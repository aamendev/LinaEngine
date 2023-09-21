# Major Structure
Application { Entry Point, Root }

Entry Point {Init, Run, shutdown}

Init { Set Root }

Root { Pointer to Managers }

::Managers
{
    Renderer;
    File;
    Memory;
    Physics;
    ParticleSystem;
    UI;
    Events;
}
API
{
    APP(Root);
    App.init();
    App.update();
    App.shutdown();
}
