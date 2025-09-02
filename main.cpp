#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum Direction { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

class Boid {
    private:
        sf::Sprite sprite;
        Direction direction;
        bool visible;
        float speedH;
        float speedW;
        int windowWidth;
        int windowHeight;

        static std::string directionToString(Direction dir) {
            switch (dir) {
                case RIGHT: return "RIGHT";
                case LEFT: return "LEFT";
                case UP: return "UP";
                case DOWN: return "DOWN";
                default: return "UNKNOWN";
            }
        }

    public:
        Boid(const sf::Texture& texture, float speedH = 6.0f, float speedW = 8.0f, 
            int winWidth = 640, int winHeight = 480) 
            : sprite(texture), direction(RIGHT), visible(false), 
            speedH(speedH), speedW(speedW), windowWidth(winWidth), windowHeight(winHeight) {
            sprite.setPosition(0.0f, 0.0f);
        }

        void setVisible(bool vis) { visible = vis; }
        bool isVisible() const { return visible; }
        
        void reset() {
            sprite.setPosition(0.0f, 0.0f);
            sprite.setRotation(0);
            direction = RIGHT;
            visible = false;
        }

        sf::Vector2f getPosition() const {
            return sprite.getPosition();
        }

        void update() {
            if (visible == false) return;

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

        bool shouldSpawnNext() const {
            return visible && direction == DOWN;
        }

        bool hasReachedTop() const {
            return visible && direction == UP && sprite.getPosition().y <= 0;
        }

        void draw(sf::RenderWindow& window) {
            if (visible) {
                window.draw(sprite);
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Boid& boid) {
            sf::Vector2f position = boid.sprite.getPosition(); 
            os << "Boid(Direction: " << directionToString(boid.direction) 
            << ", Visible: " << std::boolalpha << boid.visible 
            << ", Position: (" << position.x << ", " << position.y << "))";
            return os;
        }
};

class BoidSystem {
    private:
        std::vector<Boid> boids;
        int updateCounter;
        static const int UPDATE_FREQUENCY = 100;

    public:
        BoidSystem(const sf::Texture& texture, int numBoids = 4, 
                int winWidth = 640, int winHeight = 480) : updateCounter(0) {
            for (int i = 0; i < numBoids; ++i) {
                boids.emplace_back(texture, 6.0f, 8.0f, winWidth, winHeight);
            }

            // First boid starts visible
            if (boids.empty() == false) {
                boids[0].setVisible(true);
            }
        }

        void update() {
            ++updateCounter;
            
            if (updateCounter % UPDATE_FREQUENCY == 0) {
                // Check if we need to reset (last boid reached top)
                if (boids.empty() == false && boids.back().hasReachedTop()) {
                    resetAll();
                    return;
                }

                printBoids(boids);

                // Spawn next boids when current ones are ready
                for (size_t i = 0; i < boids.size() - 1; ++i) {
                    bool shouldSpawn = boids[i].shouldSpawnNext();
                    bool nextVisible = boids[i + 1].isVisible();

                    std::cout << "Boid " << i << ": shouldSpawnNext() = " << std::boolalpha << shouldSpawn 
                            << ", Boid " << (i + 1) << ": isVisible() = " << nextVisible << std::endl;

                    if (shouldSpawn && !nextVisible) {
                        boids[i + 1].setVisible(true);
                        std::cout << "Boid " << (i + 1) << " is now visible." << std::endl;
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
                boids[0].setVisible(true);
            }
        }

        void draw(sf::RenderWindow& window) {
            for (auto& boid : boids) {
                boid.draw(window);
            }
        }

        void printBoids(const std::vector<Boid>& boids) {
            for (const auto& boid : boids) {
                std::cout << boid << std::endl;
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

    BoidSystem boidSystem(texture, 4, width, height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        boidSystem.update();

        window.clear(sf::Color(255, 255, 255, 0));
        boidSystem.draw(window);
        window.display();
    }

    return 0;
}