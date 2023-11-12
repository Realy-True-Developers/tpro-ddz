#include <SFML/Graphics.hpp>
#include <thread>

int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Объект, который, собственно, является главным окном приложения
    sf::RenderWindow window(sf::VideoMode(600, 600), "Game", sf::Style::Default, settings);

    sf::RectangleShape Doodle(sf::Vector2f(120.f, 300.f));
    Doodle.setFillColor(sf::Color::Green);
    Doodle.setOrigin(sf::Vector2f(Doodle.getSize().x / 2, Doodle.getSize().y / 2));
    Doodle.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x / 2),
                                   static_cast<float>(window.getSize().y - 10.0f)));

    sf::Clock* clock = new sf::Clock;
    sf::Clock* upClock= new sf::Clock;
    float dT;
    float upTime = 0;
    float speed = 3000;
    float YSpeed = 1;
    while (window.isOpen())
    {
        dT = clock->restart().asSeconds();
        if (upTime>=10){
            upTime=upClock->restart().asSeconds();
            upClock->restart();
        }
        else{
            upTime=upClock->getElapsedTime().asSeconds();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                Doodle.move(-1.0f* speed*dT, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                Doodle.move(1.0f* speed*dT, 0.0f);
            if (upTime<=5||upTime>10){
                Doodle.move(0.0f,-YSpeed*upTime);
            }
            else{
                Doodle.move(0.0f,YSpeed*upTime);
            }
        }

        window.clear(sf::Color(255, 255, 255, 0));

        window.draw(Doodle);

        window.display();
    }

    return 0;
}