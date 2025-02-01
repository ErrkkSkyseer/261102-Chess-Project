#pragma once
#include <SFML/System/Vector2.hpp>

// Overloading Operator "<" and ">" for Vector2i type
// So map can fucking understand how to compare a goddamn vector
// if have #include<map> always #include "Vector2Uitls" 
namespace sf
{
    inline bool operator<(const sf::Vector2i& lhs, const sf::Vector2i& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }

    inline bool operator>(const sf::Vector2i& lhs, const sf::Vector2i& rhs) {
        return lhs.x != rhs.x ? lhs.x > rhs.x : lhs.y > rhs.y;
    }

    inline bool operator<(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }

    inline bool operator>(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
}