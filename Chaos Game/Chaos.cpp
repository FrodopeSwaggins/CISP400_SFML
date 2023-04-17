// Chaos_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Eduardo and Jordan
//Need text to user, user inut, (4), vector/array to hold point, vm,while,draw,

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

int main()
{


    //Make window
    // removed fullscreen and reduced vm size to give managable window. can be added back later
    VideoMode vm(800, 600);
    RenderWindow window(vm, "Chaos Game!!!");

    //CREATE TEXT;
    Text text, dotText;

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(10, 10);
    text.setFillColor(Color::White);
    dotText = text;
    dotText.setPosition(10, 100);

    srand(time(0));

    int inputCounter = 0; //see how many clicks;
    int dotCounter = 0;
    // rando coords
    int x = rand() % (vm.height - 50) + 10;
    int y = rand() % (vm.width - 50) + 10;

    bool acceptInput = true;

    // base triangle with random square every launch
    Vector2f point1(vm.width / 2, 0);
    Vector2f point2(50, vm.height - 50);
    Vector2f point3(vm.width - 50, vm.height - 50);

    // creating random squares
    Clock c1;
    vector<RectangleShape> s;

    // the squares
    RectangleShape dota, dotb, dotc, dot;
    dota.setSize(Vector2f(5, 5));
    dota.setFillColor(Color::White);
    dotb = dota;
    dotc = dota;
    dot = dota;

    while (window.isOpen())
    {


        //HANDLE PLAYER INPUT--------ESC
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

        // statement which adds squares. number below can be adjusted for speed by adding extra 0s
        if (c1.getElapsedTime().asSeconds() > 0.1)
        {
            // num is used to pick between point 1, 2, or 3
            int num = rand() % 3;
            s.push_back(RectangleShape());
            s.back().setSize(Vector2f(1, 1));
            // statement that chooses where the square will be 0 is point1
            if (num == 0) {
                x = lerp(x, vm.width / 2, 0.5);
                y = lerp(y, 0, 0.5);
            }
            else if (num == 1) {
                x = lerp(x, 50, 0.5);
                y = lerp(y, vm.height - 50, 0.5);
            }
            else if (num == 2) {
                x = lerp(x, vm.width - 50, 0.5);
                y = lerp(y, vm.height - 50, 0.5);;
            }
            s.back().setPosition(x, y);
            c1.restart();
        }
        /***************************************************************************
        * First three inputs
        ***************************************************************************/
        // triangle
        dota.setPosition(point1);
        dotb.setPosition(point2);
        dotc.setPosition(point3);
        /***************************************************************************
         last input
         ***************************************************************************/
      








        if (event.type == Event::MouseButtonReleased)//makes it so theres no 100 clicks per second
        {
            acceptInput = true;
        }

        //Output text;
        if (inputCounter < 4)
        {
            text.setString("Welcome to Chaos Game!!! \n   Choose 3 points for triangle");
        }
        if (inputCounter == 3)
        {
            text.setString("Select 4th point to start!");
        }

        stringstream ss;
        ss << "Dot counter: " << dotCounter;
        dotText.setString(ss.str());





        //draw
        window.clear();
        // took these out to see triangle
        //window.draw(text);
        //window.draw(dotText);
        window.draw(dota);
        window.draw(dotb);
        window.draw(dotc);
        // loop to draw the squares added to vector
        for (int i = 0; i < s.size(); i++) {
            window.draw(s[i]);
        }
        window.display();


    }
}
