#include "../game_menu/game_menu.hpp"
#include "../platforms/platforms.cpp"
using namespace sf;

void BubbleSort(platforms array[], size_t size) {
  for (size_t idx_i = 0; idx_i + 1 < size; ++idx_i) {
    for (size_t idx_j = 0; idx_j + 1 < size - idx_i; ++idx_j) {
      if (array[idx_j + 1]._coordY < array[idx_j]._coordY) {
        swap(array[idx_j], array[idx_j + 1]);
      }
    }
  }
}

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

    _platforms plat1(static_cast<PlatType>(gen()%4), 75+gen()%(WinSizeX-75), WinSizeY/5-15);
    _platforms plat2(static_cast<PlatType>(gen()%4), 75+gen()%(WinSizeX-75), 2*WinSizeY/5-15);
    _platforms plat3(static_cast<PlatType>(gen()%4), 75+gen()%(WinSizeX-75), 3*WinSizeY/5-15);
    _platforms plat4(static_cast<PlatType>(gen()%4), 75+gen()%(WinSizeX-75), 4*WinSizeY/5-15);
    _platforms plat5(static_cast<PlatType>(0), WinSizeX/2, WinSizeY-15);

    platforms _platforms[5]{plat1,plat2,plat3,plat4,plat5}; //Массив платформ для простоты работы с ними

    
    sf::RectangleShape Doodle(sf::Vector2f(20.f, 50.f));

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

    float DoodleSizeX = Doodle.getSize().x;
    float DoodleSizeY = Doodle.getSize().y;

    float PlatSizeX = plat1.shape.getSize().x;
    float PlatSizeY = plat1.shape.getSize().y;

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
                        _platforms[i].Draw(window);
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
            if (DoodleX>=DoodleSizeX/2)
                DoodleX-=0.07f;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            if (DoodleX<=WinSizeX-DoodleSizeX/2)
                DoodleX+=0.07f;
        }
        
        if (!WindowUp){
            if(isUp)
                DoodleY-=0.1f;
            else if(!isUp)
                DoodleY+=0.1f;
            if(DoodleY<=WinSizeY/3-DoodleSizeY/2)
                isUp=false;
        }
        else{
            if (isUp){
                DoodleY-=0.05f;
            }
            else{
                DoodleY+=0.05f;
            }
            for (size_t i = 0; i < 5; ++i){
                _platforms[i]._coordY+=0.2f;
            }
            prevplatformheught+=0.2f;
            if(prevplatformheught>WinSizeY-DoodleSizeY/2){
                WindowUp=false;
            }
            if(DoodleY<=WinSizeY/3)
                isUp=false;
        }
      
        if(DoodleY>=WinSizeY+DoodleSizeY/2){
            window.clear(sf::Color(255, 255, 255));
            return 0;
        }
     
        Doodle.setPosition(DoodleX, DoodleY);

        if (!isUp&&!WindowUp){ // дудл падает
            for (size_t i = 0; i < 5; ++i){
                if ((_platforms[i]._coordY-PlatSizeY/2<=DoodleY+DoodleSizeY/2)&& //Нижний край дудла ниже верхнего края платформы
                (DoodleY+DoodleSizeY/2<=_platforms[i]._coordY+PlatSizeY/2)&& //Нижний край дудла выше нижнего края платформы
                (_platforms[i]._coordX-PlatSizeX/2<DoodleX+DoodleSizeX/2)&& 
                (DoodleX-DoodleSizeX/2<_platforms[i]._coordX+PlatSizeX/2)&& //Дудл попадает на платформу хотя бы краем своего тела
                _platforms[i]._type!=broken){ //Платформа не сломанная
                    isUp=true;
                    WindowUp=true;
                    prevplatformheught=_platforms[i]._coordY;
                    if (_platforms[i]._type==disappearing){
                        _platforms[i].IsJumped=true;
                    }
                    break;
                }
            }
        }
        if (isUp){ // дудл поднимается
            for (size_t i = 0; i < 5; ++i){
                if ((_platforms[i]._coordY-PlatSizeY/2<=DoodleY-DoodleSizeY/2)&& //Верхний край дудла ниже верхнего края платформы
                (DoodleY-DoodleSizeY/2<=_platforms[i]._coordY+PlatSizeY/2)&& //Верхний край дудла выше нижнего края платформы
                (_platforms[i]._coordX-PlatSizeX/2<DoodleX+DoodleSizeX/2)&& 
                (DoodleX-DoodleSizeX/2<_platforms[i]._coordX+PlatSizeX/2)&& //Дудл попадает на платформу хотя бы краем своего тела
                _platforms[i]._type!=broken){ //Платформа не сломанная
                    isUp=false;
                    WindowUp=false;
                    break;
                }
            }
        }

        window.clear(sf::Color(255, 255, 255));

        for (size_t i = 0; i < 5; ++i){
            if (_platforms[i]._coordY>WinSizeY+PlatSizeY/2){
                int type=gen()%4;
                if (type==_platforms[0]._type){
                    type+=1;
                    type%=4;
                }
                platforms newplat(static_cast<PlatType>(type),DoodleSizeY/2+gen()%(int)(window.getSize().x-DoodleSizeY/2), -PlatSizeY/2);
                _platforms[i]=newplat;
            }
            _platforms[i].Draw(window);
        }

        BubbleSort(_platforms, 5);
      
       doodlespriteleft.setPosition(sf::Vector2f(static_cast<float>(DoodleX-30.f),
                                   static_cast<float>(DoodleY-34.f)));
      
        window.draw(Doodle);
        if (lr)
            window.draw(doodlespriteright); //отрисовка Sprite
        else if(!lr)
            window.draw(doodlespriteleft); //отрисовка Sprite
     
        window.display();
    }
    
    return 0;
}
