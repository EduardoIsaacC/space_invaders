#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Wall : public Drawable
{
private:
    vector<Sprite> sprites;
    vector<pair<int, int>> state;

public:
    Wall(int x, int y, Texture &tecture);
    void Pos(vector<pair<int, Vector2f>> &pos);
    void Collision(int indice, bool up);
    void Update();
    virtual void draw(RenderTarget &rt, RenderStates rs) const;
};