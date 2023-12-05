#pragma once
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


enum PlatType{
    standart, //Обычные платформы
    broken, //Сломанные платформы(при падении на них дудл не отскакивает, а продолжает падать)
    moving, //Движущиеся платформы
    disappearing //Платформы, исчезающие после первого отскока от них
};

class platforms
{
public:
    sf::Image game_tiles_img;
    sf::Texture game_tiles_text;
    sf::Sprite game_tiles_sprite;
    
    platforms()=delete;
    ~platforms()=default;
    
    platforms(PlatType type, float x, float y);

    void SetX(float x);
    void SetY(float y);
    void SetCoords(float x, float y);

    void Draw(sf::RenderWindow& window);

    void MovePlatform(int winsizeX, int moveSpeed);

    sf::RectangleShape shape;
    PlatType _type;
    float _coordX, _coordY;
    sf::Color _color;
    bool IsRight;
    bool IsJumped=false;
};