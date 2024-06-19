#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <Player.hpp>
#include <Bullet.hpp>
#include <Enemie.hpp>
#include <Wall.hpp>

using namespace std;
using namespace sf;

void UpdatePlayer(Player &player, Bullet &bulletPlayer);
void UpdateBulletPlayer(Bullet &bulletPlayer, vector<vector<Enemie>> &enemies);
void UpdateEnemies(vector<vector<Enemie>> &enemies);
void UpdateBulletsEnemies(Player &player);
void UpdateWall(vector<Wall> &wall, Bullet &bulletPlayer);

Texture spritesheet;

int timer = 0;
int rythm = 125;

int dirEnemies = 1;
int maxX, minX; // We declared this global so we don't have to declare it in the void
int cantEnemies;

vector<Bullet> bulletsEnemies;

vector<pair<int, Vector2f>> positionWall;

Vector2f sectionSpritesheet;

IntRect playerRect; // We declared this global so we don't have to declare it in the void
IntRect bulletRect; // We declared this global so we don't have to declare it in the void
IntRect enemieRect; // We declared this global so we don't have to declare it in the void
IntRect wallRect;

bool bulletActive = false; // We declared this global so we don't have to declare it in the void

int main()
{
    Font font2;
    if (!font2.loadFromFile("./fonts/Arcade Classic.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
        cout<< "Error al cargar la fuente";
        throw new exception();
    }
    // Crear un objeto de texto ARCADE
    Text text2;
    if (!spritesheet.loadFromFile("./assets/images/spritesheet.png"))
    {
        cout << "Error al cargar la textura\n";
        throw new exception();
    }
    // Cargar una fuente de texto
    text2.setFont(font2);
    text2.setString("¿Podras ganar?");
    text2.setCharacterSize(40);
    text2.setPosition(100, 100);
    text2.setFillColor(sf::Color::White);

    Player player(288, 555, spritesheet);

    Bullet bulletPlayer(0, 0, spritesheet, IntRect(0, 0, 0, 0), 0);

    vector<vector<Enemie>> enemies(7, vector<Enemie>(12, Enemie(0, 0, spritesheet, Vector2f(0, 0))));

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (i == 0)
            {
                sectionSpritesheet = Vector2f(0, 0);
            }
            else if (i < 3)
            {
                sectionSpritesheet = Vector2f(0, 9 + (8 * 4 + 4));
            }
            else if (i < 5)
            {
                sectionSpritesheet = Vector2f(0, 18 + (8 * 4 + 4) * 2);
            }
            else if (i < 7)
            {
                sectionSpritesheet = Vector2f(0, 27 + (8 * 4 + 4) * 3);
            }
            enemies[i][j] = Enemie(j * 30 + 24, i * 30 + 24, spritesheet, sectionSpritesheet);
        }
    }

    vector<Wall> wall(3, Wall(0, 0, spritesheet));

    for (int i = 0; i < 3; i++)
    {
        wall[i] = Wall(80 + 200 * i, 460, spritesheet); // Move to the left, 200 is the seperation between walls,  altitude
    }

    RenderWindow window(VideoMode(600, 600), "Space Invaders");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type = Event::Closed)
                window.close();
        }

        UpdatePlayer(player, bulletPlayer);

        UpdateBulletPlayer(bulletPlayer, enemies);

        UpdateEnemies(enemies);

        UpdateBulletsEnemies(player);

        UpdateWall(wall, bulletPlayer);

        if (!player.Alive())
        {
            system("clear");
            cout << "You lost\n";
            window.close();
        }

        for (int i = 0; i < (int)enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].size(); j++)
            {
                if (enemies[i][j].Pos().y >= 480)
                {
                    system("clear");
                    cout << "You lost\n";
                    window.close();
                    return 0;
                }
            }
        }

        cantEnemies = 0;

        for (int i = 0; i < (int)enemies.size(); i++)
            cantEnemies += (int)enemies[i].size();

        if (cantEnemies == 0)
        {
            system("clear");
            cout << "You Win\n";
            window.close();
        }

        window.clear();

        if (bulletActive)
            window.draw(bulletPlayer);

        for (int i = 0; i < (int)bulletsEnemies.size(); i++)
        {
            window.draw(bulletsEnemies[i]);
        }

        for (int i = 0; i < (int)enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].size(); j++)
            {
                window.draw(enemies[i][j]);
            }
        }

        for (int i = 0; i < 3; i++)
            window.draw(wall[i]);

        window.draw(player);
        window.draw(text2);
        window.display();
    }
    return 0;
}

void UpdatePlayer(Player &player, Bullet &bulletPlayer)
{

    player.Update();

    if (player.Shoot() && !bulletActive)
    { // creamos un if si el jugador desea disparar y otra condicion que si hay un abala en la pantalla no pueda disparar
        Bullet b(player.pos().x + 24, player.pos().y + 12, spritesheet, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -10);
        bulletPlayer = b;
        bulletActive = true;
    }
}

