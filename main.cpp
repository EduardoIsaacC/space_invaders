#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<time.h>
#include "Player.hpp"
#include "Bullet.hpp"
#include"Enemie.hpp"

using namespace std;
using namespace sf;

void UpdatePlayer(Player &player, bool &bulletActive, Bullet &bulletPlayer);
void UpdateBulletPlayer(Bullet &bulletPlayer, bool &bulletActive,vector<vector<Enemie>> &enemies, IntRect &bulletRect, IntRect &enemieRect);
void UpdateEnemies(vector<vector<Enemie>> &enemies, int &dirEnemies, int &minX, int &maxX);
void UpdateBulletsEnemies(Player &player, IntRect &bulletRect);

Texture spritesheet;
int timer=0;
int rythm=125;
vector<Bullet> bulletsEnemies;

IntRect playerRect;


int main(){
   
   if(!spritesheet.loadFromFile("./assets/images/spritesheet.png")){
        cout<<"Error al cargar la textura\n";
    }

    Player player(288,555,spritesheet);

    bool bulletActive=false;
    Bullet bulletPlayer(0,0,spritesheet,IntRect(0,0,0,0),0);
    IntRect bulletRect;

    vector<vector<Enemie>> enemies(7,vector<Enemie>(12,Enemie(0,0,spritesheet,Vector2f(0,0))));
    IntRect enemieRect;
    Vector2f sectionSpritesheet;

    int dirEnemies=1;

    int maxX, minX;

    for(int i=0; i < 7 ;i++){
            for (int j = 0; j < 12 ; j++)
        {
            if(i==0){
                sectionSpritesheet = Vector2f(0,0);
            }else if(i<3){
                sectionSpritesheet = Vector2f(0,9+(8*4+4));
            }else if(i<5){
                sectionSpritesheet = Vector2f(0,18+(8*4+4)*2);
            }else if(i<7){
                sectionSpritesheet = Vector2f(0,27+(8*4+4)*3);
            }
            enemies[i][j]=Enemie(j*30+24,i*30+24,spritesheet,sectionSpritesheet);
        }  
    }
    
    RenderWindow window(VideoMode(600,600),"Space Invaders");
    window.setFramerateLimit(60);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type=Event::Closed)
                window.close();
        }

        UpdatePlayer(player,bulletActive,bulletPlayer);

        UpdateBulletPlayer(bulletPlayer, bulletActive, enemies,bulletRect,enemieRect );

        UpdateEnemies(enemies, dirEnemies, minX,maxX);

        UpdateBulletsEnemies(player, bulletRect);

        if(!player.Alive()) window.close();

        for(int i=0; i < (int)enemies.size() ;i++){
            for (int j = 0; j < enemies[i].size() ; j++){
                if(enemies[i][j].Pos().y>=480){
                    window.close();
                }
            }
        }
        window.clear();

        if (bulletActive) window.draw(bulletPlayer);

        for (int i = 0; i < (int)bulletsEnemies.size(); i++){
            window.draw(bulletsEnemies[i]);
        }

        

        for(int i=0; i < (int)enemies.size() ;i++){
            for (int j = 0; j < enemies[i].size() ; j++){
                    window.draw(enemies[i][j]);
        }
        }
        
        window.draw(player);


        window.display();
    }
    return 0; 
}
void UpdatePlayer(Player &player, bool &bulletActive,Bullet &bulletPlayer){

     player.Update();

    if(player.Shoot()&&!bulletActive){//creamos un if si el jugador desea disparar y otra condicion que si hay un abala en la pantalla no pueda disparar 
         Bullet b(player.pos().x+24,player.pos().y+12,spritesheet,IntRect(13*8+16,6*8+6,8,8),-10);
        bulletPlayer = b;
        bulletActive=true;
        }
}

void UpdateBulletPlayer(Bullet &bulletPlayer, bool &bulletActive,vector<vector<Enemie>> &enemies, IntRect &bulletRect, IntRect &enemieRect){
  
    if(bulletActive) {//si hay una bala 
            bulletPlayer.Update();//llamamos al metodo update 
            if(bulletPlayer.Pos().y<-24)bulletActive = false;//y si la posicion de la bala es eigual a y-24, ya no esta la bala dentro de l panatalla 
            
            bulletRect=IntRect(bulletPlayer.Pos().x,bulletPlayer.Pos().y,3,8);
            for(int i=0; i < (int)enemies.size() ;i++){
                for (int j = 0; j < enemies[i].size() ; j++){
                    enemieRect=IntRect(enemies[i][j].Pos().x,enemies[i][j].Pos().y,24,24);
                    if(enemieRect.intersects(bulletRect)){
                        enemies[i].erase(enemies[i].begin()+j);
                        bulletActive=false;

                        break;
                }
                if(!bulletActive) break;
            }
         }
         if(!bulletActive){
            for(int i=0; i < (int)enemies.size() ;i++){
                for (int j = 0; j < enemies[i].size() ; j++){
                    enemies[i][j].Increaserythm();
                    
                }
            }
            rythm--;
         }
    }
}//por lo tanto arroja a que la bala y ano esta activa por lo tanro puede volver a disparar 

void UpdateEnemies(vector<vector<Enemie>> &enemies, int &dirEnemies, int &minX, int &maxX){
    maxX=0;
    minX=600;
        for(int i=0; i < (int)enemies.size() ;i++){
            for (int j = 0; j < enemies[i].size() ; j++){
                    maxX=max(maxX,(int)enemies[i][j].Pos().x+24*dirEnemies);
                    minX=min(minX,(int)enemies[i][j].Pos().x+24*dirEnemies);
        }
        }
        if(minX<24||maxX>576){
            for(int i=0; i < (int)enemies.size() ;i++){
            for (int j = 0; j < enemies[i].size() ; j++){
                enemies[i][j].ChangeDir();
                }
            }
            dirEnemies*=-1;
        }        
        for(int i=0; i < (int)enemies.size() ;i++){
            for (int j = 0; j < enemies[i].size() ; j++){
                    enemies[i][j].Update();
        }
        }

        timer++;

        if(timer>=rythm&&(int)enemies[0].size()>0){
            cout<<timer<<'\n';
            timer=0;
            srand(time(NULL));
            int enem = rand()%(int)enemies[0].size();
            Bullet bullet = Bullet(enemies[0][enem].Pos().x+9,enemies[0][enem].Pos().y-24,spritesheet,IntRect(13*8+8,8*2+2,8,8),10);
            bulletsEnemies.push_back(bullet);        
        }
}

void UpdateBulletsEnemies(Player &player, IntRect &bulletRect){

    for(int i=0; i < (int)bulletsEnemies.size(); i++){
        bulletsEnemies[i].Update();
    }

    for(int i=0; i<(int)bulletsEnemies.size(); i++){
        if(bulletsEnemies[i].Pos().y>600){
            bulletsEnemies.erase(bulletsEnemies.begin()+i);
        }
    }

    playerRect=IntRect(player.pos().x, player.pos().y,48,24);
    for(int i=0; i<(int)bulletsEnemies.size(); i++){
        bulletRect = IntRect(bulletsEnemies[i].Pos().x,bulletsEnemies[i].Pos().y,3,24);
        if(playerRect.intersects(bulletRect)){
            bulletsEnemies.erase(bulletsEnemies.begin()+i);
            player.Takelife();
        }
    }
}