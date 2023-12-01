#include "platforms.hpp"
using namespace sf;

platforms::platforms(PlatType type, float x, float y):
shape(sf::Vector2f(50.f, 10.f)), _type(type), _coordX(x), _coordY(y), IsRight(false), IsJumped(false),GreenP(false), BrownP(false){



   



    shape.setOrigin(35,10);
    switch (_type)
    {
    case 0:{
        _color=sf::Color(255,255,255); //Green
        GreenP=true;
        BrownP=false;
        BlueP=false;
        GreyP=false;
        break;
    }
    case 1:{
        _color=sf::Color(255,255,255); //Brown
        GreenP=false;
        BrownP=true;
        BlueP=false;
        GreyP=false;
        break;
    }
    case 2:{
        _color=sf::Color(255,255,255); //Blue
        GreenP=false;
        BrownP=false;
        BlueP=true;
        GreyP=false;
        break;
    }
    case 3:{
        _color=sf::Color(255,255,255); //Grey
        GreenP=false;
        BrownP=false;
        BlueP=false;
        GreyP=true;
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
                platforms newplat(static_cast<PlatType>(gen()%3),gen()%(window.getSize().x-75), -15);
                *this=newplat;
            }
            break;
        }
    }
    this->shape.setPosition(_coordX, _coordY);
    if (_coordY>window.getSize().y+15){
        platforms newplat2(static_cast<PlatType>(gen()%3),gen()%(window.getSize().x-75), -15);
        *this=newplat2;
    }
    window.draw(this->shape);
}
