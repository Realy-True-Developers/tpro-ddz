/*!
\file
\brief Файл с реализацией функций отрисовки всех окон различных меню

Данный файл содержит в себе реализацию методов,
 используемых в программе для отрисовки окон меню, таких как
 главное меню, меню настроек, диалогового окна при выходе из игры,
 меню настроек игрового процесса
*/


#include "game_menu.hpp"

/*!
* \brief Отрисовка главного меню игры.
* Функция рисует главное меню, позволяет переходить к другим пунктам как мышью, так и клавиатурой
* \param[in] window Окно, которое выводится на экран. Передаётся по адресу
* \param[in] start_menu_point Изначально выбранный пункт меню
*/
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

/*!
* \brief Отрисовка меню настроек игрового процесса.
* Функция рисует меню ,позволяющее выбирать количество ботов в игре (с возможностью выбрать 0, т.е. режим тренировки) и количество раундов
* \param[in] window Окно, которое выводится на экран. Передаётся по адресу
*/
void GameStart(RenderWindow& window)
{
    RectangleShape background_play(Vector2f(1920, 1080));
    Texture texture_play;

    if (!texture_play.loadFromFile("../../images/2+.jpg")) exit(1);
    background_play.setTexture(&texture_play);

	Font font;    
	if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(3);
	
	/*-------------------------------------------------------------------------------------------------------*/

	Text rounds_text, count_bots_text;
	rounds_text.setFont(font); count_bots_text.setFont(font);

	Color gamestart_text_color = Color(119,144,145);
	Color color_border = Color::Color(215, 189, 158), outline_color_border = Color(167, 147, 123);
	Color play_color = Color::Blue, exit_color = Color(119,144,145);
	Color chosen_color = Color(192, 154, 76);
	Color input_color = Color::Red;

	int max_rounds = 13, max_bots = 3;

	int pos_y = 100, step = 200, pos_x_rounds = 500, pos_x_bots = 100;

	FillText(rounds_text, pos_x_rounds, pos_y, "Rounds", 100, gamestart_text_color, 1);
	FillText(count_bots_text, pos_x_bots, pos_y + 350, "Count bots", 100, gamestart_text_color, 1);

	int pos_x_move_rounds = rounds_text.getLocalBounds().width + 300;
	int pos_x_move_bots = count_bots_text.getLocalBounds().width + 300;
	int len_rounds = 200, triangle_width = 50, triangle_height = 90;

	ConvexShape* triangle = new ConvexShape[4];
	for (size_t i = 0; i < 4; ++i)
	{triangle[i].setPointCount(3); triangle[i].setFillColor(color_border);}
	triangle[0].setPoint(0, Vector2f(pos_x_rounds + pos_x_move_rounds + triangle_width * 2, rounds_text.getPosition().y + 20));
	triangle[0].setPoint(1, Vector2f(pos_x_rounds + pos_x_move_rounds + triangle_width, rounds_text.getPosition().y + triangle_height/2 + 20));
	triangle[0].setPoint(2, Vector2f(pos_x_rounds + pos_x_move_rounds + triangle_width * 2, rounds_text.getPosition().y + triangle_height + 20));
	triangle[0].setOutlineThickness(1); triangle[0].setOutlineColor(outline_color_border);

	triangle[1].setPoint(0, Vector2f(len_rounds + pos_x_rounds + pos_x_move_rounds + triangle_width * 3, rounds_text.getPosition().y + triangle_height/2 + 20));
	triangle[1].setPoint(1, Vector2f(len_rounds + pos_x_rounds + pos_x_move_rounds + triangle_width * 2, rounds_text.getPosition().y + 20));
	triangle[1].setPoint(2, Vector2f(len_rounds + pos_x_rounds + pos_x_move_rounds + triangle_width * 2, rounds_text.getPosition().y + triangle_height + 20));
	triangle[1].setOutlineThickness(1); triangle[1].setOutlineColor(outline_color_border);

	triangle[2].setPoint(0,Vector2f(pos_x_bots + pos_x_move_bots + triangle_width * 2, count_bots_text.getPosition().y + 20));
	triangle[2].setPoint(1,Vector2f(pos_x_bots + pos_x_move_bots + triangle_width, count_bots_text.getPosition().y + triangle_height/2 + 20));
	triangle[2].setPoint(2,Vector2f(pos_x_bots + pos_x_move_bots + triangle_width * 2, count_bots_text.getPosition().y + triangle_height + 20));
	triangle[2].setOutlineThickness(1); triangle[2].setOutlineColor(outline_color_border);

	triangle[3].setPoint(0,Vector2f(len_rounds + pos_x_bots + pos_x_move_bots + triangle_width * 3, count_bots_text.getPosition().y + triangle_height/2 + 20));
	triangle[3].setPoint(1,Vector2f(len_rounds + pos_x_bots + pos_x_move_bots + triangle_width * 2, count_bots_text.getPosition().y + 20));
	triangle[3].setPoint(2,Vector2f(len_rounds + pos_x_bots + pos_x_move_bots + triangle_width * 2, count_bots_text.getPosition().y + triangle_height + 20));
	triangle[3].setOutlineThickness(1); triangle[3].setOutlineColor(outline_color_border);
	
	Text exit, play;
	exit.setFont(font); play.setFont(font);

	int pos_y_exit = VideoMode::getDesktopMode().height - 300;

	FillText(exit, pos_x_bots, pos_y_exit + 30, "Exit", 150, exit_color, 1);
	FillText(play, VideoMode::getDesktopMode().width - 500, pos_y_exit, "Play", 200, play_color, 1);

	Text rounds, bots;
	rounds.setFont(font); bots.setFont(font);

	FillText(rounds, 0, 0, "1", 100, input_color, 1);
	FillText(bots, 0, 0, "1", 100, input_color, 1);

	int pos_x_rounds_input = triangle[0].getLocalBounds().left + (triangle[1].getLocalBounds().left - triangle[0].getLocalBounds().left)/2 - rounds.getLocalBounds().width/2 + triangle_width*0.5;
	int pos_x_bots_input = triangle[2].getLocalBounds().left + (triangle[3].getLocalBounds().left - triangle[2].getLocalBounds().left)/2 - bots.getLocalBounds().width/2 + triangle_width*0.5;

	rounds.setPosition(pos_x_rounds_input, triangle[0].getLocalBounds().top - 15);
	bots.setPosition(pos_x_bots_input, triangle[2].getLocalBounds().top - 15);

	int rounds_input = 1, bots_input = 1;

	/*-------------------------------------------------------------------------------------------------------*/

	int GameStartSelected = 0;

    while (window.isOpen())
    {
        Event event_play;
        while (window.pollEvent(event_play))
        {
            if (event_play.type == Event::KeyPressed)
            {
				if (event_play.key.code == Keyboard::F4) { window.close(); }
                if (event_play.key.code == Keyboard::Escape) {sleep(milliseconds(300)); MenuStart(window, 0); return;}
				if (event_play.type == Event::Closed) window.close();
            }


			if(IntRect(triangle[0].getLocalBounds()).contains(Mouse::getPosition(window))) {GameStartSelected = 0;}
			else if(IntRect(triangle[1].getLocalBounds()).contains(Mouse::getPosition(window))) {GameStartSelected = 1;}
			else if(IntRect(triangle[2].getLocalBounds()).contains(Mouse::getPosition(window))) {GameStartSelected = 2;}
		    else if(IntRect(triangle[3].getLocalBounds()).contains(Mouse::getPosition(window))) {GameStartSelected = 3;}
			else if(IntRect(exit.getPosition().x, exit.getPosition().y, exit.getLocalBounds().width,
             exit.getLocalBounds().height + exit.getCharacterSize()/4).contains(Mouse::getPosition(window))) {GameStartSelected = 4;}
			else if(IntRect(play.getPosition().x, play.getPosition().y, play.getLocalBounds().width,
             play.getLocalBounds().height + play.getCharacterSize()/4).contains(Mouse::getPosition(window))) {GameStartSelected = 5;}

			else if (event_play.type == Event::KeyPressed)
            {
				if(event_play.key.code == Keyboard::Up)
				{ switch (GameStartSelected)
					{case 0: GameStartSelected = 5; break; case 1: GameStartSelected = 5; break; case 2: GameStartSelected = 0; break;
					 case 3: GameStartSelected = 1; break; case 4: GameStartSelected = 2; break; case 5: GameStartSelected = 3; break;} }
				if(event_play.key.code == Keyboard::Down)
				{ switch (GameStartSelected)
					{case 0: GameStartSelected = 2; break; case 1: GameStartSelected = 3; break; case 2: GameStartSelected = 5; break;
					 case 3: GameStartSelected = 5; break; case 4: GameStartSelected = 0; break; case 5: GameStartSelected = 0; break;} }
				if(event_play.key.code == Keyboard::Right){++GameStartSelected %= 6;}
				if(event_play.key.code == Keyboard::Left){--GameStartSelected %= 6;}
            }

			if (GameStartSelected == 0)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (rounds_input > 1)
						{--rounds_input;}
					else
						{}
				}
				rounds.setString(std::to_string(rounds_input));
				pos_x_rounds_input = triangle[0].getLocalBounds().left+(triangle[1].getLocalBounds().left-triangle[0].getLocalBounds().left)/2-rounds.getLocalBounds().width/2+triangle_width*0.5;
				rounds.setPosition(pos_x_rounds_input, triangle[0].getLocalBounds().top - 15);
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(exit_color);
				triangle[0].setFillColor(chosen_color); play.setFillColor(play_color);
			}
			else if (GameStartSelected == 1)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (rounds_input == max_rounds)
						{}
					else
						++rounds_input;
				}
				rounds.setString(std::to_string(rounds_input));
				pos_x_rounds_input = triangle[0].getLocalBounds().left+(triangle[1].getLocalBounds().left-triangle[0].getLocalBounds().left)/2-rounds.getLocalBounds().width/2+triangle_width*0.5;
				rounds.setPosition(pos_x_rounds_input, triangle[0].getLocalBounds().top - 15);
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(exit_color);
				triangle[1].setFillColor(chosen_color); play.setFillColor(play_color);
			}
			else if(GameStartSelected == 2)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (bots_input > 0)
						{--bots_input;}
					else
						{}
				}
				bots.setString(std::to_string(bots_input));
				pos_x_bots_input = triangle[2].getLocalBounds().left+(triangle[3].getLocalBounds().left-triangle[2].getLocalBounds().left)/2-bots.getLocalBounds().width/2+triangle_width*0.5;
				bots.setPosition(pos_x_bots_input, triangle[2].getLocalBounds().top - 15);
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(exit_color);
				triangle[2].setFillColor(chosen_color); play.setFillColor(play_color);
			}
			else if (GameStartSelected == 3)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					if (bots_input == max_bots)
						{}
					else
						++bots_input;
				}
				bots.setString(std::to_string(bots_input));
				pos_x_bots_input = triangle[2].getLocalBounds().left+(triangle[3].getLocalBounds().left-triangle[2].getLocalBounds().left)/2-bots.getLocalBounds().width/2+triangle_width*0.5;
				bots.setPosition(pos_x_bots_input, triangle[2].getLocalBounds().top - 15);;
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(exit_color);
				triangle[3].setFillColor(chosen_color); play.setFillColor(play_color);
			} else if (GameStartSelected == 4)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					sleep(milliseconds(300)); MenuStart(window, 0); return;
				}
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(chosen_color);
				play.setFillColor(play_color);
			} else if (GameStartSelected == 5)
			{
				if(event_play.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					sleep(milliseconds(300)); Play(window); return;
				}
				for (size_t i = 0; i < 4; ++i) {triangle[i].setFillColor(color_border);} exit.setFillColor(exit_color);
				play.setFillColor(chosen_color);
			}
        }
        window.clear();
        window.draw(background_play);
		window.draw(rounds_text); window.draw(count_bots_text);
		for (size_t i = 0; i < 4; ++i) {window.draw(triangle[i]);}
		window.draw(exit); window.draw(play);
		window.draw(rounds); window.draw(bots);
        window.display();
    }
}

