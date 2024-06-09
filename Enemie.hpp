#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Enemie : public Drawable{
    private:
    Sprite sprite;
    int state;
    int timer;
    int vel; 
    Vector2f point;
    public:
    Enemie(int x, int y, Texture &texture, Vector2f point );
    void Update();
    void ChangeDir();
    Vector2f Pos();
    virtual void draw(RenderTarget &rt, RenderStates rs) const;
};