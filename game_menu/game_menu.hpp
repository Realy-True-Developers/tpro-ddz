/*!
\file
\brief Заголовочный файл с описанием классов и функций

Данный файл содержит в себе определения основных 
классов и функций, используемых для реализации всех меню игры
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace sf;


namespace game 
{
	/*!
	\brief Класс, содержащий пункты основого меню.
	Класс реализует полную настройку текста меню, подсветку выбранного пункта меню
	*/
	class StartMenu
	{
	public:
		float menu_X;				
		float menu_Y;				
		int menu_Step;          	
		int max_menu;           	// Количество пунктов меню
		int size_font;          	
		int mainMenuSelected;	 	// Номер выбранного пункта меню
		Font font;          		
		int OutlineThickness = 3;	// Толщина контура обводки текста

        Text* mainMenu;             						// Динамический массив текстовых объектов названий пунктов меню
		Color menu_text_color = Color(102, 187, 19);		// Цвет пунктов меню
		Color chosen_text_color =  Color(103, 137, 139);	// Цвет выбора пункта меню
		Color border_color = Color::Black;					// Цвет обводки текста пунктов меню

		RenderWindow& mywindow;

		StartMenu(RenderWindow& window, float menux, float menuy, int step, int max_point_menu, String name[], int board, Color borderColor, int start_menu_point, int sizeFont); // Конструктор 
       
		~StartMenu() {delete[] mainMenu;}

		void draw();          													
		void MoveKeyUp();     													
		void MoveKeyDown();   													
		void setColorTextMenu(Color menColor, Color ChoColor, Color BordColor); 
		void AlignMenu(int posx);   											
		void MouseChosen(int chosen_point); 									
		int getSelectedMenuNumber() {return mainMenuSelected;} 
	};
}

// int CountLinesInFile(std::string filename);
// int GetStringsFromFileS(std::string filename, std::string** _lines);
// bool SetStringsToFileS(std::string filename, std::string* lines, int count);
// bool SortStringsInFile(std::string filename);

void FillText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color text_color = Color::White, 
int bord = 0, Color border_color = Color::Black); 

std::vector<std::string> GetSettings(const char* file);
void SaveSattings(const char* file, std::vector<std::string> settings);
void SaveScore(const char* file, std::string name, int score);

void MenuStart(RenderWindow& window, int start_menu_point);

void GameStart(RenderWindow& window);	
void Options(RenderWindow& window, int player_func_call = 1); 	
void About_Game();
void Exit(RenderWindow& Window);
void Play(RenderWindow& window);
void Pause(RenderWindow& window);