void UpdateBulletPlayer(Bullet &bulletPlayer, vector<vector<Enemie>> &enemies)
{

    if (bulletActive)
    {                          // si hay una bala
        bulletPlayer.Update(); // llamamos al metodo update
        if (bulletPlayer.Pos().y < -24)
            bulletActive = false; // y si la posicion de la bala es eigual a y-24, ya no esta la bala dentro de l panatalla

        bulletRect = IntRect(bulletPlayer.Pos().x, bulletPlayer.Pos().y, 3, 8);
        for (int i = 0; i < (int)enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].size(); j++)
            {
                enemieRect = IntRect(enemies[i][j].Pos().x, enemies[i][j].Pos().y, 24, 24);
                if (enemieRect.intersects(bulletRect))
                {
                    enemies[i].erase(enemies[i].begin() + j);
                    bulletActive = false;

                    break;
                }
                if (!bulletActive)
                    break;
            }
        }
        if (!bulletActive)
        {
            for (int i = 0; i < (int)enemies.size(); i++)
            {
                for (int j = 0; j < enemies[i].size(); j++)
                {
                    enemies[i][j].Increaserythm();
                }
            }
            rythm--;
        }
    }
} // por lo tanto arroja a que la bala y ano esta activa por lo tanro puede volver a disparar

void UpdateEnemies(vector<vector<Enemie>> &enemies)
{

    maxX = 0;
    minX = 600;
    for (int i = 0; i < (int)enemies.size(); i++)
    {
        for (int j = 0; j < enemies[i].size(); j++)
        {
            maxX = max(maxX, (int)enemies[i][j].Pos().x + 24 * dirEnemies);
            minX = min(minX, (int)enemies[i][j].Pos().x + 24 * dirEnemies);
        }
    }
    if (minX < 24 || maxX > 576)
    {
        for (int i = 0; i < (int)enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].size(); j++)
            {
                enemies[i][j].ChangeDir();
            }
        }
        dirEnemies *= -1;
    }
    for (int i = 0; i < (int)enemies.size(); i++)
    {
        for (int j = 0; j < enemies[i].size(); j++)
        {
            enemies[i][j].Update();
        }
    }

    timer++;

    if (timer >= rythm && (int)enemies[0].size() > 0)
    {
        timer = 0;
        srand(time(NULL));
        int enem = rand() % (int)enemies[0].size();
        Bullet bullet = Bullet(enemies[0][enem].Pos().x + 9, enemies[0][enem].Pos().y - 24, spritesheet, IntRect(13 * 8 + 8, 8 * 2 + 2, 8, 8), 10);
        bulletsEnemies.push_back(bullet);
    }
}

void UpdateBulletsEnemies(Player &player)
{

    for (int i = 0; i < (int)bulletsEnemies.size(); i++)
    {
        bulletsEnemies[i].Update();
    }

    for (int i = 0; i < (int)bulletsEnemies.size(); i++)
    {
        if (bulletsEnemies[i].Pos().y > 600)
        {
            bulletsEnemies.erase(bulletsEnemies.begin() + i);
        }
    }

    playerRect = IntRect(player.pos().x, player.pos().y + 9, 48, 15);
    for (int i = 0; i < (int)bulletsEnemies.size(); i++)
    {
        bulletRect = IntRect(bulletsEnemies[i].Pos().x, bulletsEnemies[i].Pos().y, 3, 24);
        if (playerRect.intersects(bulletRect))
        {
            bulletsEnemies.erase(bulletsEnemies.begin() + i);
            player.Takelife();
        }
    }
}

void UpdateWall(vector<Wall> &wall, Bullet &bulletPlayer)
{

    if (bulletActive)
    {
        bulletRect = IntRect(bulletPlayer.Pos().x, bulletPlayer.Pos().y, 3, 8);
        for (int i = 0; i < 3; i++)
        {
            wall[i].Pos(positionWall);
            for (int j = 0; j < (int)positionWall.size(); j++)
            {
                wallRect = IntRect(positionWall[j].second.x, positionWall[j].second.y, 24, 24);
                if (wallRect.intersects(bulletRect))
                {
                    wall[i].Collision(positionWall[j].first, false);
                    bulletActive = false;
                }
            }
            if (!bulletActive)
                break;
        }
    }

    bool elim = false;

    for (int h = 0; h < (int)bulletsEnemies.size(); h++)
    {
        bulletRect = IntRect(bulletsEnemies[h].Pos().x, bulletsEnemies[h].Pos().y, 3, 8);
        for (int i = 0; i < 3; i++)
        {
            wall[i].Pos(positionWall);
            for (int j = 0; j < (int)positionWall.size(); j++)
            {
                wallRect = IntRect(positionWall[j].second.x, positionWall[j].second.y, 24, 24);
                if (wallRect.intersects(bulletRect))
                {
                    wall[i].Collision(positionWall[i].first, true);
                    bulletsEnemies.erase(bulletsEnemies.begin() + h);
                    elim = true;
                    break;
                }
            }
            if (elim)
                break;
        }
    }

    for (int i = 0; i < 3; i++)
        wall[i].Update();
}
