#include "../game_menu/game_menu.hpp"
#include "../platforms/platforms.cpp"

int main(){
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    bool gamepause=true; //Флаг паузы
    bool WindowUp=false; //Подъём экрана поосле отскока от платформы
    // Объект, который, собственно, является главным окном приложения
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Game", sf::Style::Default, settings);

    int WinSizeX = window.getSize().x;
    int WinSizeY = window.getSize().y; //Переменные размера окна, чтобы не вызвать постоянно функции

    sf::RectangleShape pause(sf::Vector2f(WinSizeX, WinSizeY));
    pause.setFillColor(sf::Color(122,122,122,200));
    pause.setPosition(sf::Vector2f(0,0)); //Прямоугольник, затемняющий экран при выходе в меню паузы

    platforms plat1(static_cast<PlatType>(gen()%4), gen()%(WinSizeX-75), WinSizeY/5-15);
    platforms plat2(static_cast<PlatType>(gen()%4), gen()%(WinSizeX-75), 2*WinSizeY/5-15);
    platforms plat3(static_cast<PlatType>(gen()%4), gen()%(WinSizeX-75), 3*WinSizeY/5-15);
    platforms plat4(static_cast<PlatType>(gen()%4), gen()%(WinSizeX-75), 4*WinSizeY/5-15);
    platforms plat5(static_cast<PlatType>(gen()%4), gen()%(WinSizeX-75), WinSizeY-15);

    //sf::RectangleShape plat1(sf::Vector2f(150.f, 30.f));
    //sf::RectangleShape plat2(sf::Vector2f(150.f, 30.f));
    //sf::RectangleShape plat3(sf::Vector2f(150.f, 30.f));
    //sf::RectangleShape plat4(sf::Vector2f(150.f, 30.f));
    //sf::RectangleShape plat5(sf::Vector2f(150.f, 30.f));

    platforms platforms[5]{plat1,plat2,plat3,plat4,plat5}; //Массив платформ для простоты работы с ними

    
    sf::RectangleShape Doodle(sf::Vector2f(120., 150.));
    Doodle.setFillColor(sf::Color::Green);
    Doodle.setOrigin(sf::Vector2f(Doodle.getSize().x / 2, Doodle.getSize().y / 2)); //Создаём попрыгунчика, ставим центр его координат в центр прямоугольника

    float DoodleX=WinSizeX / 2;
    float DoodleY=WinSizeY - 100.0f;
    Doodle.setPosition(sf::Vector2f(static_cast<float>(DoodleX),
                                   static_cast<float>(DoodleY)));

    bool isUp=true; //флаг, показывает поднимается дудл или нет
    
    int prevplatform;
    float prevplatformheught;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code==sf::Keyboard::Escape)
            {
                sf::Event pauseEvent;
                gamepause=true;
                for (size_t i = 0; i < 5; ++i){
                        platforms[i].Draw(window);
                    }
                    window.draw(Doodle);
                    window.draw(pause);
                    window.display();
                while (gamepause)
                {
                    while (window.pollEvent(pauseEvent)){
                        if (pauseEvent.type == sf::Event::Closed)
                            window.close();               
                        if(pauseEvent.type == sf::Event::KeyReleased && pauseEvent.key.code==sf::Keyboard::Escape){
                            gamepause=false;
                        }
                    }
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                DoodleX-=0.07f;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                DoodleX+=0.07f;
            }

        if (!WindowUp){
            if(isUp)
                DoodleY-=0.1f;
            else if(!isUp)
                DoodleY+=0.1f;
        }
        else{
            if (isUp)
                DoodleY-=0.05f;
            else
                DoodleY+=0.05f;
            
            for (size_t i = 0; i < 5; ++i){
                platforms[i]._coordY+=0.1;
            }
            prevplatformheught+=0.1;
            if(/*platforms[prevplatform]._coordY>WinSizeY-75*/prevplatformheught>WinSizeY-75){
                WindowUp=false;
            }
        }

        if(DoodleY<=WinSizeY/3-75)
                isUp=false;

        if (DoodleX<=-Doodle.getSize().x/2)
            DoodleX=WinSizeX+Doodle.getSize().x/2-1;
        if(DoodleX>=WinSizeX+Doodle.getSize().x/2)
            DoodleX=-Doodle.getSize().x/2+1;

        
        
        if(DoodleY>=WinSizeY+Doodle.getSize().y/2){
            goto gameover;
        }
     
        Doodle.setPosition(DoodleX, DoodleY);

        if (!isUp&&!WindowUp){ // дудл падает
            for (size_t i = 0; i < 5; ++i){
                if ((platforms[i]._coordY-15<=DoodleY+75)&& //Нижний край дудла ниже верхнего края платформы
                (DoodleY+75<=platforms[i]._coordY+15)&& //Нижний край дудла выше нижнего края платформы
                (platforms[i]._coordX-75<DoodleX+60)&& 
                (DoodleX-60<platforms[i]._coordX+75)&& //Дудл попадает на платформу хотя бы краем своего тела
                platforms[i]._type!=broken){ //Платформа не сломанная
                    isUp=true;
                    WindowUp=true;
                    prevplatformheught=platforms[i]._coordY;
                    //prevplatform=i;
                    if (platforms[i]._type==disappearing){
                        platforms[i].IsJumped=true;
                    }
                    break;
                }
            }
        }

        

        window.clear(sf::Color(255, 255, 255));

        for (size_t i = 0; i < 5; ++i){
            platforms[i].Draw(window);
        }

        window.draw(Doodle);
        window.display();
    }


    gameover:{
        window.clear(sf::Color(255, 255, 255));
        return 0;
    }

    
    return 0;
}