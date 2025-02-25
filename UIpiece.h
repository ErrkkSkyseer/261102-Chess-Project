#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureHolder.h"
using namespace std;

class UIpiece {
private:
    Texture& m_Texture;
    sf::Sprite m_sprite = Sprite(m_Texture);
    Vector2f m_position;
    static const int TILE_SIZE = 100;
    bool m_active = false;


public:
     
  
    void draw(sf::RenderWindow& window);

    void setTexture(string);

    void initialize(Vector2f objectSize, Vector2f position);

    void setactive(bool);

    UIpiece(Vector2f objectSize, Vector2f position);

};
