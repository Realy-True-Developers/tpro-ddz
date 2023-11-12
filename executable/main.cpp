#include <SFML/Graphics.hpp>
#include <thread>
#include <random>

#include "../game_menu/game_menu.hpp"

int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Объект, который, собственно, является главным окном приложения
    sf::RenderWindow window(sf::VideoMode(800, 1000), "Game", sf::Style::Default, settings);

    int WinSizeX = window.getSize().x;
    int WinSizeY = window.getSize().y;

    sf::RectangleShape plat1(sf::Vector2f(150.f, 30.f));
    sf::RectangleShape plat2(sf::Vector2f(150.f, 30.f));
    sf::RectangleShape plat3(sf::Vector2f(150.f, 30.f));
    sf::RectangleShape plat4(sf::Vector2f(150.f, 30.f));
    sf::RectangleShape plat5(sf::Vector2f(150.f, 30.f));

    sf::RectangleShape platforms[5]{plat1,plat2,plat3,plat4,plat5};
    for (size_t i = 0; i < 5; ++i) {
        platforms[i].setOrigin(75,15);
        platforms[i].setFillColor(sf::Color::Cyan);
        float x = rand()%(WinSizeX-75);
        float y = rand()%(WinSizeY-15);
        platforms[i].setPosition(x,y);
    }
    
    
    
    sf::RectangleShape Doodle(sf::Vector2f(120.f, 150.f));
    Doodle.setFillColor(sf::Color::Green);
    Doodle.setOrigin(sf::Vector2f(Doodle.getSize().x / 2, Doodle.getSize().y / 2));
    float dY=0;

    float DoodleX=WinSizeX / 2;
    float DoodleY=WinSizeY - 100.0f;
    Doodle.setPosition(sf::Vector2f(static_cast<float>(DoodleX),
                                   static_cast<float>(DoodleY)));

    bool isUp=true; //флаг, показывает поднимается дудл или нет
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                DoodleX-=0.07f;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                DoodleX+=0.07f;
            }
            
        if(isUp)
            DoodleY+=0.1f;
        else
            DoodleY-=0.1f;

        if (DoodleX<=-Doodle.getSize().x/2)
            DoodleX=WinSizeX+Doodle.getSize().x/2-1;
        if(DoodleX>=WinSizeX+Doodle.getSize().x/2)
            DoodleX=-Doodle.getSize().x/2+1;

        if(DoodleY>=WinSizeY-Doodle.getSize().y/2)
                isUp=false;
            if(DoodleY<=Doodle.getSize().y/2)
                isUp=true;
            
        if (!isUp)
        {
            for (size_t i = 0; i < 5; ++i)
            {
                if (DoodleY+75.f==platforms[i].getPosition().y-15&&(platforms[i].getPosition().x-75<=DoodleX&&DoodleX<=platforms[i].getPosition().x+75))
                {
                    isUp=true;
                }
            }
            
        }
        
        Doodle.setPosition(DoodleX, DoodleY);

        window.clear(sf::Color(255, 255, 255, 0));

        for (size_t i = 0; i < 5; ++i){
            window.draw(platforms[i]);
        }

        window.draw(Doodle);
        window.display();
    }
    return 0;
}
