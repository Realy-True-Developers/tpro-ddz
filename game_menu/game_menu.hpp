#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;



namespace game 
{
	class StartMenu
	{
	public:
		float menu_X;				
		float menu_Y;				
		int menu_Step;          	
		int max_menu;           	// Количество пунктов меню
		int size_font;          	
		int mainMenuSelected;	 
		Font font;          		
		int OutlineThickness = 3;	// Толщина контура обводки текста

		
        Text* mainMenu;             // Динамический массив текстовых объектов названий пунктов меню
		Color menu_text_color = Color(237, 147, 0);		// Цвет пунктов меню
		Color chosen_text_color =  Color::Red;			// Цвет выбора пункта меню
		Color border_color = Color::Black;				// Цвет обводки текста пунктов меню

		RenderWindow& mywindow;

		StartMenu(RenderWindow& window, float menux, float menuy, int step, int max_point_menu, String name[], int sizeFont = 60); // Конструктор 
       
		~StartMenu() {delete[] mainMenu;}

		void draw();          // Отрисовка меню
		void MoveKeyUp();     // Перемещение выбора меню вверх
		void MoveKeyDown();   // Перемещение выбора меню вниз
		void setColorTextMenu(Color menColor, Color ChoColor, Color BordColor);  // Установка цвета элементов игрового меню
		void AlignMenu(int posx);   		// Выравнивание положения меню
		void MouseChosen(int chosen_point); // Выбор пункта меню мышкой
		int getSelectedMenuNumber() {return mainMenuSelected;} // Возвращает номер выбранного элемента меню
	};
}


void FillText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color text_color = Color::White, 
int bord = 0, Color border_color = Color::Black); // функция настройки текста


void About_Game();
void Options(RenderWindow& window); 	// Функция настройки игры
void GameStart();	// Функция запуска игры

int main();