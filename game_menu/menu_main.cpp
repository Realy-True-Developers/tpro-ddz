#include "game_menu.hpp"
#include <Windows.h>
using namespace sf;


int main()
{
    setlocale(LC_ALL, "Rus");

    RenderWindow window;  // Создаём окно 
    window.create(VideoMode::getDesktopMode(), L"Doodle Jump", Style::Fullscreen);
    RectangleShape background(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture texture_window;

    if (!texture_window.loadFromFile("../../images/1.jpg")) exit(2); // Установка фона главного меню
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(3);                  // Установка шрифта главного меню
    Text Titul;
    Titul.setFont(font);
    
    FillText(Titul, 300, 10, L"Doodle Jump", 200, Color(133,101,33), 3, Color(79,60,19));       // Текст с названием игры
    String name_menu[]{ L"Play", L"Options", L"About Game", L"Exit"};           // Название пунктов меню

    int left_pos = 170, top_pos = 300, step_pos = 180;
    Color borderColor = Color(83, 56, 0);
    game::StartMenu mymenu(window, left_pos, top_pos, step_pos, 4, name_menu, 2, borderColor, 110);  // Объект игровое меню
    mymenu.AlignMenu(3);                                                             // Выравнивание по левому краю пунктов меню 
            
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (IntRect(mymenu.mainMenu[0].getPosition().x, mymenu.mainMenu[0].getPosition().y, mymenu.mainMenu[0].getLocalBounds().width,
             mymenu.mainMenu[0].getLocalBounds().height + mymenu.mainMenu[0].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(0);}
            
		    else if (IntRect(mymenu.mainMenu[1].getPosition().x, mymenu.mainMenu[1].getPosition().y, mymenu.mainMenu[1].getLocalBounds().width,
             mymenu.mainMenu[1].getLocalBounds().height  + mymenu.mainMenu[1].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(1);}
            
		    else if (IntRect(mymenu.mainMenu[2].getPosition().x, mymenu.mainMenu[2].getPosition().y, mymenu.mainMenu[2].getLocalBounds().width,
             mymenu.mainMenu[2].getLocalBounds().height  + mymenu.mainMenu[2].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(2);}
            
            else if (IntRect(mymenu.mainMenu[3].getPosition().x, mymenu.mainMenu[3].getPosition().y, mymenu.mainMenu[3].getLocalBounds().width,
             mymenu.mainMenu[3].getLocalBounds().height + mymenu.mainMenu[3].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(3);}

            else if (event.type == Event::KeyReleased) // События выбора пунктов меню
            {
                if (event.key.code == Keyboard::Escape) { window.close(); }
                if (event.key.code == Keyboard::Up) { mymenu.MoveKeyUp(); }         // Нажатие на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Down) { mymenu.MoveKeyDown(); }     // Нажатие на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Enter)                             // Нажатие на клавиатуре клавиши Enter                     
                {
                    switch (mymenu.getSelectedMenuNumber())                         // Переход на выбранный пункт меню
                    {
                    case 0:GameStart(); break;
                    case 1:Options(window); break;
                    case 2:About_Game(); break;
                    case 3:window.close(); break;
                    }
                }
            }

		    if (Mouse::isButtonPressed(Mouse::Left))
		    {
			    if (mymenu.mainMenuSelected == 0) {GameStart(); break;}
			    if (mymenu.mainMenuSelected == 1) {Options(window); break;}
			    if (mymenu.mainMenuSelected == 2) {About_Game(); break;}
                if (mymenu.mainMenuSelected == 3) {window.close(); break;}
		    }
        }
        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    
    return 0;
}