/*!
* \brief Отрисовка меню настроек игры.
* Функция рисует меню настроек, позволяющее выбирать имя игрока, цвет дудла, клавишы для управления (движение вправо - влево),
* а также ширину игрового поля (узкое, стандартное или широкое). Указанные настройки можно выбрать для двух пользователей.
* Рекализована запись настроек в файл при нажатии кнопки "Save"
* \param[in] window Окно, которое выводится на экран. Передаётся по адресу
* \param[in] player_func_call Номер выбранного игрока (1 или 2)
*/
void Options(RenderWindow& window, int player_func_call)
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

	/*------------------------------------------------------------------------------------------------------------------------------------------*/

	Text* settings_desc_text = new Text[4];
	Text save;
	save.setFont(font);

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
			if (player_func_call == 1) 
				{players1.setFillColor(chosen_color); players2.setFillColor(color_players);}
			else if (player_func_call == 2)
				{players1.setFillColor(color_players); players2.setFillColor(chosen_color);}


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

				if (event_opt.key.code == Keyboard::Escape) {sleep(milliseconds(300)); MenuStart(window, 0); return;}
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
				chosen_player = player_func_call;
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
						else if (event_opt.text.unicode == 13) {}							// Нажатие enter
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
				chosen_player = player_func_call;
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
					sleep(milliseconds(300));
					MenuStart(window, 0);
					return;
				}
				for (size_t i = 0; i < 4; ++i) { border_name[i].setFillColor(color_border);
				manip_l[i].setFillColor(color_border);manip_r[i].setFillColor(color_border);triangle[i].setFillColor(color_border);}
				save.setFillColor(chosen_color);
			}

			field_size.setString(list_field_size.at(field_selected));
			chose_color.setFillColor(list_colors.at(color_selected)); 

			if(chosen_player == 1 && player_func_call == 2)
				{players1.setFillColor(chosen_color); players2.setFillColor(color_players);}
			else if (chosen_player == 2 && player_func_call == 1)
				{players2.setFillColor(chosen_color); players1.setFillColor(color_players);}

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
}

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

