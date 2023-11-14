#include "game_menu.hpp"

using namespace sf;


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


game::StartMenu::StartMenu(RenderWindow& window, float menu_x, float menu_y, int step, int max_point_menu, String name[], int board, Color borderColor, int sizeFont) // Конструктор
	:mywindow(window), menu_X(menu_x), menu_Y(menu_y), menu_Step(step), size_font(sizeFont), max_menu(max_point_menu), mainMenu(new Text[max_menu])
{
	if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(1);	// Загрузка шрифта

	for (int i = 0, ypos = menu_Y; i < max_menu; ++i, ypos += menu_Step)
	{
		mainMenu[i].setFont(font);
		FillText(mainMenu[i], menu_X, ypos, name[i], size_font, menu_text_color, board, borderColor);
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


void FillText(Text &mtext, float xpos, float ypos, String str, int size_font, Color text_color, int bord, Color border_color) // функция настройки текста
{
	mtext.setString(str);
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setFillColor(text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}


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

std::vector<std::string> GetSettings(const char* file)	//Функция получения данных из файла
{
    std::ifstream configFile(file);

    if (!configFile) {
        std::cout << "Settings file error" << std::endl;
        exit(404);
    }

    std::string line;
	std::vector<std::string> settings;
	std::string delim = ": ", token;
    while (std::getline(configFile, line)) {
		line.erase(0, line.find(delim) + delim.length());
		settings.push_back(line);
    }

    configFile.close();

    return settings;
}

// Функция для сохранения настроек игры в файл
//Порядок переменных: name, color, control_l, control_r, field_size
void SaveSattings(const char* file, std::vector<std::string> settings)
{
    std::ifstream configFile(file);
    std::vector<std::string> lines; // Здесь хранятся строки файла

    if (!configFile) {
        std::cout << "Settings file error" << std::endl;
    	exit(404);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        lines.push_back(line);
    }
    configFile.close();

    std::ofstream newConfigFile(file);
    if (!newConfigFile) {
        std::cout << "Enable to open settings file" << std::endl;
    	exit(404);
    }

    for (const auto& line : lines) {
        if (line.find("Name: ") != std::string::npos) {
            newConfigFile << "Name: " << settings.at(0) <<std::endl;
        }
        else if(line.find("Color: ") != std::string::npos) {
            newConfigFile << "Color: " << settings.at(1) <<std::endl;
        }
		else if(line.find("Control_left: ") != std::string::npos) {
            newConfigFile << "Control_left: " << settings.at(2) <<std::endl;
        }
		else if(line.find("Control_right: ") != std::string::npos) {
            newConfigFile << "Control_right: " << settings.at(3) <<std::endl;
        }
		else if(line.find("Field_size: ") != std::string::npos) {
            newConfigFile << "Field_size: " << settings.at(4) <<std::endl;
        }
    }

    newConfigFile.close();
}


void Options(RenderWindow& window, int player_func_call) // Функция настройки игры
{
    RectangleShape options_back(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture options_texture;

    if (!options_texture.loadFromFile("../../images/2.jpg")) exit(2);
    options_back.setTexture(&options_texture);

	Color options_text_color = Color(119,144,145);
	Color chosen_color = Color(192, 154, 76);
	int options_text_size = 110;

	Font font;    
	if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(3);

	Text* settings_desc_text = new Text[4];
	Text save;
	save.setFont(font);

	/*------------------------------------------------------------------------------------------------------------------------------------------*/

	String settings_text[]{L"Your name", L"Color", L"Control", L"Game field"}; 

	float pos_y = 150, step = 200, pos_x = 50, exit_save_y = 900;

	for (int i = 0, ypos = pos_y; i < 4; ++i, ypos += step) 
	{
		settings_desc_text[i].setFont(font);
		FillText(settings_desc_text[i], pos_x, ypos, settings_text[i], options_text_size, options_text_color, 1);
	}
	
	FillText(save, VideoMode::getDesktopMode().width - 850, exit_save_y, L"Save & Exit", 130, options_text_color);

	Color color_border = Color::Color(215, 189, 158), outline_color_border = Color(167, 147, 123);

	RectangleShape players1, players2;
	int border_players = 5, width_players = 400 + border_players * 3, height_players = 120;
	Color color_players = Color(234, 203, 166), chosen_color_players = Color(184, 160, 28);

	players1.setSize(Vector2f(width_players/2, height_players)); players2.setSize(Vector2f(width_players/2, height_players));
	players1.setPosition(Vector2f(VideoMode::getDesktopMode().width/2 - width_players/2, 0));
	players2.setPosition(Vector2f(VideoMode::getDesktopMode().width/2 + border_players, 0));
	players1.setFillColor(color_players); players2.setFillColor(color_players);
	players1.setOutlineThickness(border_players); players1.setOutlineColor(Color::Black);
	players2.setOutlineThickness(border_players); players2.setOutlineColor(Color::Black);

	Text p1, p2;
	Color p_color = Color::Black;
	p1.setFont(font); p2.setFont(font);
	FillText(p1, players1.getPosition().x + 50, 15, "P1", 70, p_color);
	FillText(p2, players2.getPosition().x + 50, 15, "P2", 70, p_color);

	int board = 5, board_t_name = 65, len_board_name = 600, pos_x_board_name = 1000, move_board = 15;
	RectangleShape* border_name = new RectangleShape[4];
	border_name[0].setSize(Vector2f(len_board_name, board)), border_name[1].setSize(Vector2f(board, 100));
	border_name[2].setSize(Vector2f(len_board_name, board)), border_name[3].setSize(Vector2f(board, 100));
	border_name[0].setPosition(Vector2f(pos_x_board_name,pos_y+board+move_board)), border_name[1].setPosition(Vector2f(pos_x_board_name+len_board_name,pos_y+board+move_board));
	border_name[2].setPosition(Vector2f(pos_x_board_name, pos_y+90 + board*2 + move_board)), border_name[3].setPosition(Vector2f(pos_x_board_name, pos_y + board + move_board));

	for (size_t i = 0; i < 4; ++i) {border_name[i].setFillColor(color_border);}
	int triangle_width = 50, triangle_height = 90;

	ConvexShape* triangle = new ConvexShape[4];
	for (size_t i = 0; i < 4; ++i)
	{ triangle[i].setPointCount(3); triangle[i].setFillColor(color_border); }
	triangle[0].setPoint(0, Vector2f(pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + 20));
	triangle[0].setPoint(1, Vector2f(pos_x_board_name + triangle_width, settings_desc_text[1].getPosition().y + triangle_height/2 + 20));
	triangle[0].setPoint(2, Vector2f(pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + triangle_height + 20));
	triangle[0].setOutlineThickness(1); triangle[0].setOutlineColor(outline_color_border);
	
	int move_right_triangle = len_board_name - triangle_width * 4;

	triangle[1].setPoint(0, Vector2f(move_right_triangle + pos_x_board_name + triangle_width * 3, settings_desc_text[1].getPosition().y + triangle_height/2 + 20));
	triangle[1].setPoint(1, Vector2f(move_right_triangle + pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + 20));
	triangle[1].setPoint(2, Vector2f(move_right_triangle + pos_x_board_name + triangle_width * 2, settings_desc_text[1].getPosition().y + triangle_height + 20));
	triangle[1].setOutlineThickness(1); triangle[1].setOutlineColor(outline_color_border);

	RectangleShape chose_color; chose_color.setSize(Vector2f(300, triangle_height)); chose_color.setFillColor(Color::Blue);
	chose_color.setPosition(triangle[0].getLocalBounds().getPosition().x + 100, triangle[0].getLocalBounds().getPosition().y);

	Text name, left, right, field_size;
	name.setFont(font); left.setFont(font); right.setFont(font); field_size.setFont(font);
	name.setCharacterSize(60); left.setCharacterSize(80); right.setCharacterSize(80); field_size.setCharacterSize(80);
	name.setFillColor(Color::Black); left.setFillColor(options_text_color); right.setFillColor(options_text_color); field_size.setFillColor(options_text_color);
	name.setString(L"Enter your name"); left.setString(L"Left"); right.setString(L"Right");
	name.setPosition(pos_x_board_name + 30, pos_y + 30);
	left.setPosition(pos_x_board_name, settings_desc_text[2].getPosition().y + 20);
	right.setPosition(pos_x_board_name + 350, settings_desc_text[2].getPosition().y + 20);

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

	triangle[2].setPoint(0,Vector2f(pos_x_board_name+triangle_width,settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y+settings_desc_text[1].getPosition().y+triangle_height/2+20));
	triangle[2].setPoint(1,Vector2f(pos_x_board_name+triangle_width*2,settings_desc_text[1].getPosition().y+20+settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y));
	triangle[2].setPoint(2,Vector2f(pos_x_board_name+triangle_width*2,settings_desc_text[1].getPosition().y+triangle_height+20+settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y));
	triangle[2].setOutlineThickness(1); triangle[2].setOutlineColor(outline_color_border);

	triangle[3].setPoint(0,Vector2f(move_right_triangle+triangle_width*2+pos_x_board_name+triangle_width,settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y+settings_desc_text[1].getPosition().y+triangle_height/2+20));
	triangle[3].setPoint(1,Vector2f(move_right_triangle+pos_x_board_name+triangle_width*2,settings_desc_text[1].getPosition().y+20+settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y));
	triangle[3].setPoint(2,Vector2f(move_right_triangle+pos_x_board_name+triangle_width*2,settings_desc_text[1].getPosition().y+triangle_height+20+settings_desc_text[3].getPosition().y-settings_desc_text[1].getPosition().y));
	triangle[3].setOutlineThickness(1); triangle[3].setOutlineColor(outline_color_border);

	field_size.setPosition(chose_color.getPosition().x - 10, chose_color.getPosition().y + settings_desc_text[3].getPosition().y - settings_desc_text[1].getPosition().y);
	
	Color manip_color = Color::Green;

	Text key_left_text, key_right_text;
	key_left_text.setFont(font); key_right_text.setFont(font); key_left_text.setFillColor(manip_color); key_right_text.setFillColor(manip_color); 
	key_left_text.setCharacterSize(70); key_right_text.setCharacterSize(60);
	key_left_text.setString("A"); key_right_text.setString("D");
	key_left_text.setPosition(manip_l[3].getPosition().x + 20, manip_l[3].getPosition().y + 5);
	key_right_text.setPosition(manip_r[3].getPosition().x + 20, manip_r[3].getPosition().y + 5);


	/*------------------------------------------------------------------------------------------------------------------------------------------*/

	int chosen_player = player_func_call;

	std::vector<std::string> list_field_size{"Small", "Normal", "Large"};
	int field_selected = 1;

	std::vector<Color> list_colors{Color::Black, Color::Red, Color::Green, Color::Blue, Color::Yellow};
	int color_selected = 0;

	int OptionsMenuSelected = 0;
	std::string inputed_name, inputed_l, inputed_r;


    while (window.isOpen())
    {
        Event event_opt;
        while (window.pollEvent(event_opt))
        {
			if(IntRect(players1.getPosition().x, players1.getPosition().y, players1.getSize().x, players1.getSize().y).contains(Mouse::getPosition(window)))
			{OptionsMenuSelected = 0;}

			else if(IntRect(players2.getPosition().x,players2.getPosition().y, players2.getSize().x, players2.getSize().y).contains(Mouse::getPosition(window)))
			{OptionsMenuSelected = 1;}

			else if(IntRect(border_name[0].getPosition().x,border_name[0].getPosition().y,border_name[1].getPosition().x - border_name[3].getPosition().x,
			 border_name[2].getPosition().y - border_name[0].getPosition().y).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 2;}
            
		    else if(IntRect(triangle[0].getLocalBounds()).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 3;}
			else if(IntRect(triangle[1].getLocalBounds()).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 4;}

			else if(IntRect(manip_l[0].getPosition().x,manip_l[0].getPosition().y,manip_l[1].getPosition().x - manip_l[3].getPosition().x,
			 manip_l[2].getPosition().y - manip_l[0].getPosition().y).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 5;}

			else if(IntRect(manip_r[0].getPosition().x,manip_r[0].getPosition().y,manip_r[1].getPosition().x - manip_r[3].getPosition().x,
			 manip_r[2].getPosition().y - manip_r[0].getPosition().y).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 6;}

			else if(IntRect(triangle[2].getLocalBounds()).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 7;}
			else if(IntRect(triangle[3].getLocalBounds()).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 8;}	
			else if(IntRect(save.getPosition().x, save.getPosition().y, save.getLocalBounds().width,
             save.getLocalBounds().height + save.getCharacterSize()/4).contains(Mouse::getPosition(window))) {OptionsMenuSelected = 9;}

			else if (event_opt.type == Event::KeyPressed)
            {
				if(event_opt.key.code == Keyboard::Up)
				{ switch (OptionsMenuSelected)
					{case 2: OptionsMenuSelected=9; break; case 3: OptionsMenuSelected=2; break; case 4: OptionsMenuSelected=2; break;
					case 5: OptionsMenuSelected=3; break; case 6: OptionsMenuSelected=4; break; case 7: OptionsMenuSelected=5; break;
					case 8: OptionsMenuSelected=6; break; case 9: OptionsMenuSelected=7; break; case 0: OptionsMenuSelected=9; break;
					case 1: OptionsMenuSelected=9; break;} }
				if(event_opt.key.code == Keyboard::Down)
				{ switch (OptionsMenuSelected)
					{case 2: OptionsMenuSelected=3; break; case 3: OptionsMenuSelected=5; break; case 4: OptionsMenuSelected=6; break;
					case 5: OptionsMenuSelected=7; break; case 6: OptionsMenuSelected=8; break; case 7: OptionsMenuSelected=9; break;
					case 8: OptionsMenuSelected=9; break; case 9: OptionsMenuSelected=2; break; case 0: OptionsMenuSelected=2; break;
					case 1: OptionsMenuSelected=2; break;} }
				if(event_opt.key.code == Keyboard::Right){++OptionsMenuSelected %=10;}
				if(event_opt.key.code == Keyboard::Left){--OptionsMenuSelected %=10;}

				if (event_opt.key.code == Keyboard::Escape) window.close();
				if (event_opt.type == Event::Closed) window.close();
            }


			if (OptionsMenuSelected == 0)
			{
				chosen_player = 1;
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (chosen_player != player_func_call)
						Options(window, 1);
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);manip_l[i].setFillColor(color_border);
				manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);} save.setFillColor(options_text_color);
				triangle[0].setFillColor(color_border);
			}
			else if (OptionsMenuSelected == 1)
			{
				chosen_player = 2;
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (chosen_player != player_func_call)
						Options(window, 2);
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(options_text_color); triangle[0].setFillColor(color_border);
			}
			else if(OptionsMenuSelected == 2)
			{
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(chosen_color);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);
				triangle[i].setFillColor(color_border);} save.setFillColor(options_text_color); 
				if (event_opt.type == Event::TextEntered)
				{
					if (event_opt.text.unicode < 128) 
					{
						if (event_opt.text.unicode == 8 && inputed_name.size() > 0) { 		// Нажатие backspace
							inputed_name.erase(inputed_name.size() - 1);
						} else if (event_opt.text.unicode == 8) {}
						else if (event_opt.text.unicode == 13) {}							// carriage return (enter)	
						else if(name.getLocalBounds().width < len_board_name - 70) {
							inputed_name += static_cast<char>(event_opt.text.unicode);
						}
						name.setString(inputed_name);
						// if (inputed_name.size() == 1) {name.setString("Enter your name:");}
					}
				}
			}
			else if (OptionsMenuSelected == 3)
			{
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if(color_selected == 0) { color_selected = list_colors.size() - 1;}
					else {--color_selected;}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(options_text_color); triangle[0].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 4)
			{
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if(color_selected == list_colors.size() - 1) {color_selected = 0;}
					else {++color_selected;}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(options_text_color); triangle[1].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 5)
			{
				if (event_opt.type == Event::TextEntered) {
					if (event_opt.text.unicode == 8) {}			// Backspace
					else if (event_opt.text.unicode == 13) {} 	// Enter
					else if(event_opt.text.unicode < 128) {
						inputed_l = toupper(static_cast<char>(event_opt.text.unicode));
						if(inputed_l != key_right_text.getString())
							key_left_text.setString(inputed_l);
					}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(chosen_color); manip_r[i].setFillColor(color_border);
				triangle[i].setFillColor(color_border);} save.setFillColor(options_text_color); 
			} else if (OptionsMenuSelected == 6)
			{
				if (event_opt.type == Event::TextEntered) {
					if (event_opt.text.unicode == 8) {}			// Backspace
					else if (event_opt.text.unicode == 13) {} 	// Enter
					else if (event_opt.text.unicode < 128) {
						inputed_r = toupper(static_cast<char>(event_opt.text.unicode));
						if(inputed_r != key_left_text.getString())
							key_right_text.setString(inputed_r);
					}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(chosen_color);
				triangle[i].setFillColor(color_border);} save.setFillColor(options_text_color);
			} else if (OptionsMenuSelected == 7)
			{
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if(field_selected == 0) {}
					else {--field_selected;}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(options_text_color);triangle[2].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 8)
			{
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if(field_selected == list_field_size.size() - 1) {}
					else {++field_selected;}
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(options_text_color);triangle[3].setFillColor(chosen_color);
			} else if (OptionsMenuSelected == 9)
			{
				if(event_opt.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					std::string color = std::to_string(color_selected);
					std::vector<std::string> data_save;
					data_save.push_back(inputed_name); data_save.push_back(color); data_save.push_back(inputed_l);
					data_save.push_back(inputed_r); data_save.push_back(list_field_size.at(field_selected));
					if(chosen_player == 1)
					{
						SaveSattings("../../SystemFiles/settingsP1.cfg", data_save);
					} else {
						SaveSattings("../../SystemFiles/settingsP2.cfg", data_save);
					}
					
					MenuStart(window);
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(chosen_color);
			}

			field_size.setString(list_field_size.at(field_selected));
			chose_color.setFillColor(list_colors.at(color_selected));

			if (chosen_player == 1) 
				{players1.setFillColor(chosen_color); players2.setFillColor(color_players);}
			else if (chosen_player == 2)
				{players1.setFillColor(color_players); players2.setFillColor(chosen_color);}

        }
        window.clear();
		window.draw(options_back);
		for (size_t i = 0; i < 4; ++i)
		{
			window.draw(settings_desc_text[i]);window.draw(border_name[i]);
			window.draw(triangle[i]);window.draw(manip_l[i]);window.draw(manip_r[i]);
		}
		window.draw(players1); window.draw(players2);
		window.draw(p1); window.draw(p2);
		window.draw(name); window.draw(left); window.draw(right);
		window.draw(chose_color);
		window.draw(field_size);
		window.draw(key_left_text); window.draw(key_right_text); 
		window.draw(save);
        window.display();
    }
	
	// for(int i = 0; i < 5; ++i) std::cout << GetSettings("../../SystemFiles/settingsP1.cfg").at(i) << std::endl;
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

