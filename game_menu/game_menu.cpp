#include "game_menu.hpp"

// метод настройки текстовых объектов пунктов игрового меню
void game::StartMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos)
{
	text.setFont(font);                 // шрифт
	text.setFillColor(menu_text_color); // цвет 
	text.setString(str);                // текст
	text.setCharacterSize(size_font);   // размер шрифта
	text.setPosition(xpos, ypos);       // координаты текстового объекта
	text.setOutlineThickness(3);        // толщина контура обводки текста
	text.setOutlineColor(border_color); // цвет контура обводки текста
}
// Выравнивание пунктов меню по левому по правому по центру 
void game::StartMenu::AlignMenu(int posx)
{
	float nullx = 0;
	for (int i = 0; i < max_menu; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0; // выравнивание по правому краю от установленных координат
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;  // по левому краю
			break;
		case 2:
			nullx = nullx = mainMenu[i].getLocalBounds().width / 2;  // по центру
			break;
		}
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}

}
// Конструктор
game::StartMenu::StartMenu(sf::RenderWindow& window, float menux, float menuy, 
      int index, sf::String name[], int sizeFont, int step)
	:mywindow(window), menu_X(menux), menu_Y(menuy), size_font(sizeFont), menu_Step(step)
{
	// Загрузка шрифта
	if (!font.loadFromFile("C:/Works/tpro-ddz/fonts/troika.otf")) exit(32);
	max_menu = index; // Количество єлементов меню 
	mainMenu = new sf::Text[max_menu];     // Динамический массив пунктов меню
    // Выстраиваем элементы меню
	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step) setInitText(mainMenu[i], name[i], menu_X, ypos);
	mainMenuSelected = 0; // Задаём начальное положения выбраного пункта меню
    // цвет выбраного пункта меню
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}
// перемещение выбора меню вверх
void game::StartMenu::MoveUp()
{
	mainMenuSelected--;  
    // подсвечиваем выбранный пункт меню
	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(menu_text_color);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
}
// перемещение выбора меню вниз
void game::StartMenu::MoveDown()
{
	mainMenuSelected++;
// подсвечиваем выбранный пункт меню
	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
	else
	{
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}

}
// рисуем элементы меню в графическом окне
void game::StartMenu::draw()
{
  // перебираем для отрисовки существующие текстовые объекты пунктов меню 	
  for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}
// назначение цвета элементам пунктов меню
void game::StartMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	menu_text_color = menColor;   // цвет пунктов меню
	chose_text_color = ChoColor; // цвет выбраного пункта меню
	border_color = BordColor;    // цвет контура пунктов меню

	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}