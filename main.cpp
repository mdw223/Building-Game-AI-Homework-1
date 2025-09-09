/**
 * @author Malik Wensman
 * @date September 5, 2025 
 */

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <thread> // This was generated with the help of ChatGPT
#include <chrono> // This was generated with the help of ChatGPT

enum Direction { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

class Boid {
    private:
        sf::Sprite sprite;
        Direction direction;
        bool isVisible;
        float speedH;
        float speedW;
        int windowWidth;
        int windowHeight;

    public:
        // This constructor was generated with the help of ChatGPT
        Boid(const sf::Texture& texture, float speedH = 6.0f, float speedW = 8.0f, 
            int winWidth = 640, int winHeight = 480) 
            : sprite(texture), direction(RIGHT), isVisible(false), 
            speedH(speedH), speedW(speedW), windowWidth(winWidth), windowHeight(winHeight) {
            sprite.setPosition(0.0f, 0.0f);
        }

        void setIsVisible(bool visibility) { isVisible = visibility; }
        bool getIsVisible() const { return isVisible; }
        
        void reset() {
            sprite.setPosition(0.0f, 0.0f);
            sprite.setRotation(0);
            direction = RIGHT;
            isVisible = false;
        }
        
        // is read only
        sf::Vector2f getPosition() const {
            return sprite.getPosition();
        }

        void update() {
            if (isVisible == false) return;

            sf::FloatRect bounds = sprite.getGlobalBounds();
            
            switch (direction) {
                case RIGHT:
                    sprite.move(speedW, 0.0f);
                    if (sprite.getPosition().x + bounds.width >= windowWidth) {
                        direction = DOWN;
                        sprite.setRotation(90);
                    }
                    break;
                    
                case DOWN:
                    sprite.move(0.0f, speedH);
                    if (sprite.getPosition().y + bounds.height >= windowHeight) {
                        direction = LEFT;
                        sprite.setRotation(180);
                    }
                    break;
                    
                case LEFT:
                    sprite.move(-speedW, 0.0f);
                    if (sprite.getPosition().x - bounds.width <= 0) {
                        direction = UP;
                        sprite.setRotation(270);
                    }
                    break;
                    
                case UP:
                    sprite.move(0.0f, -speedH);
                    break;
            }
        }

        bool shouldCreateNewBoid() const {
            return isVisible && direction == DOWN;
        }

        bool hasReachedTop() const {
            return isVisible && direction == UP && sprite.getPosition().y <= 0;
        }

        // & : pass by reference so it can be updated
        void draw(sf::RenderWindow& window) {
            if (isVisible) {
                window.draw(sprite);
            }
        }
};

/**
 * Manages all the boids in a vector to be able to update, create, reset, and draw multiple boids at a time
 */
class BoidManager {
    private:
        // vector ensures elements stored in continguous memory, faster, auto resizing
        std::vector<Boid> boids; 
        int updateCounter;
        static const int UPDATE_FREQUENCY = 100;

    public:
        // This constructor was generated with the help of ChatGPT
        BoidManager(const sf::Texture& texture, int numBoids = 4, 
                int winWidth = 640, int winHeight = 480) : updateCounter(0) {
            for (int i = 0; i < numBoids; ++i) {
                // constructs new element at end of vector using args, more efficient than push_back()
                boids.emplace_back(texture, 6.0f, 8.0f, winWidth, winHeight); 
            }

            // First boid starts visible
            if (boids.empty() == false) {
                boids[0].setIsVisible(true);
            }
        }

        void update() {
            ++updateCounter;
            
            // execute every 100 calls
            if (updateCounter % UPDATE_FREQUENCY == 0) {
                // Check if we need to reset the game, only if the last boid reached top
                if (boids.empty() == false && boids.back().hasReachedTop()) {
                    std::this_thread::sleep_for(std::chrono::seconds(2)); // This was generated with the help of ChatGPT
                    resetAll();
                    return; // dont do anyting else for this iteration
                }

                // Spawn next boids when current ones are ready
                for (size_t i = 0; i < boids.size() - 1; ++i) {
                    bool shouldCreateNewBoid = boids[i].shouldCreateNewBoid();
                    bool nextVisible = boids[i + 1].getIsVisible();

                    if (shouldCreateNewBoid && !nextVisible) {
                        boids[i + 1].setIsVisible(true);
                    }
                }

                // Update all boids
                for (auto& boid : boids) {
                    boid.update();
                }
            }
        }

        void resetAll() {
            for (auto& boid : boids) {
                boid.reset();
            }
            if (boids.empty() == false) {
                boids[0].setIsVisible(true);
            }
        }

        void draw(sf::RenderWindow& window) {
            for (auto& boid : boids) {
                boid.draw(window);
            }
        }

};

int main() {
    const int width = 640;
    const int height = 480;
    sf::RenderWindow window(sf::VideoMode(width, height), "Building Game AI Homework 1");

    sf::Texture texture;
    if (texture.loadFromFile("boid-sm.png") == false) {
        std::cerr << "Error loading texture!" << std::endl;
        return 1;
    }

    // this button was generated with the help of ChatGPT
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Warning: Could not load font. Button text may not display properly." << std::endl;
    }
    sf::RectangleShape button(sf::Vector2f(150, 50));
    button.setPosition(width/2 - 100, height - 240);
    button.setFillColor(sf::Color::Green);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::Black);
    sf::Text buttonText("Click for more boids", font, 16);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(width/2 - 90, height - 240);

    // part 2
    bool isSimple = true;
    sf::Sprite sprite(texture);
    sprite.setPosition(0.f, 0.f);
    int iteration = 0;

    // part 3
    BoidManager* boidManager = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // This button event was generated with the help of ChatGPT
        if (event.type == sf::Event::MouseButtonPressed && isSimple) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    
                    if (button.getGlobalBounds().contains(mousePosF)) {
                        isSimple = false;
                        boidManager = new BoidManager(texture, 4, width, height);
                    }
                }
            }

        if(isSimple) {
            if (iteration % 100 == 0) {
                sprite.move(10.0f, 0.0f);
                if (sprite.getPosition().x + sprite.getGlobalBounds().width >= width) {
                    sprite.setPosition(0.f, 0.f);
                }
            }
            window.clear(sf::Color(255, 255, 255, 0));
            window.draw(sprite);
            window.draw(button);
            window.draw(buttonText);
            window.display();
            iteration++;
        } else {
            boidManager->update();
            window.clear(sf::Color(255, 255, 255, 0));
            boidManager->draw(window);
            window.display();
        }
    }

    delete boidManager;
    return 0;
}