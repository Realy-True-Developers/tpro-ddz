#include "game_menu.hpp"

using namespace sf;



void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color menu_text_color = Color::White, 
int bord = 0, Color border_color = Color::Black); // функция настройки текста


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
    setlocale(LC_ALL,"Rus");

    RenderWindow window;  // Создаём окно 
    window.create(VideoMode::getDesktopMode(), L"Doodle Jump", Style::Fullscreen);

    window.setMouseCursorVisible(false);                    //отключаем видимость курсора

    float width = VideoMode::getDesktopMode().width;        // получение текущего размера экрана
    float height = VideoMode::getDesktopMode().height;
    
    RectangleShape background(Vector2f(width, height));     // Создание прямоугольника
    Texture texture_window;

    if (!texture_window.loadFromFile("../../images/doodle_main.png")) exit(2); // Установка фона главного меню
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(3);             // Установка шрифта главного меню
    Text Titul;
    Titul.setFont(font);
    
    InitText(Titul, 350, 50, L"Doodle Jump", 150, Color(237, 147, 0), 3);   // Текст с названием игры

    String name_menu[]{ L"Играть", L"Настройки", L"Об игре", L"Выход"};     // Название пунктов меню
    game::StartMenu mymenu(window, 150, 350, 4, name_menu, 100, 120);       // Объект игровое меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);  // Установка цвета элементов пунктов меню
    mymenu.AlignMenu(3);                                                    // выравнивание по левому краю пунктов меню 
            
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased) // События выбра пунктов меню
            {
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
        }
        
        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    
    return 0;
}


void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color, int bord, Color border_color) // функция настройки текста
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}