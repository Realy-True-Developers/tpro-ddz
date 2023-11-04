#include "game_menu.hpp"

using namespace sf;



// void game::setFillText(Text& text, String str, float xpos, float ypos) // Настройка текстовых объектов игрового меню
// {
// 	text.setString(str);                // Текст
// 	text.setCharacterSize(size_font);   // Размер шрифта
// 	text.setFont(font);                 // Шрифт
// 	text.setPosition(xpos, ypos);       // Координаты текстового объекта
// 	text.setFillColor(menu_text_color); // Цвет пункта меню
// 	text.setOutlineColor(border_color);	// Цвет контура обводки текста
// }

// Нах оно надо, можно прописть это в main
void game::StartMenu::AlignMenu(int posx) // Выравнивание пунктов меню по левому по правому по центру 
{
	float nullx = 0;

	for (int i = 0; i < max_menu; ++i)
	{
		switch (posx)
		{
		case 0:
			nullx = 0;											// выравнивание по правому краю от установленных координат
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;  		// по левому краю
			break;
		case 2:
			nullx = mainMenu[i].getLocalBounds().width / 2;  	// по центру
			break;
		}
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}


game::StartMenu::StartMenu(RenderWindow& window, float menu_x, float menu_y, int step, int max_point_menu, String name[], int sizeFont) // Конструктор
	:mywindow(window), menu_X(menu_x), menu_Y(menu_y), menu_Step(step), size_font(sizeFont), max_menu(max_point_menu), mainMenu(new Text[max_menu])
{
	if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(1);	// Загрузка шрифта

	for (int i = 0, ypos = menu_Y; i < max_menu; ++i, ypos += menu_Step)
	{
		mainMenu[i].setFont(font);
		FillText(mainMenu[i], menu_X, ypos, name[i], size_font, menu_text_color);
	}

	mainMenuSelected = 0;											// Задаём начальное положения выбраного пункта меню
	mainMenu[mainMenuSelected].setFillColor(chosen_text_color); 	// Подсвечиваем выбранный пункт меню
}


void game::StartMenu::MoveKeyDown() // Перемещение выбора меню вниз
{
	mainMenuSelected++;
	if (mainMenuSelected < max_menu) 
	{
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);	// Устанавка стандартного цвета для предыдущего пункта
		mainMenu[mainMenuSelected].setFillColor(chosen_text_color); 	// Подсветка выбранного пункта меню
	}
	else
	{
		mainMenuSelected = 0;
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chosen_text_color);
	} 
}


void game::StartMenu::MoveKeyUp() // Перемещение выбора меню вверх
{
	mainMenuSelected--;  
	if (mainMenuSelected >= 0) 
	{
		mainMenu[mainMenuSelected].setFillColor(chosen_text_color);		// Подсветка выбранного пункта меню
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);	// Устанавка стандартного цвета для следующего пункта
	}
	else
	{
		mainMenuSelected = max_menu - 1;
		mainMenu[0].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chosen_text_color);
	}
}

void game::StartMenu::MouseChosen(int chosen_point) 				// Выбор пункта меню мышкой
{
	mainMenuSelected = chosen_point;  
	mainMenu[mainMenuSelected].setFillColor(chosen_text_color);		// Подсветка выбранного пункта меню
	for(int i = 0; i < max_menu; ++i)
	{
		if(i != mainMenuSelected)
			mainMenu[i].setFillColor(menu_text_color);				// Подсветка остальных пунктов меню
	}
}


void game::StartMenu::draw() // Отрисовка каждого объекта меню
{
	for (int i = 0; i < max_menu; ++i) mywindow.draw(mainMenu[i]); 
}


// void game::MenuSettings::draw() // Отрисовка каждого объекта меню
// {
// 	for (int i = 0; i < max_menu; ++i) mywindow.draw(settingsMenu[i]);
// }


void game::StartMenu::setColorTextMenu(Color menColor, Color ChosenColor, Color BordColor) // Установка цвета элементов меню
{
	menu_text_color = menColor;   		// Цвет пунктов меню
	chosen_text_color = ChosenColor;	// Цвет выбраного пункта меню
	border_color = BordColor;    		// Цвет контура пунктов меню

	for (int i = 0; i < max_menu; ++i)
	{
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chosen_text_color);
}


