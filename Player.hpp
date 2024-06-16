#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player: public Drawable{
    private:
        Sprite sprite;
        int life;
        int vel;
        bool shoot=false;
        public:
    Player(int x, int y, Texture &texture);
        void Update();
        bool Shoot();
        void Takelife();
        bool Alive();
        Vector2f pos();
        virtual void draw(RenderTarget &rt, RenderStates rs) const;
};