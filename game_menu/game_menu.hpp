#include <SFML/Graphics.hpp>

namespace game {

	class StartMenu
	{
	public:
		float menu_X;                   // Координаты меню по X
		float menu_Y;				    // Координаты меню по Y
		int menu_Step;                  // Расстояние между пунктами меню
		int max_menu;                   // Максимальное количество пунктов меню
		int size_font;                  // Размер шрифта
		int mainMenuSelected;           // Номер текущего пункта меню 
		sf::Font font;                  // Шрифт меню 
		// Динамический массив текстовых объектов названий пунктов меню
        sf::Text* mainMenu;             
		sf::Color menu_text_color = sf::Color::White;    // Цвет пунктов меню
		sf::Color chose_text_color = sf::Color::Yellow;  // Цвет выбора пункта меню
		sf::Color border_color = sf::Color::Black;       // Цвет обводки текста пунктов меню

		// Настройка текста пунктов меню
        // Параметры: ссылка на текстовый объект, текст, координаты текста
		void setInitText(sf::Text& text, sf::String str, float xpos, float ypos);
        // Ссылка на графическое окно
		sf::RenderWindow& mywindow;   	
	
		// Конструктор 
        // Параметры: ссылка на графическое окно, координаты игрового меню по x и y
        // количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
		StartMenu(sf::RenderWindow& window, float menux, float menuy, 
                 int index, sf::String name[], int sizeFont = 60, int step = 80);
       
		~StartMenu()
		{
			delete[] mainMenu;
		}

		void draw();        // Рисуем меню

		void MoveUp();     // Перемещение выбора меню вверх

		void MoveDown();   // Перемещение выбора меню вниз
        
        // Цвет элементов игрового меню
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, 
                              sf::Color BordColor);  

		void AlignMenu(int posx);   // Выравнивание положения меню

		int getSelectedMenuNumber() // Возвращает номер выбранного элемента меню
		{
			return mainMenuSelected;
		}
	};
}