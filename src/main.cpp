#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode{ 1920u, 1080u },
                                                "SFML Test project" };
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(50, 50));

    while (window.isOpen())
    {
        for (sf::Event event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
