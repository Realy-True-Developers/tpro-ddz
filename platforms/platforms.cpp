#include "platforms.hpp"

platforms::platforms(PlatType type, float x, float y):
shape(sf::Vector2f(150.f, 30.f)), _type(type), _coordX(x), _coordY(y), IsRight(false), IsJumped(false){
    shape.setOrigin(75,15);
    switch (_type)
    {
    case 0:{
        _color=sf::Color::Cyan;
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
    this->shape.setPosition(_coordX, _coordY);
    switch (_type)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:{
            if (this->IsRight)
                this->SetX(this->_coordX+0.03f);
            else
                this->SetX(this->_coordX-0.03f); //Передвигаем движущиеся платформы
            if (_coordX>=window.getSize().x-75){
                IsRight=false;
                break;
            }
            if (_coordX<=75)
                IsRight=true; //Меняем направление движения
            break;
        }
        case 3:{
            if (IsJumped){
                platforms newplat(static_cast<PlatType>(rand()%3),rand()%(window.getSize().x-75), 200+rand()%(window.getSize().y-75));
                *this=newplat;
            }
            break;
        }
    }
    window.draw(this->shape);
}
