/*!
\file
\brief Файл с реализацией функций для визуализации меню игры

Данный файл содержит в себе реализацию методов,
 используемых в программе для отрисовки объектов
*/


#include "game_menu.hpp"


 /*!
* \brief Выравнивание пунктов меню по левому краю, по правому краю по центру 
* \param[in] posx Основной параметр. 0 = выравниевание по правому краю. 1 = выравниевание по левому краю. 2 = по центру
* @return Функция является методом класса, ничего невозвращает, работает с самим объектом класса
*/
void game::StartMenu::AlignMenu(int posx)
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

 /*!
* \brief Конструктор класса StartMenu 
* \param[in] window Ркно, которое выводится на экран. Передаётся по адресу
* \param[in] menu_x Позииция текста от левого края экрана
* \param[in] menu_y Позииция текста от верхнего края экрана
* \param[in] step Шаг между пунктами меню
* \param[in] max_point_menu Максимальное количество пунктов меню
* \param[in] name Массив с названиями пунктов меню
* \param[in] board Тощина обводки текста
* \param[in] borderColor Цвет обводки текста
* \param[in] start_menu_point Изначально выбранный пункт меню
* \param[in] sizeFont Толщина шрифта
* @return Функция является методом класса, ничего невозвращает, работает с самим объектом класса
*/
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

 /*!
* \brief Перемещение на один пункт меню вниз клавишей 
*/
void game::StartMenu::MoveKeyDown()
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

 /*!
* \brief Перемещение на один пункт меню вверх клавишей 
*/
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

 /*!
* \brief Подсвечивание выбранного пункта меню
* \param[in] chosen_point Номер выбранного пункта
*/
void game::StartMenu::MouseChosen(int chosen_point)
{
	mainMenuSelected = chosen_point;  
	mainMenu[mainMenuSelected].setFillColor(chosen_text_color);		// Подсветка выбранного пункта меню
	for(int i = 0; i < max_menu; ++i)
	{
		if(i != mainMenuSelected)
			mainMenu[i].setFillColor(menu_text_color);				// Подсветка остальных пунктов меню
	}
}

 /*!
* \brief Метод класса StartMenu, отрисовка меню в окне
*/
void game::StartMenu::draw()
{
	for (int i = 0; i < max_menu; ++i) mywindow.draw(mainMenu[i]); 
}

 /*!
* \brief Установка цвета элементов меню
* \param[in] menColor Основной цвет меню
* \param[in] ChosenColor Цвет выбранного пункта меню
* \param[in] BordColor Цвет контура пунктов меню
*/
void game::StartMenu::setColorTextMenu(Color menColor, Color ChosenColor, Color BordColor)
{
	menu_text_color = menColor;   		
	chosen_text_color = ChosenColor;	
	border_color = BordColor;    		

	for (int i = 0; i < max_menu; ++i)
	{
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chosen_text_color);
}

 /*!
* \brief Функция настройки текста
* \param[in] mtext Объект пункта меню
* \param[in] xpos Расположение по x
* \param[in] ypos Расположение по y
* \param[in] str Текст пункта
* \param[in] size_font Толщина шрифта
* \param[in] text_color Цвет пункта
* \param[in] bord Толщина обводки текста
* \param[in] border_color Цвет контура текста
*/
void FillText(Text &mtext, float xpos, float ypos, String str, int size_font, Color text_color, int bord, Color border_color) // 
{
	mtext.setString(str);
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setFillColor(text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}

 /*!
* \brief Функция получения данных из файла, порядок переменных: name, color, control_l, control_r, field_size
* \param[in] file Название файла
* @return Функция возвращает вектор string данных, которые содержатся в файле
*/
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

/*!
* \brief Функция записи данных в файл, порядок переменных: name, color, control_l, control_r, field_size
* \param[in] file Название файла
* \param[in] bordesettingsr_color Вектор string с параметрами, которые необходимо записать в файл
*/
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

// int CountLinesInFile(std::string filename)
// {
//   	std::ifstream file(filename, std::ios::in);

// 	if (!file)
// 	{
// 		return -1;
// 	}
// 	int count = 0;
// 	char buffer[1000];

// 	while (!file.eof())
// 	{
// 		count++;
// 		file.getline(buffer, 1000);
// 	}

// 	file.close();
// 	return count;
// }

// int GetStringsFromFileS(std::string filename, std::string** _lines)
// {
// 	std::string* lines; 					// временный список строк
// 	int n = CountLinesInFile(filename); 	// Получить количество строк в файле

// 	if (n == -1) return -1;

// 	std::ifstream file(filename);
// 	if (!file) exit(404);

// 	try {
// 		lines = new std::string[n];
// 	}
// 	catch (std::bad_alloc e)
// 	{
// 		file.close(); return -2; // возврат с кодом -2
// 	}

// 	std::string line;
// 	std::string delim = ", ";

// 	for (int i = 0; i < n; i++)
// 	{
// 		file.getline(line, 1000);

// 		line.erase(0, line.find(delim) + delim.length());
// 		lines.push_back(lines);

// 		int len;
// 		for (len = 0; buffer[len] != '\0'; len++);

// 		lines[i].assign(buffer, len);
// 	}
// 	file.close();

// 	*_lines = lines;
// 	return n;
// }

// bool SetStringsToFileS(std::string filename, std::string* lines, int count)
// {
// 	std::ofstream file(filename);

// 	if (!file) return false;

// 	for (int i = 0; i < count - 1; i++)
// 		file << lines[i] << std::endl;

// 	file << lines[count - 1];

// 	file.close();
// 	return true;
// }

// bool SortStringsInFile(std::string filename)
// {
// 	int count;
// 	std::string* lines = nullptr;
// 	std::string s;

// 	count = GetStringsFromFileS(filename, &lines);
// 	if (count < 0) return false;

// 	for (int i = 0; i < count - 1; i++)
// 		for (int j = i; j >= 0; j--)
// 		if (lines[j] > lines[j + 1])
// 		{
// 			s = lines[j];
// 			lines[j] = lines[j + 1];
// 			lines[j + 1] = s;
// 		}

// 	bool res = SetStringsToFileS(filename, lines, count);

// 	if (lines != nullptr) delete[] lines;

// 	return res;
// }

/*!
* \brief Функция записи данных в файл, порядок переменных: name, color, control_l, control_r, field_size
* \param[in] file Название файла
* \param[in] bordesettingsr_color Вектор string с параметрами, которые необходимо записать в файл
*/
void SaveScore(const char* file, std::string name, int score)
{
    std::ofstream scoreFile(file);
    std::vector<std::string> lines; // Здесь хранятся строки файла

    if (!scoreFile) {
        std::cout << "Score file error" << std::endl;
    	exit(404);
    }

	scoreFile << name << ", " << score << std::endl;
    scoreFile.close();

    std::ifstream sortscoreFile(file);
    if (!sortscoreFile) {
        std::cout << "Score file error" << std::endl;
    	exit(404);
    }

	// std::string line;
    // while (std::getline(sortscoreFile, line)) {
    //     lines.push_back(line);
    // }
}