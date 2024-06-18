#include <Player.hpp>

Player::Player(int x, int y, Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(13 * 8 + 8, 7 * 8 + 7, 16, 8));
    sprite.setPosition(x, y);
    sprite.setScale(3, 3);
    life = 3;
    vel = 5;
}

void Player::Update()
{
    if (Keyboard::isKeyPressed(Keyboard::Right) && sprite.getPosition().x + vel < 552)
    {
        sprite.move(vel, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && sprite.getPosition().x + vel * -1 > 0)
    {
        sprite.move(vel * -1, 0);
    }
}

bool Player::Shoot()
{
    if (Keyboard::isKeyPressed(Keyboard::Space) && !shoot)
    {
        shoot = true;
        return true;
    }
    else if (!Keyboard::isKeyPressed(Keyboard::Space))
    {
        shoot = false;
    }
    return false;
}

Vector2f Player::pos()
{
    return sprite.getPosition();
}

void Player::Takelife()
{
    life--;
}

bool Player::Alive()
{
    return (life != 0);
}

void Player::draw(RenderTarget &rt, RenderStates rs) const
{
    rt.draw(sprite, rs);
}