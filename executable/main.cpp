#include "../game_menu/game_menu.hpp"
#include "../platforms/platforms.cpp"
using namespace sf;

int main(){
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());



    Image doodleimageright; //создал объект Image
    doodleimageright.loadFromFile("../../images/blue-lik-right.png");
    Image doodleimageleft; //создал объект Image
    doodleimageleft.loadFromFile("../../images/blue-lik-left.png");

    Texture doodletextureright; //создал объект Texture
    doodletextureright.loadFromImage(doodleimageright); //передал в него объект Image
    Texture doodletextureleft; //создал объект Texture
    doodletextureleft.loadFromImage(doodleimageleft); //передал в него объект Image

    Sprite doodlespriteright; // создал объект Sprite
    doodlespriteright.setTexture(doodletextureright); //передал в него объект Texture
    Sprite doodlespriteleft; // создал объект Sprite
    doodlespriteleft.setTexture(doodletextureleft); //передал в него объект Texture





    ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    bool lr = true;
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

    platforms platforms[5]{plat1,plat2,plat3,plat4,plat5}; //Массив платформ для простоты работы с ними

    
    sf::RectangleShape Doodle(sf::Vector2f(20., 30.));
    Doodle.setFillColor(sf::Color::Green);
    Doodle.setOrigin(sf::Vector2f(Doodle.getSize().x / 2, Doodle.getSize().y / 2)); //Создаём попрыгунчика, ставим центр его координат в центр прямоугольника

    float DoodleX=WinSizeX / 2;
    float DoodleY=WinSizeY - 100.0f;
    Doodle.setPosition(sf::Vector2f(static_cast<float>(DoodleX),
                                   static_cast<float>(DoodleY)));

    
    doodlespriteright.setPosition(sf::Vector2f(static_cast<float>(DoodleX-30.f),
                                   static_cast<float>(DoodleY-34.f))); // задал Sprite начальную позицию далее он двигается вместе с первоначальным прямоугольником
    doodlespriteleft.setPosition(sf::Vector2f(static_cast<float>(DoodleX-30.f),
                                   static_cast<float>(DoodleY-34.f))); // задал Sprite начальную позицию далее он двигается вместе с первоначальным прямоугольником


    bool isUp=true; //флаг, показывает поднимается дудл или нет
    
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
                    window.draw(doodlespriteright); //отрисовка Sprite
                    window.draw(doodlespriteleft);
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
                doodlespriteleft.move(-0.07f, 0);
                doodlespriteleft.setTextureRect(IntRect(0,0,62,60));
                doodlespriteright.setTextureRect(IntRect(300,200,200,200));
                lr = false;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                DoodleX+=0.07f;
                doodlespriteright.move(0.07f, 0);
                doodlespriteright.setTextureRect(IntRect(0,0,62,60));
                doodlespriteleft.setTextureRect(IntRect(300,200,200,200));
                lr = true;
            }

        if (!WindowUp){
            if(isUp) {
                DoodleY-=0.1f;
                doodlespriteright.move(0, -0.1f);
                doodlespriteleft.move(0, -0.1f); }
            else if(!isUp) {
                DoodleY+=0.1f;
                doodlespriteright.move(0, 0.1f);
                doodlespriteleft.move(0, 0.1f); }
        }
        else{
            if (isUp) {
                DoodleY-=0.05f;
                doodlespriteright.move(0, -0.05f);
                doodlespriteleft.move(0, -0.05f); }
            else {
                DoodleY+=0.05f;
                doodlespriteright.move(0, 0.05f);
                doodlespriteleft.move(0, 0.05f); }
            for (size_t i = 0; i < 5; ++i){
                platforms[i]._coordY+=0.1;
            }
            prevplatformheught+=0.1;
            if(prevplatformheught>WinSizeY-75){
                WindowUp=false;
            }
        }

        if(DoodleY<=WinSizeY/3-75)
                isUp=false;

        if (DoodleX<=-Doodle.getSize().x/2)
            DoodleX=WinSizeX+Doodle.getSize().x/2-1;
        if(DoodleX>=WinSizeX+Doodle.getSize().x/2)
            DoodleX=-Doodle.getSize().x/2+1;
        doodlespriteright.setPosition(sf::Vector2f(static_cast<float>(DoodleX-30.f),
                                   static_cast<float>(DoodleY-34.f)));
        doodlespriteleft.setPosition(sf::Vector2f(static_cast<float>(DoodleX-30.f),
                                   static_cast<float>(DoodleY-34.f)));
        
        if(DoodleY>=WinSizeY+Doodle.getSize().y/2){
            goto gameover;
        }
     
        Doodle.setPosition(DoodleX, DoodleY);

        if (!isUp&&!WindowUp){ // дудл падает
            for (size_t i = 0; i < 5; ++i){
                if ((platforms[i]._coordY-platforms[i].shape.getSize().y/2<=DoodleY+Doodle.getSize().y/2)&& //Нижний край дудла ниже верхнего края платформы
                (DoodleY+Doodle.getSize().y/2<=platforms[i]._coordY+platforms[i].shape.getSize().y/2)&& //Нижний край дудла выше нижнего края платформы
                (platforms[i]._coordX-platforms[i].shape.getSize().x/2<DoodleX+Doodle.getSize().x/2)&& 
                (DoodleX-Doodle.getSize().x/2<platforms[i]._coordX+platforms[i].shape.getSize().x/2)&& //Дудл попадает на платформу хотя бы краем своего тела
                platforms[i]._type!=broken){ //Платформа не сломанная
                    isUp=true;
                    WindowUp=true;
                    prevplatformheught=platforms[i]._coordY;
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
        if (lr)
            window.draw(doodlespriteright); //отрисовка Sprite
        else if(!lr)
            window.draw(doodlespriteleft); //отрисовка Sprite
        window.display();
    }


    gameover:{
        window.clear(sf::Color(255, 255, 255));
        return 0;
    }

    
    return 0;
}
