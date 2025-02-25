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
    auto textureSize = m_sprite.getTexture().getSize();
    m_sprite.setScale(Vector2f(objectSize.x / textureSize.x, objectSize.y / textureSize.y));
    m_sprite.setColor(Color::White);
    m_position = position;
}
void UIpiece::setactive(bool value)
{
    m_active = value;
}

/// <summary>
/// Fixing no appropiate defult constroctor issue.
/// </summary>
/// <param name="textureName"></param>
UIpiece::UIpiece(string textureName)
    : m_Texture(TextureHolder::getTexture("assets/" + textureName + ".png"))
{
}

UIpiece::UIpiece(Vector2f objectSize, Vector2f position, string textureName)
    : m_Texture(TextureHolder::getTexture("assets/" + textureName + ".png"))
{
    initialize(objectSize, position);
}