// game::MenuSettings::MenuSettings(RenderWindow& window, float menux, float menuy, int step, int max_point_menu, String name[], int sizeFont)
// 	:mywindow(window), menu_X(menux), menu_Y(menuy), menu_Step(step), size_font(sizeFont), max_menu(max_point_menu), settingsMenu(new Text[max_menu])
// {
// 	if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(1);	// Загрузка шрифта
	
// 	for (int i = 0, ypos = menu_Y; i < max_menu; ++i, ypos += menu_Step)
// 	{
// 		settingsMenu[i].setFont(font);
// 		FillText(settingsMenu[i], menu_X, ypos, name[i], size_font, menu_text_color);
// 	}

// 	MenuSettingsSelected = 0;												// Задаём начальное положения выбраного пункта меню
// 	settingsMenu[MenuSettingsSelected].setFillColor(chosen_text_color); 	// Подсвечиваем выбранный пункт меню
// }


void FillText(Text &mtext, float xpos, float ypos, String str, int size_font, Color text_color, int bord, Color border_color) // функция настройки текста
{
	mtext.setString(str);
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setFillColor(text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}


// void EnteringText(Text& text, float xpos, float ypos, int width, int height, String str, int size_font = 60, Color text_color = Color::White, 
// int bord = 1, Color border_color = Color::Black)
// {
// 	text.setString(str);
//     text.setCharacterSize(size_font);
//     text.setPosition(xpos, ypos);
//     text.setFillColor(text_color);
//     text.setOutlineThickness(bord);
//     text.setOutlineColor(border_color);
// }


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
    RenderWindow Options;
	Options.create(VideoMode::getDesktopMode(), L"Options", Style::Fullscreen);
    RectangleShape options_back(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture options_texture;

    if (!options_texture.loadFromFile("../../images/White.jpg")) exit(2);
    options_back.setTexture(&options_texture);

	Color options_text_color = Color::Blue;
	Color chosen_color = Color::Red;
	int options_text_size = 100;

	Font font;    
	if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(3);

	Text* settings_desc_text = new Text[4];
	Text exit, save;
	exit.setFont(font); save.setFont(font);

	String settings_text[]{L"Your name", L"Color", L"Manipulation", L"Game field"};

	
	float pos_y = 50, step = 200, pos_x = 50, exit_save_y = 900;

	//game::MenuSettings settings(Options, pos_x, pos_y, step, 4, settings_text, 100);

	for (int i = 0, ypos = pos_y; i < 4; ++i, ypos += step) 
	{
		settings_desc_text[i].setFont(font);
		FillText(settings_desc_text[i], pos_x, ypos, settings_text[i], options_text_size, options_text_color);
	}
	
	FillText(exit, pos_x, exit_save_y, L"Exit", 130, options_text_color);
	FillText(save, 1920 - 280 - pos_x, exit_save_y, L"Save", 130, options_text_color);
	
	Color color_border = Color::Color( 255,192,203);

	int board = 5, board_t_name = 65, len_board_name = 600, pos_x_board_name = 800;
	RectangleShape* border_name = new RectangleShape[4];
	border_name[0].setSize(Vector2f(len_board_name, board)), border_name[1].setSize(Vector2f(board, 95));
	border_name[2].setSize(Vector2f(len_board_name, board)), border_name[3].setSize(Vector2f(board, 95));
	border_name[0].setPosition(Vector2f(pos_x_board_name, board_t_name)), border_name[1].setPosition(Vector2f(pos_x_board_name + len_board_name, board_t_name));
	border_name[2].setPosition(Vector2f(pos_x_board_name, board_t_name+90)), border_name[3].setPosition(Vector2f(pos_x_board_name, board_t_name));
	for (size_t i = 0; i < 4; ++i) {border_name[i].setFillColor(color_border);}

	int triangle_width = 50, triangle_height = 90;
	ConvexShape* triangle = new ConvexShape[4];
	for (size_t i = 0; i < 4; ++i)
	{
		triangle[i].setPointCount(3); triangle[i].setFillColor(color_border);
		triangle[i].setPoint(0, Vector2f(pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + 20));
		triangle[i].setPoint(1, Vector2f(pos_x_board_name + triangle_width, settings_desc_text[1].getPosition().y + triangle_height/2 + 20));
		triangle[i].setPoint(2, Vector2f(pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + triangle_height + 20));
	}
	triangle[1].move(len_board_name - triangle_width * 4, 0); triangle[1].setPoint(1, Vector2f(pos_x_board_name + triangle_width * 3, settings_desc_text[1].getPosition().y + triangle_height/2 + 20));

	RectangleShape chose_color; chose_color.setSize(Vector2f(300, triangle_height)); chose_color.setFillColor(Color::Blue);
	chose_color.setPosition(triangle[0].getLocalBounds().getPosition().x + 100, triangle[0].getLocalBounds().getPosition().y);

	Text name, left, right, field_size;
	name.setFont(font); left.setFont(font); right.setFont(font); field_size.setFont(font);
	name.setCharacterSize(70); left.setCharacterSize(options_text_size); right.setCharacterSize(options_text_size); field_size.setCharacterSize(options_text_size);
	name.setFillColor(Color::Black); left.setFillColor(options_text_color); right.setFillColor(options_text_color); field_size.setFillColor(options_text_color);
	name.setString(L"Enter your name:"); left.setString(L"Left"); right.setString(L"Right"); field_size.setString(L"Normal");
	name.setPosition(pos_x + settings_desc_text[0].getLocalBounds().width+300-10, pos_y + board*4);
	left.setPosition(pos_x_board_name, settings_desc_text[2].getPosition().y);
	right.setPosition(pos_x_board_name + 350, settings_desc_text[2].getPosition().y);

	int len_board_manip = 95;
	RectangleShape* manip_l = new RectangleShape[4];
	manip_l[0].setSize(Vector2f(len_board_manip, board)), manip_l[1].setSize(Vector2f(board, len_board_manip));
	manip_l[2].setSize(Vector2f(len_board_manip, board)), manip_l[3].setSize(Vector2f(board, len_board_manip));
	manip_l[0].setPosition(Vector2f(left.getPosition().x + 200, settings_desc_text[2].getPosition().y + 20));
	manip_l[1].setPosition(Vector2f(left.getPosition().x + len_board_manip + 200, settings_desc_text[2].getPosition().y + 20));
	manip_l[2].setPosition(Vector2f(left.getPosition().x + 200, settings_desc_text[2].getPosition().y+90 + 20));
	manip_l[3].setPosition(Vector2f(left.getPosition().x + 200, settings_desc_text[2].getPosition().y + 20));
	for (size_t i = 0; i < 4; ++i) {manip_l[i].setFillColor(color_border);}
	
	RectangleShape* manip_r = new RectangleShape[4];
	manip_r[0].setSize(manip_l[0].getSize()), manip_r[1].setSize(manip_l[1].getSize());
	manip_r[2].setSize(manip_l[2].getSize()), manip_r[3].setSize(manip_l[3].getSize());
	manip_r[0].setPosition(manip_l[0].getPosition()); manip_r[1].setPosition(manip_l[1].getPosition());
	manip_r[2].setPosition(manip_l[2].getPosition()); manip_r[3].setPosition(manip_l[3].getPosition());
	for (size_t i = 0; i < 4; ++i) {manip_r[i].setFillColor(color_border);  manip_r[i].move(420, 0);}

	triangle[3].setPoint(1, Vector2f(pos_x_board_name + triangle_width * 3, settings_desc_text[1].getPosition().y + triangle_height/2 + 20));
	triangle[2].move(0, settings_desc_text[3].getPosition().y - settings_desc_text[1].getPosition().y);
	triangle[3].move(len_board_name - triangle_width * 4, settings_desc_text[3].getPosition().y - settings_desc_text[1].getPosition().y);

	field_size.setPosition(chose_color.getPosition().x - 10, chose_color.getPosition().y + settings_desc_text[3].getPosition().y - settings_desc_text[1].getPosition().y - 20);




	int OptionsMenuSelected = 0;
	std::string inputed_name;

    while (Options.isOpen())
    {
        Event event_opt;
        while (Options.pollEvent(event_opt))
        {
			if(OptionsMenuSelected == 0)
			{
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(chosen_color);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color);
				if (event_opt.type == sf::Event::TextEntered) {
					if (event_opt.text.unicode < 128) 
					{
						if (event_opt.text.unicode == 8 && inputed_name.size() > 0) { 		// Нажатие backspace
							inputed_name.erase(inputed_name.size() - 1);
						} else if (event_opt.text.unicode == 8){}
						else if (event_opt.text.unicode == 13) { 							// carriage return (enter)
							
						}
						else if(inputed_name.size()<13){
							inputed_name += static_cast<char>(event_opt.text.unicode);
						}
						// if (inputed_name.size() == 1) {name.setString("Enter your name:");}
						name.setString(inputed_name);
					}
				}
			}
			else if (OptionsMenuSelected == 1)
			{
				


				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color); triangle[0].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 2)
			{
				


				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color); triangle[1].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 3)
			{



				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(chosen_color);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color);
			} else if (OptionsMenuSelected == 4)
			{
				


				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(chosen_color);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color);
			} else if (OptionsMenuSelected == 5)
			{
				
				

				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color);triangle[2].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 6)
			{
				
				

				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(options_text_color);triangle[3].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 7)
			{
				
				

				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(chosen_color); save.setFillColor(options_text_color);
			} else if (OptionsMenuSelected == 8)
			{
				
				

				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				exit.setFillColor(options_text_color); save.setFillColor(chosen_color);
			}
			// if (IntRect(exit.getPosition().x, exit.getPosition().y, exit.getLocalBounds().width,
            //  exit.getLocalBounds().height + exit.getCharacterSize()/4).contains(Mouse::getPosition(Options))) { MouseChosen(0) }
            
		    // else if (IntRect(save.getPosition().x, save.getPosition().y, save.getLocalBounds().width,
            //  save.getLocalBounds().height + save.getCharacterSize()/4).contains(Mouse::getPosition(Options))) { MouseChosen(1) }

            // else if (event_opt.type == Event::KeyReleased) // События выбора пунктов меню
            // {
            //     if (event_opt.key.code == Keyboard::Escape) {  }
            //     if (event_opt.key.code == Keyboard::Left) {  }         // Нажатие на клавиатуре стрелки вверх
            //     if (event_opt.key.code == Keyboard::Right) {  }     // Нажатие на клавиатуре стрелки вниз
            //     if (event_opt.key.code == Keyboard::Enter)                             // Нажатие на клавиатуре клавиши Enter                     
            //     {
            //         switch (mymenu.getSelectedMenuNumber())                         // Переход на выбранный пункт меню
            //         {
            //         case 0:GameStart();   break;
            //         case 1:Options();     break;
            //         case 2:About_Game();  break;
            //         case 3:window.close(); break;
            //         }
            //     }
            // }

		    // if (Mouse::isButtonPressed(Mouse::Left))
		    // {
			//     if (mymenu.mainMenuSelected == 0) {GameStart(); break;}
			//     if (mymenu.mainMenuSelected == 1) {window.close(); Options(); break;}
			//     if (mymenu.mainMenuSelected == 2) {About_Game(); break;}
            //     if (mymenu.mainMenuSelected == 3) {window.close(); break;}
		    // }



            // if (event_opt.type == Event::Closed) Options.close(); // Переходит в главное меню по нажатию alt + f4
            if (event_opt.type == Event::KeyPressed)
            {
                if (event_opt.key.code == Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
		Options.draw(options_back);
		for (size_t i = 0; i < 4; ++i){Options.draw(settings_desc_text[i]);}
		//settings.draw();
		for (size_t i = 0; i < 4; ++i){Options.draw(border_name[i]);}
		Options.draw(name); Options.draw(left); Options.draw(right);
		for (size_t i = 0; i < 4; ++i){Options.draw(triangle[i]);}
		for (size_t i = 0; i < 4; ++i){Options.draw(manip_l[i]);}
		for (size_t i = 0; i < 4; ++i){Options.draw(manip_r[i]);}
		Options.draw(chose_color);
		Options.draw(field_size);
		Options.draw(exit);
		Options.draw(save);
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