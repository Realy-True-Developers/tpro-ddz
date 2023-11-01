#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;



namespace game 
{
	class StartMenu
	{
	public:
		float menu_X;				// Координаты меню по X
		float menu_Y;				// Координаты меню по Y
		int menu_Step;          	// Расстояние между пунктами меню
		int max_menu;           	// Максимальное количество пунктов меню
		int size_font;          	// Размер шрифта
		int mainMenuSelected;		// Номер текущего пункта меню 
		Font font;          		// Шрифт 
		int OutlineThickness = 3;	// Толщина контура обводки текста

		
        Text* mainMenu;             // Динамический массив текстовых объектов названий пунктов меню
		Color menu_text_color;		// Цвет пунктов меню
		Color chosen_text_color;	// Цвет выбора пункта меню
		Color border_color;			// Цвет обводки текста пунктов меню

		RenderWindow& mywindow;	// Ссылка на графическое окно

        // Параметры: ссылка на текстовый объект, текст, координаты текста
		void setInitText(Text& text, String str, float xpos, float ypos); // Настройка текста пунктов меню

        // Параметры: ссылка на графическое окно, координаты игрового меню по x и y
        // количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
		StartMenu(RenderWindow& window, float menux, float menuy, int index, String name[], int sizeFont = 60, int step = 80); // Конструктор 
       
		~StartMenu() {delete[] mainMenu;}

		void draw();       // Отрисовка меню

		void MoveUp();     // Перемещение выбора меню вверх

		void MoveDown();   // Перемещение выбора меню вниз
        
        
		void setColorTextMenu(Color menColor, Color ChoColor, Color BordColor);  // Установка цвета элементов игрового меню

		void AlignMenu(int posx);   // Выравнивание положения меню

		int getSelectedMenuNumber() {return mainMenuSelected;} // Возвращает номер выбранного элемента меню
	};
}