#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "TextureHolder.h"

using namespace std;


class UIpiece {
private:
    Texture& m_Texture;
    Sprite m_sprite = Sprite(m_Texture);
    
    Vector2f m_position;
    
    bool m_active = false;

    //Initialize must be private, it should only be initialize once (by constructor)
    void initialize(Vector2f objectSize, Vector2f position);

public:
     
    UIpiece(string textureName = NOTEXTURE);
    UIpiece(Vector2f objectSize, Vector2f position, string textureName = NOTEXTURE);
  

    void setTexture(string);
    void setactive(bool);

    void draw(sf::RenderWindow& window);

};
