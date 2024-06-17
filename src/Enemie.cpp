#include<Enemie.hpp>

Enemie::Enemie(int x, int y, Texture &texture, Vector2f p){
    point=p;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(point.x,point.y,8,8));
    sprite.setPosition(x,y);
    sprite.setScale(3,3);
    state=0;
    timer=0;
    vel=24;
    rythm=100;
}

void Enemie::Update(){
    if(timer>=rythm){//velocidad del alienigena
        sprite.move(vel,0);
        state++;
        state%=2 ;
        sprite.setTextureRect(IntRect(point.x+state*9,point.y,8,8));
        timer=0;
    }   
    timer ++;
}

void Enemie::ChangeDir(){
        vel*=-1;
        sprite.move(0,abs(vel));
}

Vector2f Enemie::Pos(){
    return sprite.getPosition();
}

void Enemie::Increaserythm(){
    rythm--;
}

void Enemie::draw(RenderTarget &rt, RenderStates rs) const{
    rt.draw(sprite,rs);
}