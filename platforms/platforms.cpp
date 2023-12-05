#include "platforms.hpp"
using namespace std;

platforms::platforms(PlatType type, float x, float y):
shape(sf::Vector2f(60.f, 14.f)), _type(type), _coordX(x), _coordY(y), IsRight(static_cast<bool>(rand()%2)), IsJumped(false){
    shape.setOrigin(30,7);
    game_tiles_img.loadFromFile("../../images/game-tiles.png");
    game_tiles_text.loadFromImage(game_tiles_img); //передал в него объект Image
    game_tiles_sprite.setTexture(game_tiles_text); //передал в него объект Texture
    switch (_type)
    {
    case 0:{
        _color=sf::Color::Green;
        break;
    }
    case 1:{
        _color=sf::Color(205,133,65); //Brown
        break;
    }
    case 2:{
        _color=sf::Color::Blue;
        break;
    }
    case 3:{
        _color=sf::Color(122,122,122);
        break;
    }
    default:
        break;
    }

    shape.setFillColor(_color);
}


void platforms::SetX(float x){
    _coordX=x;
}
void platforms::SetY(float y){
    _coordY=y;
}
void platforms::SetCoords(float x, float y){
    this->SetX(x);
    this->SetY(y);
}

void platforms::Draw(sf::RenderWindow& window){
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());
    if (_coordY>window.getSize().y+5){
        platforms newplat2(static_cast<PlatType>(gen()%4),25+gen()%(window.getSize().x-150), -5);
        *this=newplat2;
    }
    switch (_type)
    {
        case 0:{
            game_tiles_sprite.setTextureRect(sf::IntRect(0,0,64,16));
            break;
        }
        case 1:{
            game_tiles_sprite.setTextureRect(sf::IntRect(0,72,64,16));
            break;
        }
        case 2:{
            game_tiles_sprite.setTextureRect(sf::IntRect(0,17,64,17));
            if (IsRight)
                SetX(_coordX+0.03f);
            else
                SetX(_coordX-0.03f); //Передвигаем движущиеся платформы
            if (_coordX>=window.getSize().x-75){
                IsRight=false;
                break;
            }
            if (_coordX<=75)
                IsRight=true; //Меняем направление движения
            break;
        }
        case 3:{
            game_tiles_sprite.setTextureRect(sf::IntRect(0,36,64,16));
            if (IsJumped){
                _color=sf::Color(0,0,0,0);
                shape.setFillColor(_color);
            }
            break;
        }
    }
    shape.setPosition(_coordX, _coordY);
    game_tiles_sprite.setPosition(_coordX-30, _coordY-7);

    window.draw(shape);
    //window.draw(game_tiles_sprite);
}