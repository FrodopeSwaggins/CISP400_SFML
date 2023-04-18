// Chaos_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Eduardo and Jordan
//Need text to user, user inut, (4), vector/array to hold point, vm,while,draw,

#include <iostream>
#include <sstream>
#include <cstdlib>
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
    VideoMode vm(1000, 1000);
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

    int inputCounter = 0; //see how many clicks;
    int dotCounter = 0;

    //dots
    RectangleShape dot1, dot2, dot3, dot4, dot5, dot6;
    dot1.setSize(Vector2f(1, 1));
    dot1.setFillColor(Color::White);
    dot2 = dot1;
    dot3 = dot1;
    dot4 = dot1;
    dot5 = dot1;
    dot6 = dot1;
    vector<RectangleShape> dotList;
    int rng; //rng number

    //control input;
    bool acceptInput = true;


    Vector2f temp, temp2;

    //COLORS!!!//was experimentin with values, var does not == color
    Color red(255, 0, 0);
    Color blue(0, 0, 255);
    Color green(0, 255, 0);
    Color yellow(255, 255, 0);
    Color pink(255, 0, 255);


    while (window.isOpen())
    {
        //Coordinates
        int x, y;

        //TO CLOSE
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        //ESC TO CLOSE
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /***************************************************************************
        * First three inputs + 1 to start
        ***************************************************************************/

        if (acceptInput && dotCounter == 0)//For the first click, now need 2 more + 1;
        {
            if (event.type == Event::MouseButtonPressed)//CLICK
            {
                x = event.mouseButton.x;        //GET X
                y = event.mouseButton.y;        //GET Y
                dot1.setPosition(x, y);         //SET DOT X,Y
                inputCounter++;                 //INCREMENT
                dotCounter++;
                acceptInput = false;            //AVOID 100 MPH
            }
        }
        if (acceptInput && dotCounter == 1)        //AGAIN2
        {
            if (event.type == Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                dot2.setPosition(x, y);
                inputCounter++;
                dotCounter++;
                acceptInput = false;
            }
        }
        if (acceptInput && dotCounter == 2)         //AGAIN3
        {
            if (event.type == Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                dot3.setPosition(x, y);
                inputCounter++;
                dotCounter++;
                acceptInput = false;
            }
        }

        if (acceptInput && dotCounter == 3)         //AGAIN3
        {
            if (event.type == Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                dot4.setPosition(x, y);
                inputCounter++;
                dotCounter++;
                acceptInput = false;
            }
        }

        if (acceptInput && dotCounter == 4)         //AGAIN3
        {
            if (event.type == Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                dot5.setPosition(x, y);
                inputCounter++;
                dotCounter++;
                acceptInput = false;
            }
        }

        if (acceptInput && dotCounter == 5)         //AGAIN4 AND LAST
        {
            if (event.type == Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                dot6.setPosition(x, y);
                inputCounter++;
                dotCounter++;
                acceptInput = false;
                dotList.push_back(dot1);
                dotList.push_back(dot2);
                dotList.push_back(dot3);
                dotList.push_back(dot4);
                dotList.push_back(dot5);
                dotList.push_back(dot6);
            }
        }

        /***************************************************************************
                 Chaos part
         ***************************************************************************/
        if (dotCounter >= 6)
        {
            RectangleShape* ndot = new RectangleShape;          //MAKES NEW EA FRAME
            ndot->setSize(Vector2f(1, 1));
            //ndot->setFillColor(Color::White);
            rng = rand() % (5);                                 //RANDOM 0,1,2
            if (rng == 0)
            {
                ndot->setFillColor(pink);
                temp = dot1.getPosition();                      //GET FIRST DOT X AND Y
                temp2 = dotList.at(dotList.size() - 1).getPosition();//GET LAST DOT X AND Y
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);                                   //GET MIDPOINT^^/////////////
                ndot->setPosition(temp);                            //MIDPOINT IS NEW DOT, BACK AT THE LINE
                dotList.push_back(*ndot);
                dotCounter++;


            }
            else if (rng == 1)
            {
                ndot->setFillColor(blue);
                temp = dot2.getPosition();
                temp2 = dotList.at(dotList.size() - 1).getPosition();
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);
                ndot->setPosition(temp);
                dotList.push_back(*ndot);
                dotCounter++;

            }
            else if (rng == 2)
            {
                ndot->setFillColor(red);
                temp = dot3.getPosition();
                temp2 = dotList.at(dotList.size() - 1).getPosition();
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);
                ndot->setPosition(temp);
                dotList.push_back(*ndot);
                dotCounter++;

            }
            else if (rng == 3)
            {
                ndot->setFillColor(yellow);
                temp = dot4.getPosition();
                temp2 = dotList.at(dotList.size() - 1).getPosition();
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);
                ndot->setPosition(temp);
                dotList.push_back(*ndot);
                dotCounter++;

            }
            else if (rng == 4)
            {
                ndot->setFillColor(green);
                temp = dot5.getPosition();
                temp2 = dotList.at(dotList.size() - 1).getPosition();
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);
                ndot->setPosition(temp);
                dotList.push_back(*ndot);
                dotCounter++;

            }
            else
            {
                ndot->setFillColor(green);
                temp = dot6.getPosition();
                temp2 = dotList.at(dotList.size() - 1).getPosition();
                temp.x = lerp(temp.x, temp2.x, 0.33);                           ///////////////////////////
                temp.y = lerp(temp.y, temp2.y, 0.33);
                ndot->setPosition(temp);
                dotList.push_back(*ndot);
                dotCounter++;

            }
        }


        //makes it so theres no 100 clicks per second
        if (event.type == Event::MouseButtonReleased)
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
        window.draw(text);
        window.draw(dotText);
        for (int i = 5; i < dotList.size(); i++)      //NOTE i=3, case window already drawing dots1-4 down there
        {
            window.draw(dotList.at(i));
        }
        window.draw(dot1);
        window.draw(dot2);
        window.draw(dot3);
        window.draw(dot4);
        window.draw(dot5);
        window.draw(dot6);
        window.display();


    }
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

