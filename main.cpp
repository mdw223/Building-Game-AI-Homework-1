#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    int width = 640;
    int height = 480;
    sf::RenderWindow window(sf::VideoMode(width, height), "Building Game AI Homework 1");
    
    // sf::CircleShape shape(5.f); // shape(radius)
    // shape.setFillColor(sf::Color::Green);
    // sf::RenderTexture renderTexture;
    // renderTexture.create(10, 10);
    // renderTexture.clear(sf::Color::Transparent);
    // renderTexture.draw(shape);
    // renderTexture.display();
    // sf::Sprite topSprite(renderTexture.getTexture());
    // topSprite.setPosition(0.f, 0.f);

    sf::Texture texture;
    if (!texture.loadFromFile("boid-sm.png"))
    {
        exit(1);
    }
    sf::Sprite sprite1(texture);
    sprite1.setPosition(0.f, 0.f); // Start position

    sf::Sprite sprite2(texture);
    bool sprite2Visible = false;

    sf::Sprite sprite3(texture);
    bool sprite3Visible = false;


    int direction1 = 0; // Movement direction: 0 = right, 1 = down, 2 = left, 3 = up
    float speed = 5.f; // Speed of movement
    int direction2 = 0;
    int direction3 = 0;
    int iteration = 0;
    while (window.isOpen()) 
    {
        sf::Event event;
        // checks for any pending events in the window's queue
        // pollEvent() is non-blocking unlike waitEvent()
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if( iteration % 100 == 0) {

            if (sprite2Visible && direction2 == 1) {
                sprite2.move(0.f,speed);
                if (sprite3Visible == false) {
                    sprite3Visible = true;
                    sprite3.setPosition(0.f, 0.f);
                }
                
            }
            if (sprite3Visible == true && direction3 == 0) {
                sprite3.move(speed, 0.f);
            }

            if (sprite2Visible && direction2 == 0) {
                sprite2.move(speed, 0.f);
                if (sprite2.getPosition().x + sprite2.getGlobalBounds().width >= width) {
                    direction2 = 1;
                    sprite2.setRotation(90);
                }
            }

            

            // will start moving right: direction = 0
            switch (direction1) {
                case 0: // right
                    sprite1.move(speed, 0.f);
                    if (sprite1.getPosition().x + sprite1.getGlobalBounds().width >= width) {
                        direction1 = 1;
                        sprite1.setRotation(90);

                        sprite2Visible = true;
                        sprite2.setPosition(0.f, 0.f);
                    }
                    break;
                case 1: // down
                    sprite1.move(0.f,speed);
                    if (sprite1.getPosition().y + sprite1.getGlobalBounds().height >= height) {
                        direction1 = 2;
                        sprite1.setRotation(180);
                    }
                    break;
                case 2: // left
                    sprite1.move(-speed,0.f);
                    if (sprite1.getPosition().x - sprite1.getGlobalBounds().width <= 0) {
                        direction1 = 3;
                        sprite1.setRotation(270);
                    }
                    break;
                case 3: // up
                    sprite1.move(0.f,-speed);
                    if (sprite1.getPosition().y - sprite1.getGlobalBounds().height <= 0) {
                        direction1 = 0;
                        sprite1.setRotation(0);
                    }
                    break;
            }
        }
            
        
        
        
        /* The window is cleared with a white color (RGBA: 255, 255, 255, 0). 
        The last value (0) indicates full transparency, which may not be visible 
        */
        window.clear(sf::Color(255,255,255,0));
        window.draw(sprite1); // The sprite is drawn onto the window.
        if (sprite2Visible) {
            window.draw(sprite2);
        }
        if (sprite3Visible) {
            window.draw(sprite3);
        }
        //window.draw(topSprite);
        window.display(); // The display is updated to show the new frame.
        
        ++iteration;

    }

    return 0;
}