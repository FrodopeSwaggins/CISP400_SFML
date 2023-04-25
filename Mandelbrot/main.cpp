#include "ComplexPlane.h"
#include <iostream>

int main()
{
    // rendering window and creating aspect ratio
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandelbrot Set", Style::Fullscreen);

    // initializing ComplexPlane object using the aspect ratio
    float ratio = resolution.x / resolution.y;
    ComplexPlane mandel(ratio);
    
    // hud and font initializers
    Text hud;
    Font font;

    // VertexArray initialized with 'Points' type
    VertexArray screen;
    screen.setPrimitiveType(Points);
    screen.resize(resolution.x * resolution.y);

    // enum class for game states
    enum class State { CALCULATING, DISPLAYING};
    State state = State::CALCULATING;

    // game loop. work in progress. can close window and thats it.
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        
    }
}

