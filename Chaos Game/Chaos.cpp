// Chaos_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Eduardo and Jordan
//Need text to user, user inut, (4), vector/array to hold point, vm,while,draw,

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

// linear interpolation function
float lerp(float a, float b, float f)               //To get midpoint/2 and .33
{
    return a + f * (b - a);
}

int main()
{
    VideoMode vm(1920, 1080);                        //Make window
    RenderWindow window(vm, "Chaos Game!!!", Style::Fullscreen);

    Text text, dotText;                               //CREATE TEXT; ,,INSTRUCTION AND COUNTER 
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(10, 10);
    text.setFillColor(Color::White);
    dotText = text;
    dotText.setPosition(10, 100);

    int dotCounter = 0;                             //see how many clicks;

    RectangleShape dot1;                            //Object to create dots
    dot1.setSize(Vector2f(1, 1));                  //dots1 used as base for first 4 clicks
    dot1.setFillColor(Color::White);
    vector<RectangleShape> dotList;

    int rng;                                        //rng number

    bool acceptInputMouse = true;                   //control input;

    Vector2f temp, temp2;

    Color red(255, 0, 0);
    Color blue(0, 0, 255);
    Color green(0, 255, 0);
    Color yellow(255, 255, 0);
    Color pink(255, 0, 255);
    Color orange(255, 128, 0);
    Color purple(127, 0, 255);

    vector<Color> rainbow = { red, orange, yellow, green, blue, purple };                           //VECTOR RAINBOW   

    bool isTriangle = false;                                                                        //List for shapes;
    bool isPent = false;
    bool isHex = false;



    while (window.isOpen())                                                                         //Frame loop starts
    {
        float x, y;                                                                                  //Coordinates for points

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)                                                        //Close for red X 
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))                                               //ESC TO CLOSE
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) && isPent == false && isHex == false)                                                    //what shape user wants
        {
            isTriangle = true;

        }
        if (Keyboard::isKeyPressed(Keyboard::W) && isTriangle == false && isHex == false)
        {
            isPent = true;

        }
        if (Keyboard::isKeyPressed(Keyboard::E) && isTriangle == false && isHex == isPent)
        {
            isHex = true;

        }

        /***************************************************************************
         GET Q,W,E AND RELATING INPUT CLICKS
        ***************************************************************************/

        if (acceptInputMouse && dotCounter < 5 && isTriangle == true && isPent == false && isHex == false)             //Loops to get click input 4 times
        {
            if (event.type == Event::MouseButtonPressed)
            {
                RectangleShape* ndot = new RectangleShape;                                                           //new dot
                x = event.mouseButton.x;                                                                             //GET X THEN Y
                y = event.mouseButton.y;
                *ndot = dot1;
                ndot->setPosition(x, y);                                                                             //SET DOT X,Y                              
                dotCounter++;                                                                                        //INCREMENT
                acceptInputMouse = false;                                                                            //AVOID 100 MPH
                dotList.push_back(*ndot);                                                                            //Push in vector
            }
        }

        if (acceptInputMouse && dotCounter < 7 && isTriangle == false && isPent == true && isHex == false)           //FOR pent
        {
            if (event.type == Event::MouseButtonPressed)
            {
                RectangleShape* ndot = new RectangleShape;
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                *ndot = dot1;
                ndot->setPosition(x, y);
                dotCounter++;
                acceptInputMouse = false;
                dotList.push_back(*ndot);
            }
        }
        if (acceptInputMouse && dotCounter < 8 && isTriangle == false && isPent == false && isHex == true)          //FOR HEX
        {
            if (event.type == Event::MouseButtonPressed)
            {
                RectangleShape* ndot = new RectangleShape;
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                *ndot = dot1;
                ndot->setPosition(x, y);
                dotCounter++;
                acceptInputMouse = false;
                dotList.push_back(*ndot);
            }
        }
        if (acceptInputMouse && dotCounter > 3000)                                                                  //RESET PART
        {                                                                                                           //RESET if COUNTER>3000
            if (event.type == Event::MouseButtonPressed)
            {
                dotList.clear();
                dotCounter = 0;
                isTriangle = false;
                isPent = false;
                isHex = false;

            }
        }
        /***************************************************************************
                 Chaos part
         ***************************************************************************/
        if (dotCounter >= 4 && isTriangle == true && isPent == false && isHex == false)
        {
            RectangleShape* ndot = new RectangleShape;                  //MAKES NEW EA FRAME
            ndot->setSize(Vector2f(1, 1));
            //ndot->setFillColor(Color::White);
            rng = rand() % (3);                                         //RANDOM 0,1,2
            // if (rng == 0)
             //{
            ndot->setFillColor(rainbow.at(rng));
            temp = dotList.at(rng).getPosition();                     //GET FIRST DOT X AND Y
            temp2 = dotList.at(dotList.size() - 1).getPosition();   //GET LAST DOT X AND Y
            temp.x = lerp(temp.x, temp2.x, 0.5);
            temp.y = lerp(temp.y, temp2.y, 0.5);
            ndot->setPosition(temp);                                //GET MIDPOINT^^/////////////
            dotList.push_back(*ndot);                               //MIDPOINT IS NEW DOT, BACK AT THE LINE
            dotCounter++;
            /*  }
              else if (rng == 1)                                          //same for next 2 block, but index = rng
              {
                  ndot->setFillColor(blue);                               //COMMITTED OUT INCASE TOP BLOCK (EXPERIMENT FAILS)
                  temp = dotList.at(1).getPosition();
                  temp2 = dotList.at(dotList.size() - 1).getPosition();
                  temp.x = temp.x + temp2.x;
                  temp.x = temp.x / 2;
                  temp.y = temp.y + temp2.y;
                  temp.y = temp.y / 2;
                  ndot->setPosition(temp);
                  dotList.push_back(*ndot);
                  dotCounter++;
              }
              else
              {
                  ndot->setFillColor(green);
                  temp = dotList.at(2).getPosition();
                  temp2 = dotList.at(dotList.size() - 1).getPosition();
                  temp.x = temp.x + temp2.x;
                  temp.x = temp.x / 2;
                  temp.y = temp.y + temp2.y;
                  temp.y = temp.y / 2;
                  ndot->setPosition(temp);
                  dotList.push_back(*ndot);
                  dotCounter++;
              }*/
        }
        if (dotCounter >= 6 && isTriangle == false && isPent == true && isHex == false)
        {
            RectangleShape* ndot = new RectangleShape;
            ndot->setSize(Vector2f(1, 1));
            rng = rand() % (5);
            ndot->setFillColor(rainbow.at(rng));
            temp = dotList.at(rng).getPosition();
            temp2 = dotList.at(dotList.size() - 1).getPosition();
            temp.x = lerp(temp.x, temp2.x, 0.33);
            temp.y = lerp(temp.y, temp2.y, 0.33);
            ndot->setPosition(temp);
            dotList.push_back(*ndot);
            dotCounter++;
        }
        if (dotCounter >= 7 && isTriangle == false && isPent == false && isHex == true)
        {
            RectangleShape* ndot = new RectangleShape;
            ndot->setSize(Vector2f(1, 1));
            rng = rand() % (6);
            ndot->setFillColor(rainbow.at(rng));
            temp = dotList.at(rng).getPosition();
            temp2 = dotList.at(dotList.size() - 1).getPosition();
            temp.x = lerp(temp.x, temp2.x, 0.33);
            temp.y = lerp(temp.y, temp2.y, 0.33);
            ndot->setPosition(temp);
            dotList.push_back(*ndot);
            dotCounter++;
        }

        if (event.type == Event::MouseButtonReleased)               //Controls clicks
        {
            acceptInputMouse = true;
        }

        if (dotCounter == 0 && isTriangle == false && isPent == false && isHex == false)            //Output text                
        {
            text.setString("Welcome to Chaos Game!!! \n   Q=Triangle, W=Pentagon, E=Hexagon");
        }
        if (isTriangle == true && dotCounter < 4)
        {
            text.setString("TRIANGLE--Select 4 point to start!");
        }
        if (isPent == true && dotCounter < 7)
        {
            text.setString("PENTAGON--Select 6th point to start!");
        }
        if (isHex == true && dotCounter < 8)
        {
            text.setString("HEXAGON--Select 7 point to start!");
        }
        if (dotCounter > 8)
        {
            text.setString("");
        }
        if (dotCounter > 3000)
        {
            text.setString("Should see pattern by now \n Click anywhere to restart");
        }

        stringstream ss;
        ss << "Dot counter: " << dotCounter;
        dotText.setString(ss.str());

        window.clear();                                              //draw
        window.draw(text);
        window.draw(dotText);
        for (int i = 0; i < dotList.size(); i++)
        {
            window.draw(dotList.at(i));
        }
        window.display();
    }
}