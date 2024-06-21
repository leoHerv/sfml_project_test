#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode{ 1920u, 1080u },
                                                "SFML Test project", sf::Style::Default, settings};
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(50, 50));
    //window.setVerticalSyncEnabled(true); Not supported.

    sf::Texture textureBird;
    if (!textureBird.loadFromFile("resources/bird.png"))
    {
        std::cout << "Error : load texture from 'resources/bird.png'" << std::endl;
    }
    textureBird.setSmooth(true);

    sf::Sprite spriteBird;
    spriteBird.setTexture(textureBird);

    sf::Font fontArial;
    if (!fontArial.loadFromFile("resources/ARIAL.TTF"))
    {
        std::cout << "Error : load font from 'resources/ARIAL.TTF'" << std::endl;
    }

    while (window.isOpen())
    {
        for (sf::Event event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // KeyPressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << event.key.scancode << std::endl;
                    std::cout << "code: " << event.key.code << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;
                    std::cout << "alt: " << event.key.alt << std::endl;
                    std::cout << "shift: " << event.key.shift << std::endl;
                    std::cout << "system: " << event.key.system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
                    std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
                }

                if (event.key.scancode == sf::Keyboard::Scan::Left)
                {
                    //spriteBird.move(sf::Vector2f(-5.f, 0.f));
                }
                if (event.key.scancode == sf::Keyboard::Scan::Right)
                {
                    //spriteBird.move(sf::Vector2f(5.f, 0.f));
                }
            }
            // MouseButtonPressed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                //std::cout << "Left" << std::endl;
                spriteBird.move(sf::Vector2f(-5.f, 0.f));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
                //std::cout << "Right" << std::endl;
                spriteBird.move(sf::Vector2f(5.f, 0.f));
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                std::cout << "mouse x: " << localPosition.x << std::endl;
                std::cout << "mouse y: " << localPosition.y << std::endl;
            }

            // Resized
            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

        } // End events.

        // Zoomed View.
        //sf::View view(sf::FloatRect(0.f, 0.f, 500.f, 500.f));
        //window.setView(view);

        // Clear the window in black.
        window.clear(sf::Color::Black);

        // What we want to draw.
        window.draw(spriteBird);

        sf::Text text;
        text.setFont(fontArial);
        text.setString("Hello World !");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(100.f, 100.f);

        window.draw(text);

        // Draw on the window.
        window.display();
    }
}
