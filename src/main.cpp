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

    int fotograma = 0;
    while (true)
    {
        this_thread::sleep_for(0.1s);
        fotograma++;
        Element personaje = spinner(21, fotograma) | bold | color(Color::Red) | bgcolor(Color::White);
        Element dibujo = hbox({personaje, nave.GetElement(), muro.GetElement(), enemigo.GetElement()});
        Screen pantalla = Screen::Create(Dimension::Full());
        Render(pantalla, dibujo);
        pantalla.Print();
        cout<<pantalla.ResetPosition();
    }
    return EXIT_SUCCESS;
}