#include <iostream>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <fstream>
#include <string>
#include <dibujo.hpp>

using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    Dibujo muro("./assets/images/muro.txt");
    Dibujo nave("./assets/images/nave.txt");
    Dibujo enemigo("./assets/images/enemigo.txt");
    Dibujo platillo("./assets/images/platillo.txt");
    int fotograma = 0;
    while (true)
    {
        this_thread::sleep_for(0.1s);
        Element dibujo = hbox({nave.GetElement(), muro.GetElement(), enemigo.GetElement(), platillo.GetElement()});
        Screen pantalla = Screen::Create(Dimension::Full());
        Render(pantalla, dibujo);
        pantalla.Print();
        cout<<pantalla.ResetPosition();
    }
    return EXIT_SUCCESS;
}