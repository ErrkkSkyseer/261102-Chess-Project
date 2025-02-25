#include "UIpiece.h"

void UIpiece::draw(sf::RenderWindow& window)
{
    if (!m_active)
        return;
    m_sprite.setPosition(m_position);
        window.draw(m_sprite);

}


void UIpiece::setTexture(string Texturename){
    string path = "assets/" + Texturename + ".png";
    m_sprite.setTexture(TextureHolder::getTexture(path));
}

void UIpiece::initialize(Vector2f objectSize, Vector2f position)
{
   
    auto Texturesize = m_sprite.getTexture().getSize();
    m_sprite.setScale(Vector2f(objectSize.x / Texturesize.x, objectSize.y / Texturesize.y));
    m_sprite.setColor(Color::White);
    m_position = position;
}
void UIpiece::setactive(bool value)
{
    m_active = value;
}

UIpiece::UIpiece(Vector2f objectSize, Vector2f position)
{
    string path = "assets/notexture.png";
    m_sprite = Sprite(TextureHolder::getTexture(path));

    initialize(objectSize, position);

}

