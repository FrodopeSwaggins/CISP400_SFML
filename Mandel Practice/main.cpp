#include <SFML/Graphics.hpp>
#include <complex>

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int MAX_ITERATIONS = 10;

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Set");

    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    std::complex<double> c;
    std::complex<double> z;

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            c = { (4.0 * x / WIDTH - 2.0), (4.0 * y / HEIGHT - 2.0) };
            z = 0;

            int i;
            for (i = 0; i < MAX_ITERATIONS && std::abs(z) <= 2; i++)
            {
                z = z * z + c;
            }

            if (i == MAX_ITERATIONS)
            {
                image.setPixel(x, y, sf::Color::White);
            }
            else
            {
                float color = static_cast<float>(i) / MAX_ITERATIONS;
                image.setPixel(x, y, sf::Color(255 * color, 255 * color, 255 * color));
            }
        }
    }

    texture.update(image);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}