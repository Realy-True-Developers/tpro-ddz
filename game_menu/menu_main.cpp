#include "game_menu.hpp"


int main()
{
    RenderWindow window;  // Создаём окно 
    window.create(VideoMode::getDesktopMode(), L"Doodle Jump", Style::Fullscreen);
    window.setFramerateLimit(60);

    MenuStart(window, 0);

    return 0;
}


void MenuStart(RenderWindow& window, int start_menu_point)
{
    RectangleShape background(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture texture_window;
    
    if (!texture_window.loadFromFile("../../images/mainBackground.jpg")) exit(2); // Установка фона главного меню
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(3);                  // Установка шрифта главного меню
    Text Titul;
    Titul.setFont(font);
    
    FillText(Titul, 300, 10, L"Doodle Jump", 200, Color(133,101,33), 3, Color(79,60,19));       // Текст с названием игры
    String name_menu[]{ L"Play", L"Options", L"About Game", L"Exit"};                           // Название пунктов меню

    int left_pos = 170, top_pos = 300, step_pos = 180;
    Color borderColor = Color(83, 56, 0);
    game::StartMenu mymenu(window, left_pos, top_pos, step_pos, 4, name_menu, 2, borderColor, start_menu_point,  110);  // Объект игровое меню
    mymenu.AlignMenu(3);                                                                                                // Выравнивание по левому краю пунктов меню 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (IntRect(mymenu.mainMenu[0].getPosition().x, mymenu.mainMenu[0].getPosition().y, mymenu.mainMenu[0].getLocalBounds().width * 1.5,
             mymenu.mainMenu[0].getLocalBounds().height + mymenu.mainMenu[0].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(0);}
            
		    else if (IntRect(mymenu.mainMenu[1].getPosition().x, mymenu.mainMenu[1].getPosition().y, mymenu.mainMenu[1].getLocalBounds().width * 1.2,
             mymenu.mainMenu[1].getLocalBounds().height  + mymenu.mainMenu[1].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(1);}
            
		    else if (IntRect(mymenu.mainMenu[2].getPosition().x, mymenu.mainMenu[2].getPosition().y, mymenu.mainMenu[2].getLocalBounds().width,
             mymenu.mainMenu[2].getLocalBounds().height  + mymenu.mainMenu[2].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(2);}
            
            else if (IntRect(mymenu.mainMenu[3].getPosition().x, mymenu.mainMenu[3].getPosition().y, mymenu.mainMenu[3].getLocalBounds().width * 1.5,
             mymenu.mainMenu[3].getLocalBounds().height + mymenu.mainMenu[3].getCharacterSize()/4).contains(Mouse::getPosition(window))) {mymenu.MouseChosen(3);}

            if (event.type == Event::KeyReleased) // События выбора пунктов меню
            {
                if (event.key.code == Keyboard::F4) { window.close(); }         // Нажатие на клавиатуре клавиши Escape
                if (event.key.code == Keyboard::Up) { mymenu.MoveKeyUp(); }         // Нажатие на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Down) { mymenu.MoveKeyDown(); }     // Нажатие на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Enter)                              // Нажатие на клавиатуре клавиши Enter                     
                {
                    switch (mymenu.getSelectedMenuNumber())                         // Переход на выбранный пункт меню
                    {
                    case 0: sleep(milliseconds(300)); GameStart(window); return;
                    case 1: sleep(milliseconds(300)); Options(window, 1); return;
                    case 2: sleep(milliseconds(300)); About_Game(); return;
                    case 3: sleep(milliseconds(300)); Exit(window); return;
                    }
                }
            }

		    if (Mouse::isButtonPressed(Mouse::Left))
		    {
			    if (mymenu.mainMenuSelected == 0) {sleep(milliseconds(300)); GameStart(window); return;}
			    if (mymenu.mainMenuSelected == 1) {sleep(milliseconds(300)); Options(window, 1); return;}
			    if (mymenu.mainMenuSelected == 2) {sleep(milliseconds(300)); About_Game(); return;}
                if (mymenu.mainMenuSelected == 3) {sleep(milliseconds(300)); Exit(window); return;}
		    }
        }
        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
}