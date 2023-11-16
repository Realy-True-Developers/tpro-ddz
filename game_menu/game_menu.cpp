#include "game_menu.hpp"


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


game::StartMenu::StartMenu(RenderWindow& window, float menu_x, float menu_y, int step, int max_point_menu, String name[], int board, Color borderColor, int start_menu_point, int sizeFont) // Конструктор
	:mywindow(window), menu_X(menu_x), menu_Y(menu_y), menu_Step(step), size_font(sizeFont), max_menu(max_point_menu), mainMenu(new Text[max_menu])
{
	if (!font.loadFromFile("../../fonts/doodle.ttf")) exit(1);	// Загрузка шрифта

	for (int i = 0, ypos = menu_Y; i < max_menu; ++i, ypos += menu_Step)
	{
		mainMenu[i].setFont(font);
		FillText(mainMenu[i], menu_X, ypos, name[i], size_font, menu_text_color, board, borderColor);
	}

	mainMenuSelected = start_menu_point;
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


//Функция получения данных из файла
//Порядок переменных: name, color, control_l, control_r, field_size
std::vector<std::string> GetSettings(const char* file)	
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