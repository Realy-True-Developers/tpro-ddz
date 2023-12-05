//#include "../game_menu/game_menu.hpp"
#include "../game_logic/game_logic.hpp"
using namespace std;



int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Game", sf::Style::Default, settings);

    play(window);
    
    return 0;
}