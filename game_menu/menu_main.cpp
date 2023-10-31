#include "game_menu.hpp"

using namespace sf;

// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, 
    Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

// Функция перехода к игре
void GameStart()
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

// Функция настройки игры
void Options()
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
            if (event_opt.type == Event::Closed) Options.close();
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

// Функция с описанием игры
void About_Game()
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
            if (event_play.type == Event::Closed) About.close();
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
    
    // Создаём окно windows
    RenderWindow window;
    // Параметры: размер окна установить согласно текущему разрешению экрана
    // название моя игра, развернуть графическое окно на весь размер экрана
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);

    //отключаем видимость курсора
    window.setMouseCursorVisible(false); 

    // получаем текущий размер экрана
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // Устанавливаем фон для графического окна 
    // Создаём прямоугольник
    RectangleShape background(Vector2f(width, height));
    // Загружаем в прямоугольник текстуру с изображением sources/images/doodle_main.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile("../../images/doodle_main.png")) return 4;
    background.setTexture(&texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("C:/Works/tpro-ddz/fonts/troika.otf")) return 5;
    Text Titul;
    Titul.setFont(font);
     // Текст с названием игры
    InitText(Titul, 480, 50, L"Апокалипсис", 150, Color(237, 147, 0), 3);

    // Название пунктов меню
    String name_menu[]{ L"Старт",L"Настройки", L"О игре",L"Выход"};
    
    // Объект игровое меню
    game::StartMenu mymenu(window, 950, 350, 4, name_menu, 100, 120);
    // Установка цвета элементов пунктов меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // выравнивание по центру пунктов меню 
    mymenu.AlignMenu(2);
            
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                // События выбра пунктов меню
                // нажати на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }   
                // нажати на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }  
                // нажати на клавиатуре клавиши Enter
                if (event.key.code == Keyboard::Return)                       
                {
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber())
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

// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, 
    Color menu_text_color, int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}