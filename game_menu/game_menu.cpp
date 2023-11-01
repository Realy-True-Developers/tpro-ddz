#include "game_menu.hpp"

using namespace sf;



void game::StartMenu::setInitText(Text& text, String str, float xpos, float ypos) // Настройка текстовых объектов игрового меню
{
	text.setString(str);                // Текст
	text.setCharacterSize(size_font);   // Размер шрифта
	text.setFont(font);                 // Шрифт
	text.setPosition(xpos, ypos);       // Координаты текстового объекта
	text.setFillColor(menu_text_color); // Цвет 
	text.setOutlineColor(border_color); // Цвет контура обводки текста
}

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


game::StartMenu::StartMenu(RenderWindow& window, float menu_x, float menu_y, int max_point_menu, String name[], int sizeFont, int step) // Конструктор
	:mywindow(window), menu_X(menu_x), menu_Y(menu_y), size_font(sizeFont), menu_Step(step), max_menu(max_point_menu), mainMenu(new Text[max_menu])
{
	if (!font.loadFromFile("../../fonts/ArialRegular.ttf")) exit(1);	// Загрузка шрифта

	for (int i = 0,  ypos = menu_Y; i < max_menu; ++i, ypos += menu_Step) setInitText(mainMenu[i], name[i], menu_X, ypos); // Выстраивание элементов  меню
	
	mainMenuSelected = 0;											// Задаём начальное положения выбраного пункта меню
	mainMenu[mainMenuSelected].setFillColor(chosen_text_color); 	// Подсвечиваем выбранный пункт меню
}


void game::StartMenu::MoveDown() // Перемещение выбора меню вниз
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


void game::StartMenu::MoveUp() // Перемещение выбора меню вверх
{
	mainMenuSelected--;  
	if (mainMenuSelected >= 0) {
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