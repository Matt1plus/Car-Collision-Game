#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>    

// Define the car class
class Car {
public:
    sf::RectangleShape shape;
    int speed;

    Car() {
        shape.setSize(sf::Vector2f(50, 30));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(375, 500);
        speed = 5;
    }

    void moveLeft() {
        if (shape.getPosition().x > 50) {
            shape.move(-speed, 0);
        }
    }

    void moveRight() {
        if (shape.getPosition().x < 700) {
            shape.move(speed, 0);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Car Game");

    // Create the car object
    Car car;

    // Obstacles vector
    std::vector<sf::RectangleShape> obstacles;

    // Random obstacle generation
    srand(time(NULL));

    // Scoring variables
    int carsPassed = 0;
    int obstaclesPassed = 0;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle other events like key presses for car movement
        }

        // Clear the window
        window.clear();

        // Move and draw the car
        // Handle car movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            car.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            car.moveRight();
        }
        window.draw(car.shape);

        // Generate obstacles
        if (rand() % 100 < 10) { // Adjust the percentage for obstacle generation
            sf::RectangleShape obstacle(sf::Vector2f(50, 30));
            obstacle.setFillColor(sf::Color::Blue);
            obstacle.setPosition(rand() % 750, 0);
            obstacles.push_back(obstacle);
        }

        // Move and draw obstacles
        for (size_t i = 0; i < obstacles.size(); i++) {
            obstacles[i].move(0, 5); // Adjust obstacle speed
            window.draw(obstacles[i]);
        }

        // Check if obstacles passed
        for (size_t i = 0; i < obstacles.size(); i++) {
            if (obstacles[i].getPosition().y > 600) {
                obstaclesPassed++;
                obstacles.erase(obstacles.begin() + i);
            }
        }

        // Check if car passed
        for (size_t i = 0; i < obstacles.size(); i++) {
            if (car.shape.getGlobalBounds().intersects(obstacles[i].getGlobalBounds())) {
                // Handle collision (game over logic)
                // For now, let's just close the window
                window.close();
            }
        }

        // Display score
        std::cout << "Cars Passed: " << carsPassed << ", Obstacles Passed: " << obstaclesPassed << std::endl;

        // Display everything on the screen
        window.display();
    }

    return 0;
}