/*!
* \brief Диалоговое окно, появляющееся при нажатии кнопки выхода из игры.
* При нажатии кнопки "Exit" поялвяется диалоговое окно, с вопросом "Do you want exit?",
* на что пользователь может нажать (как с помощью клавиатуры, так и мышью) "Yes" или "No"
* \param[in] window Окно, которое выводится на экран. Передаётся по адресу
*/
void Exit(RenderWindow& window)
{
	Color buttons_color = Color::Black, buttons_chosen = Color::Red;

	int exit_width = 800, exit_height = 300;
	RectangleShape ExitShape;
	ExitShape.setPosition(Vector2f(VideoMode::getDesktopMode().width/2 - exit_width/2, VideoMode::getDesktopMode().height/2 - exit_height/2));
	ExitShape.setSize(Vector2f(exit_width, exit_height));
	ExitShape.setFillColor(Color(234, 203, 166));
	ExitShape.setOutlineThickness(5);
	ExitShape.setOutlineColor(Color(167, 147, 123));

	Font font;
    if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(3);

	Text exit_text("Do you want exit?", font, 75);
	exit_text.setFillColor(Color::Black);
	exit_text.setPosition(ExitShape.getPosition().x + (ExitShape.getLocalBounds().width - exit_text.getLocalBounds().width)/2, ExitShape.getPosition().y + 40);

	Text exit_yes("Yes", font, 65);
	exit_yes.setFillColor(buttons_color);
	exit_yes.setPosition(ExitShape.getPosition().x + 100,
	ExitShape.getPosition().y + ExitShape.getLocalBounds().height - exit_yes.getLocalBounds().height - 60);

	Text exit_no("No", font, 65);
	exit_no.setFillColor(buttons_chosen);
	exit_no.setPosition(ExitShape.getPosition().x + ExitShape.getLocalBounds().width - 200,
	ExitShape.getPosition().y + ExitShape.getLocalBounds().height - exit_no.getLocalBounds().height - 60);

	int exit_selected = 1;

	while (window.isOpen())
    {
        Event event_exit;
        while (window.pollEvent(event_exit))
        {
			if (event_exit.type == Event::KeyReleased)
            {
                if (event_exit.key.code == Keyboard::Escape) {MenuStart(window, 3); return;}
				if(event_exit.type == Event::Closed) window.close();
			}

			if(IntRect(exit_yes.getPosition().x, exit_yes.getPosition().y, exit_yes.getLocalBounds().width * 1.5,
             exit_yes.getLocalBounds().height + exit_yes.getCharacterSize()/3).contains(Mouse::getPosition(window)))
			{exit_selected = 0;}

			else if(IntRect(exit_no.getPosition().x, exit_no.getPosition().y, exit_no.getLocalBounds().width * 1.5,
             exit_no.getLocalBounds().height + exit_no.getCharacterSize()/3).contains(Mouse::getPosition(window)))
			{exit_selected = 1;}

			else if (event_exit.type == Event::KeyPressed)
            {
				if(event_exit.key.code == Keyboard::Right) ++exit_selected %=2;
				if(event_exit.key.code == Keyboard::Left) {if(exit_selected==0) exit_selected = 1; else --exit_selected %=2;}
            }

			if (exit_selected == 0)
			{
				if(event_exit.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					window.close();
				}
			} else if (exit_selected == 1)
			{
				if(event_exit.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left))
				{
					sleep(milliseconds(300));
					MenuStart(window, 3); return;
				}
			}

			if (exit_selected == 1)
				{exit_no.setFillColor(buttons_chosen); exit_yes.setFillColor(buttons_color);}
			else if (exit_selected == 0)
				{exit_no.setFillColor(buttons_color); exit_yes.setFillColor(buttons_chosen);}
		}
		window.draw(ExitShape);
		window.draw(exit_text); window.draw(exit_yes); window.draw(exit_no);
		window.display();
	}
}


void Play(RenderWindow& window)
{

}