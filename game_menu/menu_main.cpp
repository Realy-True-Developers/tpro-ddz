#include "game_menu.hpp"


int main()
{
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Doodle Jump", Style::Fullscreen);
    window.setFramerateLimit(60);

    MenuStart(window, 0);

    return 0;
}