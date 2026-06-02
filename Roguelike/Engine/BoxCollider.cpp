#include "pch.h"
#include "BoxCollider.h"
#include "MathUtils.h"
#include "CircleCollider.h"

using namespace GameEngine;
std::vector<sf::Vector2f> GameEngine::BoxCollider::GetWorldVertices() const
{
    sf::Vector2f center = GetWorldCenter();
    sf::Vector2f half = GetHalfSize();
    float rotation = GetWorldRotation();

    // Локальные вершины (до поворота)
    std::vector<sf::Vector2f> localVertices = {
        {-half.x, -half.y}, // левый-верхний
        { half.x, -half.y}, // правый-верхний
        { half.x,  half.y}, // правый-нижний
        {-half.x,  half.y}  // левый-нижний
    };

    // Поворачиваем и смещаем в мировые координаты
    std::vector<sf::Vector2f> worldVertices(4);
    float rad = ToRadians(rotation);
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    for (int i = 0; i < 4; ++i) {
        // Поворот
        worldVertices[i].x = localVertices[i].x * cos - localVertices[i].y * sin;
        worldVertices[i].y = localVertices[i].x * sin + localVertices[i].y * cos;
        // Смещение
        worldVertices[i] += center;
    }

    return worldVertices;
}