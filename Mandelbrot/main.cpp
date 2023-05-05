#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

int main()
{
    // Get desktop resolution and aspect ratio
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    float aspectRatio = static_cast<float>(desktop.height) / desktop.width;

    // Construct window
    sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Mandelbrot Set");

    // Construct complex plane
    ComplexPlane complexPlane(aspectRatio);

    // Construct font and text objects
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text("", font, 20);
    text.setPosition(10, 10);
    text.setFillColor(sf::Color::White);

    // Construct VertexArray
    const int pixelWidth = desktop.width;
    const int pixelHeight = desktop.height;
    sf::VertexArray vArray(sf::Points, pixelWidth * pixelHeight);
    for (int i = 0; i < pixelHeight; i++) {
        for (int j = 0; j < pixelWidth; j++) {
            vArray[j + i * pixelWidth].position = { (float)j,(float)i };
        }
    }

    // Initialize state variable to CALCULATING
    enum class State { CALCULATING, DISPLAYING };
    State state = State::CALCULATING;

    // Begin main loop
    while (window.isOpen())
    {
        // Handle Input segment
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f coord = window.mapPixelToCoords(pixelPos, complexPlane.getView());
                if (event.mouseButton.button == sf::Mouse::Right) {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(coord);
                    state = State::CALCULATING;
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(coord);
                    state = State::CALCULATING;
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f coord = window.mapPixelToCoords(pixelPos, complexPlane.getView());
                complexPlane.setMouseLocation(coord);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Update Scene segment
        if (state == State::CALCULATING) {
            for (int i = 0; i < pixelHeight; i++) {
                for (int j = 0; j < pixelWidth; j++) {
                    sf::Vector2f coord = window.mapPixelToCoords(sf::Vector2i(j, i), complexPlane.getView());
                    size_t count = complexPlane.countIterations(coord);
                    Uint8 r, g, b;
                    complexPlane.iterationsToRGB(count, r, g, b);
                    vArray[j + i * pixelWidth].color = sf::Color(r, g, b);
                }
            }
            complexPlane.loadText(text);
            state = State::DISPLAYING;
        }

        // Draw Scene segment
        window.clear();
        window.draw(vArray);
        window.draw(text);
        window.display();
    }
}