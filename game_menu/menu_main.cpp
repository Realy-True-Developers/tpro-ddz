#include "game_menu.hpp"
#include <Windows.h>
using namespace sf;



void GameStart() // Функция запуска игры
{
    RenderWindow Play(VideoMode::getDesktopMode(), L"Уровень 1", Style::Fullscreen);
    RectangleShape background_play(Vector2f(1920, 1080));
    Texture texture_play;

    if (!texture_play.loadFromFile("../../images/doodle_main.png")) exit(1);
    background_play.setTexture(&texture_play);

    while (Play.isOpen())
    {
        Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) { Play.close(); }
            }
        }
        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}


void Options() // Функция настройки игры
{
    RenderWindow Options(VideoMode::getDesktopMode(), L"Настройки", Style::Fullscreen);
    RectangleShape background_opt(Vector2f(1920, 1080));
    Texture texture_opt;

    if (!texture_opt.loadFromFile("../../images/doodle_main.png")) exit(2);
    background_opt.setTexture(&texture_opt);

    while (Options.isOpen())
    {
        Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            // if (event_opt.type == Event::Closed) Options.close(); // Переходит в главное меню по нажатию alt + f4
            if (event_opt.type == Event::KeyPressed)
            {
                if (event_opt.key.code == Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}


void About_Game() // Функция с описанием игры
{
    RenderWindow About(VideoMode::getDesktopMode(), L"О игре", Style::Fullscreen);
    RectangleShape background_ab(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture texture_ab;

    if (!texture_ab.loadFromFile("../../images/doodle_main.png")) exit(3);
    background_ab.setTexture(&texture_ab);
    
    while (About.isOpen())
    {
        Event event_play;
        while (About.pollEvent(event_play))
        {
            // if (event_play.type == Event::Closed) About.close();  // Переходит в главное меню по нажатию alt + f4
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.display();
    }
}


int main()
{
    setlocale(LC_ALL, "Rus");

    RenderWindow window;  // Создаём окно 
    window.create(VideoMode::getDesktopMode(), L"Doodle Jump", Style::Fullscreen);

    // window.setMouseCursorVisible(false);                    //отключаем видимость курсора

    float width = VideoMode::getDesktopMode().width;        // получение текущего размера экрана
    float height = VideoMode::getDesktopMode().height;
    
    RectangleShape background(Vector2f(width, height));     // Создание прямоугольника
    Texture texture_window;

    if (!texture_window.loadFromFile("../../images/doodle_main.png")) exit(2); // Установка фона главного меню
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(3);           // Установка шрифта главного меню
    Text Titul;
    Titul.setFont(font);
    
    InitText(Titul, 350, 50, L"Doodle Jump", 150, Color(237, 147, 0), 3);      // Текст с названием игры
    String name_menu[]{ L"GameStart", L"Options", L"About Game", L"Exit"};     // Название пунктов меню

    int left_pos = 150, top_pos = 350, step_pos = 150;
    game::StartMenu mymenu(window, left_pos, top_pos, step_pos, 4, name_menu, 100); // Объект игровое меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);          // Установка цвета элементов пунктов меню
    mymenu.AlignMenu(3);                                                            // выравнивание по левому краю пунктов меню 
            
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (IntRect(mymenu.mainMenu[0].getPosition().x, mymenu.mainMenu[0].getPosition().y, mymenu.mainMenu[0].getLocalBounds().width,
             mymenu.mainMenu[0].getLocalBounds().height + mymenu.mainMenu[0].getCharacterSize()/3).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(0);}
            
		    else if (IntRect(mymenu.mainMenu[1].getPosition().x, mymenu.mainMenu[1].getPosition().y, mymenu.mainMenu[1].getLocalBounds().width,
             mymenu.mainMenu[1].getLocalBounds().height  + mymenu.mainMenu[1].getCharacterSize()/3).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(1);}
            
		    else if (IntRect(mymenu.mainMenu[2].getPosition().x, mymenu.mainMenu[2].getPosition().y, mymenu.mainMenu[2].getLocalBounds().width,
             mymenu.mainMenu[2].getLocalBounds().height  + mymenu.mainMenu[2].getCharacterSize()/3).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(2);}
            
            else if (IntRect(mymenu.mainMenu[3].getPosition().x, mymenu.mainMenu[3].getPosition().y, mymenu.mainMenu[3].getLocalBounds().width,
             mymenu.mainMenu[3].getLocalBounds().height + mymenu.mainMenu[3].getCharacterSize()/3).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(3);}

            else if (event.type == Event::KeyReleased) // События выбора пунктов меню
            {
                // if (event.key.code == Keyboard::Escape) { window.close(); }
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }        // Нажатие на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }    // Нажатие на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Return)                         // Нажатие на клавиатуре клавиши Enter                     
                {
                    switch (mymenu.getSelectedMenuNumber())                     // Переход на выбранный пункт меню
                    {
                    case 0:GameStart();   break;
                    case 1:Options();     break;
                    case 2:About_Game();  break;
                    case 3:window.close(); break;
                    }
                }
            }

		    if (Mouse::isButtonPressed(Mouse::Left))
		    {
			    if (mymenu.mainMenuSelected == 0) {GameStart(); break;}
			    if (mymenu.mainMenuSelected == 1) {Options(); break;}
			    if (mymenu.mainMenuSelected == 2) {About_Game(); break;}
                if (mymenu.mainMenuSelected == 3) {window.close(); break;}
		    }
        }
        // std::cout << float(mymenu.mainMenu[0].getLocalBounds().height);
        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    
    return 0;
}


