#include "EntryPoint.h"

int main()
{
    ly::Application* app = GetApplication();
    app->Run();
    delete app;
}